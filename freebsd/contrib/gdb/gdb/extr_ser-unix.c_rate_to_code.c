#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int rate; int code; } ;

/* Variables and functions */
 TYPE_1__* baudtab ; 
 int /*<<< orphan*/  warning (char*,int,int,...) ; 

__attribute__((used)) static int
rate_to_code (int rate)
{
  int i;

  for (i = 0; baudtab[i].rate != -1; i++)
    {
      /* test for perfect macth. */
      if (rate == baudtab[i].rate)
        return baudtab[i].code;
      else
        {
	  /* check if it is in between valid values. */
          if (rate < baudtab[i].rate)
	    {
	      if (i)
	        {
	          warning ("Invalid baud rate %d.  Closest values are %d and %d.",
	                    rate, baudtab[i - 1].rate, baudtab[i].rate);
		}
	      else
	        {
	          warning ("Invalid baud rate %d.  Minimum value is %d.",
	                    rate, baudtab[0].rate);
		}
	      return -1;
	    }
        }
    }
 
  /* The requested speed was too large. */
  warning ("Invalid baud rate %d.  Maximum value is %d.",
            rate, baudtab[i - 1].rate);
  return -1;
}