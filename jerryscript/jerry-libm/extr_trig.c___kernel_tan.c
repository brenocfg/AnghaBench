#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ lo; } ;
struct TYPE_4__ {double dbl; TYPE_1__ as_int; } ;
typedef  TYPE_2__ double_accessor ;

/* Variables and functions */
 double T0 ; 
 double T1 ; 
 double T10 ; 
 double T11 ; 
 double T12 ; 
 double T2 ; 
 double T3 ; 
 double T4 ; 
 double T5 ; 
 double T6 ; 
 double T7 ; 
 double T8 ; 
 double T9 ; 
 int __HI (double) ; 
 int __LO (double) ; 
 double fabs (double) ; 
 double one ; 
 double pio4 ; 
 double pio4lo ; 

__attribute__((used)) static double
__kernel_tan (double x, double y, int iy)
{
  double_accessor z;
  double r, v, w, s;
  int ix, hx;

  hx = __HI (x); /* high word of x */
  ix = hx & 0x7fffffff; /* high word of |x| */
  if (ix < 0x3e300000) /* x < 2**-28 */
  {
    if ((int) x == 0) /* generate inexact */
    {
      if (((ix | __LO (x)) | (iy + 1)) == 0)
      {
        return one / fabs (x);
      }
      else
      {
        if (iy == 1)
        {
          return x;
        }
        else /* compute -1 / (x + y) carefully */
        {
          double a;
          double_accessor t;

          z.dbl = w = x + y;
          z.as_int.lo = 0;
          v = y - (z.dbl - x);
          t.dbl = a = -one / w;
          t.as_int.lo = 0;
          s = one + t.dbl * z.dbl;
          return t.dbl + a * (s + t.dbl * v);
        }
      }
    }
  }
  if (ix >= 0x3FE59428) /* |x| >= 0.6744 */
  {
    if (hx < 0)
    {
      x = -x;
      y = -y;
    }
    z.dbl = pio4 - x;
    w = pio4lo - y;
    x = z.dbl + w;
    y = 0.0;
  }
  z.dbl = x * x;
  w = z.dbl * z.dbl;
  /*
   * Break x^5 * (T[1] + x^2 * T[2] + ...) into
   * x^5 (T[1] + x^4 * T[3] + ... + x^20 * T[11]) +
   * x^5 (x^2 * (T[2] + x^4 * T[4] + ... + x^22 * [T12]))
   */
  r = T1 + w * (T3 + w * (T5 + w * (T7 + w * (T9 + w * T11))));
  v = z.dbl * (T2 + w * (T4 + w * (T6 + w * (T8 + w * (T10 + w * T12)))));
  s = z.dbl * x;
  r = y + z.dbl * (s * (r + v) + y);
  r += T0 * s;
  w = x + r;
  if (ix >= 0x3FE59428)
  {
    v = (double) iy;
    return (double) (1 - ((hx >> 30) & 2)) * (v - 2.0 * (x - (w * w / (w + v) - r)));
  }
  if (iy == 1)
  {
    return w;
  }
  else
  {
    /*
     * if allow error up to 2 ulp, simply return
     * -1.0 / (x + r) here
     */
    /* compute -1.0 / (x + r) accurately */
    double a;
    double_accessor t;

    z.dbl = w;
    z.as_int.lo = 0;
    v = r - (z.dbl - x); /* z + v = r + x */
    t.dbl = a = -1.0 / w; /* a = -1.0 / w */
    t.as_int.lo = 0;
    s = 1.0 + t.dbl * z.dbl;
    return t.dbl + a * (s + t.dbl * v);
  }
}