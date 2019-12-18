#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */

/* Variables and functions */
 char* strrchr (char*,char) ; 

char *
sparc_stabs_unglobalize_name (char *name)
{
  /* The Sun compilers (Sun ONE Studio, Forte Developer, Sun WorkShop,
     SunPRO) convert file static variables into global values, a
     process known as globalization.  In order to do this, the
     compiler will create a unique prefix and prepend it to each file
     static variable.  For static variables within a function, this
     globalization prefix is followed by the function name (nested
     static variables within a function are supposed to generate a
     warning message, and are left alone).  The procedure is
     documented in the Stabs Interface Manual, which is distrubuted
     with the compilers, although version 4.0 of the manual seems to
     be incorrect in some places, at least for SPARC.  The
     globalization prefix is encoded into an N_OPT stab, with the form
     "G=<prefix>".  The globalization prefix always seems to start
     with a dollar sign '$'; a dot '.' is used as a seperator.  So we
     simply strip everything up until the last dot.  */

  if (name[0] == '$')
    {
      char *p = strrchr (name, '.');
      if (p)
	return p + 1;
    }

  return name;
}