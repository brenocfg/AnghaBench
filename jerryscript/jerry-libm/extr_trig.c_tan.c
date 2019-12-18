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
 int __HI (double) ; 
 int __ieee754_rem_pio2 (double,double*) ; 
 double __kernel_tan (double,double,int) ; 

double
tan (double x)
{
  double y[2], z = 0.0;
  int n, ix;

  /* High word of x. */
  ix = __HI (x);

  /* |x| ~< pi/4 */
  ix &= 0x7fffffff;
  if (ix <= 0x3fe921fb)
  {
    return __kernel_tan (x, z, 1);
  }

  /* tan(Inf or NaN) is NaN */
  else if (ix >= 0x7ff00000)
  {
    return x - x; /* NaN */
  }

  /* argument reduction needed */
  else
  {
    n = __ieee754_rem_pio2 (x, y);
    return __kernel_tan (y[0], y[1], 1 - ((n & 1) << 1)); /*   1 -- n even, -1 -- n odd */
  }
}