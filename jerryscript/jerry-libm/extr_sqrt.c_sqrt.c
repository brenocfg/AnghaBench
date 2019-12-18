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
struct TYPE_3__ {int hi; unsigned int lo; } ;
struct TYPE_4__ {scalar_t__ dbl; TYPE_1__ as_int; } ;
typedef  TYPE_2__ double_accessor ;

/* Variables and functions */
 int __HI (double) ; 
 unsigned int __LO (double) ; 
 scalar_t__ one ; 
 scalar_t__ tiny ; 

double
sqrt (double x)
{
  int sign = (int) 0x80000000;
  unsigned r, t1, s1, ix1, q1;
  int ix0, s0, q, m, t, i;

  ix0 = __HI (x); /* high word of x */
  ix1 = __LO (x); /* low word of x */

  /* take care of Inf and NaN */
  if ((ix0 & 0x7ff00000) == 0x7ff00000)
  {
    return x * x + x; /* sqrt(NaN) = NaN, sqrt(+inf) = +inf, sqrt(-inf) = sNaN */
  }
  /* take care of zero */
  if (ix0 <= 0)
  {
    if (((ix0 & (~sign)) | ix1) == 0) /* sqrt(+-0) = +-0 */
    {
      return x;
    }
    else if (ix0 < 0) /* sqrt(-ve) = sNaN */
    {
      return (x - x) / (x - x);
    }
  }
  /* normalize x */
  m = (ix0 >> 20);
  if (m == 0) /* subnormal x */
  {
    while (ix0 == 0)
    {
      m -= 21;
      ix0 |= (ix1 >> 11);
      ix1 <<= 21;
    }
    for (i = 0; (ix0 & 0x00100000) == 0; i++)
    {
      ix0 <<= 1;
    }
    m -= i - 1;
    ix0 |= (ix1 >> (32 - i));
    ix1 <<= i;
  }
  m -= 1023; /* unbias exponent */
  ix0 = (ix0 & 0x000fffff) | 0x00100000;
  if (m & 1) /* odd m, double x to make it even */
  {
    ix0 += ix0 + ((ix1 & sign) >> 31);
    ix1 += ix1;
  }
  m >>= 1; /* m = [m / 2] */

  /* generate sqrt(x) bit by bit */
  ix0 += ix0 + ((ix1 & sign) >> 31);
  ix1 += ix1;
  q = q1 = s0 = s1 = 0; /* [q,q1] = sqrt(x) */
  r = 0x00200000; /* r = moving bit from right to left */

  while (r != 0)
  {
    t = s0 + r;
    if (t <= ix0)
    {
      s0 = t + r;
      ix0 -= t;
      q += r;
    }
    ix0 += ix0 + ((ix1 & sign) >> 31);
    ix1 += ix1;
    r >>= 1;
  }

  r = sign;
  while (r != 0)
  {
    t1 = s1 + r;
    t = s0;
    if ((t < ix0) || ((t == ix0) && (t1 <= ix1)))
    {
      s1 = t1 + r;
      if (((t1 & sign) == sign) && (s1 & sign) == 0)
      {
        s0 += 1;
      }
      ix0 -= t;
      if (ix1 < t1)
      {
        ix0 -= 1;
      }
      ix1 -= t1;
      q1 += r;
    }
    ix0 += ix0 + ((ix1 & sign) >> 31);
    ix1 += ix1;
    r >>= 1;
  }

  double_accessor ret;

  /* use floating add to find out rounding direction */
  if ((ix0 | ix1) != 0)
  {
    ret.dbl = one - tiny; /* trigger inexact flag */
    if (ret.dbl >= one)
    {
      ret.dbl = one + tiny;
      if (q1 == (unsigned) 0xffffffff)
      {
        q1 = 0;
        q += 1;
      }
      else if (ret.dbl > one)
      {
        if (q1 == (unsigned) 0xfffffffe)
        {
          q += 1;
        }
        q1 += 2;
      }
      else
      {
        q1 += (q1 & 1);
      }
    }
  }
  ix0 = (q >> 1) + 0x3fe00000;
  ix1 = q1 >> 1;
  if ((q & 1) == 1)
  {
    ix1 |= sign;
  }
  ix0 += (m << 20);
  ret.as_int.hi = ix0;
  ret.as_int.lo = ix1;
  return ret.dbl;
}