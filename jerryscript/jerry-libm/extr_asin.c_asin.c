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
 int __HI (double) ; 
 int __LO (double) ; 
 double fabs (double) ; 
 double huge ; 
 double one ; 
 double pS0 ; 
 double pS1 ; 
 double pS2 ; 
 double pS3 ; 
 double pS4 ; 
 double pS5 ; 
 double pio2_hi ; 
 double pio2_lo ; 
 double pio4_hi ; 
 double qS1 ; 
 double qS2 ; 
 double qS3 ; 
 double qS4 ; 
 double sqrt (double) ; 

double
asin (double x)
{
  double t, p, q, c, r, s;
  double_accessor w;
  int hx, ix;

  hx = __HI (x);
  ix = hx & 0x7fffffff;
  if (ix >= 0x3ff00000) /* |x| >= 1 */
  {
    if (((ix - 0x3ff00000) | __LO (x)) == 0) /* asin(1) = +-pi/2 with inexact */
    {
      return x * pio2_hi + x * pio2_lo;
    }
    return (x - x) / (x - x); /* asin(|x|>1) is NaN */
  }
  else if (ix < 0x3fe00000) /* |x| < 0.5 */
  {
    if (ix < 0x3e400000) /* if |x| < 2**-27 */
    {
      if (huge + x > one) /* return x with inexact if x != 0 */
      {
        return x;
      }
    }
    t = x * x;
    p = t * (pS0 + t * (pS1 + t * (pS2 + t * (pS3 + t * (pS4 + t * pS5)))));
    q = one + t * (qS1 + t * (qS2 + t * (qS3 + t * qS4)));
    w.dbl = p / q;
    return x + x * w.dbl;
  }
  /* 1 > |x| >= 0.5 */
  w.dbl = one - fabs (x);
  t = w.dbl * 0.5;
  p = t * (pS0 + t * (pS1 + t * (pS2 + t * (pS3 + t * (pS4 + t * pS5)))));
  q = one + t * (qS1 + t * (qS2 + t * (qS3 + t * qS4)));
  s = sqrt (t);
  if (ix >= 0x3FEF3333) /* if |x| > 0.975 */
  {
    w.dbl = p / q;
    t = pio2_hi - (2.0 * (s + s * w.dbl) - pio2_lo);
  }
  else
  {
    w.dbl = s;
    w.as_int.lo = 0;
    c = (t - w.dbl * w.dbl) / (s + w.dbl);
    r = p / q;
    p = 2.0 * s * r - (pio2_lo - 2.0 * c);
    q = pio4_hi - 2.0 * w.dbl;
    t = pio4_hi - (p - q);
  }
  if (hx > 0)
  {
    return t;
  }
  else
  {
    return -t;
  }
}