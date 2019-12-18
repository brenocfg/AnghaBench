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
 long _divulong (long,long) ; 

long
_divslong (long a, long b)
{
  long r;

  r = _divulong((a < 0 ? -a : a),
                (b < 0 ? -b : b));
  if ( (a < 0) ^ (b < 0))
    return -r;
  else
    return r;
}