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
 double P1 ; 
 double P2 ; 
 double P3 ; 
 double P4 ; 
 double P5 ; 
 unsigned int __HI (double) ; 
 unsigned int __LO (double) ; 
 scalar_t__* halF ; 
 double huge ; 
 double invln2 ; 
 double* ln2HI ; 
 double* ln2LO ; 
 double o_threshold ; 
 double one ; 
 double twom1000 ; 
 double u_threshold ; 

double
exp (double x) /* default IEEE double exp */
{
  double hi, lo, c, t;
  int k = 0, xsb;
  unsigned hx;

  hx = __HI (x); /* high word of x */
  xsb = (hx >> 31) & 1; /* sign bit of x */
  hx &= 0x7fffffff; /* high word of |x| */

  /* filter out non-finite argument */
  if (hx >= 0x40862E42) /* if |x| >= 709.78... */
  {
    if (hx >= 0x7ff00000)
    {
      if (((hx & 0xfffff) | __LO (x)) != 0) /* NaN */
      {
        return x + x;
      }
      else /* exp(+-inf) = {inf,0} */
      {
        return (xsb == 0) ? x : 0.0;
      }
    }
    if (x > o_threshold) /* overflow */
    {
      return huge * huge;
    }
    if (x < u_threshold) /* underflow */
    {
      return twom1000 * twom1000;
    }
  }

  /* argument reduction */
  if (hx > 0x3fd62e42) /* if  |x| > 0.5 ln2 */
  {
    if (hx < 0x3FF0A2B2) /* and |x| < 1.5 ln2 */
    {
      hi = x - ln2HI[xsb];
      lo = ln2LO[xsb];
      k = 1 - xsb - xsb;
    }
    else
    {
      k = (int) (invln2 * x + halF[xsb]);
      t = k;
      hi = x - t * ln2HI[0]; /* t * ln2HI is exact here */
      lo = t * ln2LO[0];
    }
    x = hi - lo;
  }
  else if (hx < 0x3e300000) /* when |x| < 2**-28 */
  {
    if (huge + x > one) /* trigger inexact */
    {
      return one + x;
    }
  }
  else
  {
    k = 0;
  }

  double_accessor ret;

  /* x is now in primary range */
  t = x * x;
  c = x - t * (P1 + t * (P2 + t * (P3 + t * (P4 + t * P5))));
  if (k == 0)
  {
    return one - ((x * c) / (c - 2.0) - x);
  }
  else
  {
    ret.dbl = one - ((lo - (x * c) / (2.0 - c)) - hi);
  }
  if (k >= -1021)
  {
    ret.as_int.hi += (k << 20); /* add k to y's exponent */
    return ret.dbl;
  }
  else
  {
    ret.as_int.hi += ((k + 1000) << 20); /* add k to y's exponent */
    return ret.dbl * twom1000;
  }
}