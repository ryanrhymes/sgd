// -*- C++ -*-
// SVM with stochastic gradient (preprocessing)
// Copyright (C) 2007- Leon Bottou

// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 2.1 of the License, or (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111, USA


#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <cstdlib>
#include <cstdio>
#include <cmath>

#if defined(WIN32)
# include <io.h>
# include <fcntl.h>
#endif


#include "assert.h"
#include "vectors.h"
#include "data.h"

using namespace std;


int 
main(int argc, const char **argv)
{
  bool vwflag = false;
  bool binflag = false;
  string filename;
  // parse arguments
  if (argc > 1)
    filename = argv[argc-1];
  if (argc == 2)
    vwflag = binflag = false;
  else if (argc == 3 && string(argv[1]) == "-vw")
    vwflag = true;
  else if (argc == 3 && string(argv[1]) == "-bin")
    binflag = true;
  else 
    assertfail("usage: " << argv[0] << " [-vw|-bin] file.bin[.gz]");

  // windows: make cout binary (sigh!)
#ifdef WIN32
  if (binflag)
    _setmode(1, _O_BINARY);
#endif
  
  // convert data by chunks
  xvec_t x;
  yvec_t y;
  int total = 0;
  Loader loader(filename.c_str());
  while (loader.load(x, y, false, 100) > 0)
    {
      int size = x.size();
      for (int i=0; i<size; i++) 
        if (binflag) 
          { cout.put(y[i] > 0 ? 1 : 0); x[i].save(cout); }
        else if (vwflag)
          { cout << y[i] << " |" << x[i]; }
        else 
          { cout << y[i] << x[i]; }
      total += size;
      x.clear();
      y.clear();
    }
  cerr << "Converted " << total << " rows." << endl;
  return 0;
}

