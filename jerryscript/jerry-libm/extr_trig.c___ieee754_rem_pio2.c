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
struct TYPE_3__ {int hi; int /*<<< orphan*/  lo; } ;
struct TYPE_4__ {double dbl; TYPE_1__ as_int; } ;
typedef  TYPE_2__ double_accessor ;

/* Variables and functions */
 int __HI (double) ; 
 int /*<<< orphan*/  __LO (double) ; 
 int __kernel_rem_pio2 (double*,double*,int,int,int) ; 
 double fabs (double) ; 
 scalar_t__ half ; 
 double invpio2 ; 
 int* npio2_hw ; 
 double pio2_1 ; 
 double pio2_1t ; 
 double pio2_2 ; 
 double pio2_2t ; 
 double pio2_3 ; 
 double pio2_3t ; 
 double two24 ; 
 double zero ; 

__attribute__((used)) static int
__ieee754_rem_pio2 (double x, double *y)
{
  double_accessor z;
  double w, t, r, fn;
  double tx[3];
  int e0, i, j, nx, n, ix, hx;

  hx = __HI (x); /* high word of x */
  ix = hx & 0x7fffffff;
  if (ix <= 0x3fe921fb) /* |x| ~<= pi/4 , no need for reduction */
  {
    y[0] = x;
    y[1] = 0;
    return 0;
  }
  if (ix < 0x4002d97c) /* |x| < 3pi/4, special case with n = +-1 */
  {
    if (hx > 0)
    {
      z.dbl = x - pio2_1;
      if (ix != 0x3ff921fb) /* 33 + 53 bit pi is good enough */
      {
        y[0] = z.dbl - pio2_1t;
        y[1] = (z.dbl - y[0]) - pio2_1t;
      }
      else /* near pi/2, use 33 + 33 + 53 bit pi */
      {
        z.dbl -= pio2_2;
        y[0] = z.dbl - pio2_2t;
        y[1] = (z.dbl - y[0]) - pio2_2t;
      }
      return 1;
    }
    else /* negative x */
    {
      z.dbl = x + pio2_1;
      if (ix != 0x3ff921fb) /* 33 + 53 bit pi is good enough */
      {
        y[0] = z.dbl + pio2_1t;
        y[1] = (z.dbl - y[0]) + pio2_1t;
      }
      else /* near pi/2, use 33 + 33 + 53 bit pi */
      {
        z.dbl += pio2_2;
        y[0] = z.dbl + pio2_2t;
        y[1] = (z.dbl - y[0]) + pio2_2t;
      }
      return -1;
    }
  }
  if (ix <= 0x413921fb) /* |x| ~<= 2^19 * (pi/2), medium size */
  {
    t = fabs (x);
    n = (int) (t * invpio2 + half);
    fn = (double) n;
    r = t - fn * pio2_1;
    w = fn * pio2_1t; /* 1st round good to 85 bit */
    if (n < 32 && ix != npio2_hw[n - 1])
    {
      y[0] = r - w; /* quick check no cancellation */
    }
    else
    {
      j = ix >> 20;
      y[0] = r - w;
      i = j - (((__HI (y[0])) >> 20) & 0x7ff);
      if (i > 16) /* 2nd iteration needed, good to 118 */
      {
        t = r;
        w = fn * pio2_2;
        r = t - w;
        w = fn * pio2_2t - ((t - r) - w);
        y[0] = r - w;
        i = j - (((__HI (y[0])) >> 20) & 0x7ff);
        if (i > 49) /* 3rd iteration need, 151 bits acc, will cover all possible cases */
        {
          t = r;
          w = fn * pio2_3;
          r = t - w;
          w = fn * pio2_3t - ((t - r) - w);
          y[0] = r - w;
        }
      }
    }
    y[1] = (r - y[0]) - w;
    if (hx < 0)
    {
      y[0] = -y[0];
      y[1] = -y[1];
      return -n;
    }
    else
    {
      return n;
    }
  }
  /*
   * all other (large) arguments
   */
  if (ix >= 0x7ff00000) /* x is inf or NaN */
  {
    y[0] = y[1] = x - x;
    return 0;
  }
  /* set z = scalbn(|x|, ilogb(x) - 23) */
  z.as_int.lo = __LO (x);
  e0 = (ix >> 20) - 1046; /* e0 = ilogb(z) - 23; */
  z.as_int.hi = ix - (e0 << 20);
  for (i = 0; i < 2; i++)
  {
    tx[i] = (double) ((int) (z.dbl));
    z.dbl = (z.dbl - tx[i]) * two24;
  }
  tx[2] = z.dbl;
  nx = 3;
  while (tx[nx - 1] == zero) /* skip zero term */
  {
    nx--;
  }
  n = __kernel_rem_pio2 (tx, y, e0, nx, 2);
  if (hx < 0)
  {
    y[0] = -y[0];
    y[1] = -y[1];
    return -n;
  }
  return n;
}