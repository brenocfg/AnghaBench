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
struct TYPE_3__ {int hi; int lo; } ;
struct TYPE_4__ {double dbl; TYPE_1__ as_int; } ;
typedef  TYPE_2__ double_accessor ;

/* Variables and functions */
 int __HI (double) ; 
 unsigned int __LO (double) ; 

double
nextafter (double x,
           double y)
{
  int hx, hy, ix, iy;
  unsigned lx, ly;
  double_accessor ret;

  hx = __HI (x); /* high word of x */
  lx = __LO (x); /* low  word of x */
  hy = __HI (y); /* high word of y */
  ly = __LO (y); /* low  word of y */
  ix = hx & 0x7fffffff; /* |x| */
  iy = hy & 0x7fffffff; /* |y| */

  if (((ix >= 0x7ff00000) && ((ix - 0x7ff00000) | lx) != 0)     /* x is nan */
      || ((iy >= 0x7ff00000) && ((iy - 0x7ff00000) | ly) != 0)) /* y is nan */
  {
    return x + y;
  }

  if (x == y)
  {
    return x; /* x=y, return x */
  }

  if ((ix | lx) == 0)
  { /* x == 0 */
    ret.as_int.hi = hy & 0x80000000; /* return +-minsubnormal */
    ret.as_int.lo = 1;
    y = ret.dbl * ret.dbl;
    if (y == ret.dbl)
    {
      return y;
    }
    else
    {
      return ret.dbl; /* raise underflow flag */
    }
  }

  if (hx >= 0)
  { /* x > 0 */
    if (hx > hy || ((hx == hy) && (lx > ly)))
    { /* x > y, x -= ulp */
      if (lx == 0)
      {
        hx -= 1;
      }

      lx -= 1;
    }
    else
    { /* x < y, x += ulp */
      lx += 1;

      if (lx == 0)
      {
        hx += 1;
      }
    }
  }
  else
  { /* x < 0 */
    if (hy >= 0 || hx > hy || ((hx == hy) && (lx > ly)))
    { /* x < y, x -= ulp */
      if (lx == 0)
      {
        hx -= 1;
      }

      lx -= 1;
    }
    else
    { /* x > y, x += ulp */
      lx += 1;

      if (lx == 0)
      {
        hx += 1;
      }
    }
  }

  hy = hx & 0x7ff00000;

  if (hy >= 0x7ff00000)
  {
    return x + x; /* overflow */
  }

  if (hy < 0x00100000)
  { /* underflow */
    y = x * x;
    if (y != x)
    { /* raise underflow flag */
      ret.as_int.hi = hx;
      ret.as_int.lo = lx;
      return ret.dbl;
    }
  }

  ret.as_int.hi = hx;
  ret.as_int.lo = lx;
  return ret.dbl;
}