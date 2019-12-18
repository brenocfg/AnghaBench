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
 int process_reference (char**) ; 

int
symbol_reference_defined (char **string)
{
  char *p = *string;
  int refnum = 0;

  refnum = process_reference (&p);

  /* Defining symbols end in '=' */
  if (*p == '=')
    {
      /* Symbol is being defined here. */
      *string = p + 1;
      return refnum;
    }
  else
    {
      /* Must be a reference.   Either the symbol has already been defined,
         or this is a forward reference to it.  */
      *string = p;
      return -1;
    }
}