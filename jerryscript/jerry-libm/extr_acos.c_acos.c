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
 double one ; 
 double pS0 ; 
 double pS1 ; 
 double pS2 ; 
 double pS3 ; 
 double pS4 ; 
 double pS5 ; 
 double pi ; 
 double pio2_hi ; 
 double pio2_lo ; 
 double qS1 ; 
 double qS2 ; 
 double qS3 ; 
 double qS4 ; 
 double sqrt (double) ; 

double
acos (double x)
{
  double z, p, q, r, w, s, c;
  int hx, ix;

  hx = __HI (x);
  ix = hx & 0x7fffffff;
  if (ix >= 0x3ff00000) /* |x| >= 1 */
  {
    if (((ix - 0x3ff00000) | __LO (x)) == 0) /* |x| == 1 */
    {
      if (hx > 0) /* acos(1) = 0  */
      {
        return 0.0;
      }
      else /* acos(-1) = pi */
      {
        return pi + 2.0 * pio2_lo;
      }
    }
    return (x - x) / (x - x); /* acos(|x|>1) is NaN */
  }
  if (ix < 0x3fe00000) /* |x| < 0.5 */
  {
    if (ix <= 0x3c600000) /* if |x| < 2**-57 */
    {
      return pio2_hi + pio2_lo;
    }
    z = x * x;
    p = z * (pS0 + z * (pS1 + z * (pS2 + z * (pS3 + z * (pS4 + z * pS5)))));
    q = one + z * (qS1 + z * (qS2 + z * (qS3 + z * qS4)));
    r = p / q;
    return pio2_hi - (x - (pio2_lo - x * r));
  }
  else if (hx < 0) /* x < -0.5 */
  {
    z = (one + x) * 0.5;
    p = z * (pS0 + z * (pS1 + z * (pS2 + z * (pS3 + z * (pS4 + z * pS5)))));
    q = one + z * (qS1 + z * (qS2 + z * (qS3 + z * qS4)));
    s = sqrt (z);
    r = p / q;
    w = r * s - pio2_lo;
    return pi - 2.0 * (s + w);
  }
  else /* x > 0.5 */
  {
    double_accessor df;
    z = (one - x) * 0.5;
    s = sqrt (z);
    df.dbl = s;
    df.as_int.lo = 0;
    c = (z - df.dbl * df.dbl) / (s + df.dbl);
    p = z * (pS0 + z * (pS1 + z * (pS2 + z * (pS3 + z * (pS4 + z * pS5)))));
    q = one + z * (qS1 + z * (qS2 + z * (qS3 + z * qS4)));
    r = p / q;
    w = r * s + c;
    return 2.0 * (df.dbl + w);
  }
}