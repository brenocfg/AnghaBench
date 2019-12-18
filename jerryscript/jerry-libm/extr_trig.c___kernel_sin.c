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
 double S1 ; 
 double S2 ; 
 double S3 ; 
 double S4 ; 
 double S5 ; 
 double S6 ; 
 int __HI (double) ; 
 double half ; 

__attribute__((used)) static double
__kernel_sin (double x, double y, int iy)
{
  double z, r, v;
  int ix;

  ix = __HI (x) & 0x7fffffff; /* high word of x */
  if (ix < 0x3e400000) /* |x| < 2**-27 */
  {
    if ((int) x == 0)
    {
      return x; /* generate inexact */
    }
  }
  z = x * x;
  v = z * x;
  r = S2 + z * (S3 + z * (S4 + z * (S5 + z * S6)));
  if (iy == 0)
  {
    return x + v * (S1 + z * r);
  }
  else
  {
    return x - ((z * (half * y - v * r) - y) - v * S1);
  }
}