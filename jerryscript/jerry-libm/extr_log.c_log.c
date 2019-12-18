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
struct TYPE_3__ {int hi; } ;
struct TYPE_4__ {double dbl; TYPE_1__ as_int; } ;
typedef  TYPE_2__ double_accessor ;

/* Variables and functions */
 double Lg1 ; 
 double Lg2 ; 
 double Lg3 ; 
 double Lg4 ; 
 double Lg5 ; 
 double Lg6 ; 
 double Lg7 ; 
 int __HI (double) ; 
 unsigned int __LO (double) ; 
 double ln2_hi ; 
 double ln2_lo ; 
 double two54 ; 
 double zero ; 

double
log (double x)
{
  double hfsq, f, s, z, R, w, t1, t2, dk;
  int k, hx, i, j;
  unsigned lx;

  hx = __HI (x); /* high word of x */
  lx = __LO (x); /* low  word of x */

  k = 0;
  if (hx < 0x00100000) /* x < 2**-1022  */
  {
    if (((hx & 0x7fffffff) | lx) == 0) /* log(+-0) = -inf */
    {
      return -two54 / zero;
    }
    if (hx < 0) /* log(-#) = NaN */
    {
      return (x - x) / zero;
    }
    k -= 54;
    x *= two54; /* subnormal number, scale up x */
    hx = __HI (x); /* high word of x */
  }
  if (hx >= 0x7ff00000)
  {
    return x + x;
  }
  k += (hx >> 20) - 1023;
  hx &= 0x000fffff;
  i = (hx + 0x95f64) & 0x100000;

  double_accessor temp;
  temp.dbl = x;
  temp.as_int.hi = hx | (i ^ 0x3ff00000); /* normalize x or x / 2 */
  k += (i >> 20);
  f = temp.dbl - 1.0;

  if ((0x000fffff & (2 + hx)) < 3) /* |f| < 2**-20 */
  {
    if (f == zero)
    {
      if (k == 0)
      {
        return zero;
      }
      else
      {
        dk = (double) k;
        return dk * ln2_hi + dk * ln2_lo;
      }
    }
    R = f * f * (0.5 - 0.33333333333333333 * f);
    if (k == 0)
    {
      return f - R;
    }
    else
    {
      dk = (double) k;
      return dk * ln2_hi - ((R - dk * ln2_lo) - f);
    }
  }
  s = f / (2.0 + f);
  dk = (double) k;
  z = s * s;
  i = hx - 0x6147a;
  w = z * z;
  j = 0x6b851 - hx;
  t1 = w * (Lg2 + w * (Lg4 + w * Lg6));
  t2 = z * (Lg1 + w * (Lg3 + w * (Lg5 + w * Lg7)));
  i |= j;
  R = t2 + t1;
  if (i > 0)
  {
    hfsq = 0.5 * f * f;
    if (k == 0)
    {
      return f - (hfsq - s * (hfsq + R));
    }
    else
    {
      return dk * ln2_hi - ((hfsq - (s * (hfsq + R) + dk * ln2_lo)) - f);
    }
  }
  else
  {
    if (k == 0)
    {
      return f - s * (f - R);
    }
    else
    {
      return dk * ln2_hi - ((s * (f - R) - dk * ln2_lo) - f);
    }
  }
}