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
 int __HI (double) ; 
 int __LO (double) ; 
 double copysign (double,double) ; 
 double huge ; 
 double tiny ; 
 double two54 ; 
 double twom54 ; 

double
scalbn (double x, int n)
{
  int k, hx, lx;

  hx = __HI (x);
  lx = __LO (x);
  k = (hx & 0x7ff00000) >> 20; /* extract exponent */
  if (k == 0) /* 0 or subnormal x */
  {
    if ((lx | (hx & 0x7fffffff)) == 0) /* +-0 */
    {
      return x;
    }
    x *= two54;
    hx = __HI (x);
    k = ((hx & 0x7ff00000) >> 20) - 54;
    if (n < -50000) /*underflow */
    {
      return tiny * x;
    }
  }
  if (k == 0x7ff) /* NaN or Inf */
  {
    return x + x;
  }
  k = k + n;
  if (k > 0x7fe) /* overflow  */
  {
    return huge * copysign (huge, x);
  }
  if (k > 0) /* normal result */
  {
    double_accessor ret;
    ret.dbl = x;
    ret.as_int.hi = (hx & 0x800fffff) | (k << 20);
    return ret.dbl;
  }
  if (k <= -54)
  {
    if (n > 50000) /* in case integer overflow in n + k */
    {
      return huge * copysign (huge, x); /*overflow */
    }
    else
    {
      return tiny * copysign (tiny, x); /*underflow */
    }
  }
  k += 54; /* subnormal result */
  double_accessor ret;
  ret.dbl = x;
  ret.as_int.hi = (hx & 0x800fffff) | (k << 20);
  return ret.dbl * twom54;
}