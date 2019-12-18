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
typedef  int u_int32_t ;
typedef  int int32_t ;
struct TYPE_3__ {int mswhi; int mswlo; int lswhi; int lswlo; } ;
struct TYPE_4__ {long double value; TYPE_1__ parts32; } ;
typedef  TYPE_2__ ieee_quad_shape_type ;

/* Variables and functions */
 long double* LD ; 
 long double* LN ; 
 long double* PD ; 
 long double* PN ; 
 long double* bp ; 
 long double cp ; 
 long double cp_h ; 
 long double cp_l ; 
 long double* dp_h ; 
 long double* dp_l ; 
 long double fabsl (long double) ; 
 long double floorl (long double) ; 
 long double huge ; 
 long double lg2 ; 
 long double lg2_h ; 
 long double lg2_l ; 
 long double nan_mix (long double,long double) ; 
 long double one ; 
 long double ovt ; 
 long double scalbnl (long double,int) ; 
 long double sqrtl (long double) ; 
 long double tiny ; 
 long double two ; 
 long double two113 ; 
 long double zero ; 

long double
powl(long double x, long double y)
{
  long double z, ax, z_h, z_l, p_h, p_l;
  long double yy1, t1, t2, r, s, t, u, v, w;
  long double s2, s_h, s_l, t_h, t_l;
  int32_t i, j, k, yisint, n;
  u_int32_t ix, iy;
  int32_t hx, hy;
  ieee_quad_shape_type o, p, q;

  p.value = x;
  hx = p.parts32.mswhi;
  ix = hx & 0x7fffffff;

  q.value = y;
  hy = q.parts32.mswhi;
  iy = hy & 0x7fffffff;


  /* y==zero: x**0 = 1 */
  if ((iy | q.parts32.mswlo | q.parts32.lswhi | q.parts32.lswlo) == 0)
    return one;

  /* 1.0**y = 1; -1.0**+-Inf = 1 */
  if (x == one)
    return one;
  if (x == -1.0L && iy == 0x7fff0000
      && (q.parts32.mswlo | q.parts32.lswhi | q.parts32.lswlo) == 0)
    return one;

  /* +-NaN return x+y */
  if ((ix > 0x7fff0000)
      || ((ix == 0x7fff0000)
	  && ((p.parts32.mswlo | p.parts32.lswhi | p.parts32.lswlo) != 0))
      || (iy > 0x7fff0000)
      || ((iy == 0x7fff0000)
	  && ((q.parts32.mswlo | q.parts32.lswhi | q.parts32.lswlo) != 0)))
    return nan_mix(x, y);

  /* determine if y is an odd int when x < 0
   * yisint = 0       ... y is not an integer
   * yisint = 1       ... y is an odd int
   * yisint = 2       ... y is an even int
   */
  yisint = 0;
  if (hx < 0)
    {
      if (iy >= 0x40700000)	/* 2^113 */
	yisint = 2;		/* even integer y */
      else if (iy >= 0x3fff0000)	/* 1.0 */
	{
	  if (floorl (y) == y)
	    {
	      z = 0.5 * y;
	      if (floorl (z) == z)
		yisint = 2;
	      else
		yisint = 1;
	    }
	}
    }

  /* special value of y */
  if ((q.parts32.mswlo | q.parts32.lswhi | q.parts32.lswlo) == 0)
    {
      if (iy == 0x7fff0000)	/* y is +-inf */
	{
	  if (((ix - 0x3fff0000) | p.parts32.mswlo | p.parts32.lswhi |
	    p.parts32.lswlo) == 0)
	    return y - y;	/* +-1**inf is NaN */
	  else if (ix >= 0x3fff0000)	/* (|x|>1)**+-inf = inf,0 */
	    return (hy >= 0) ? y : zero;
	  else			/* (|x|<1)**-,+inf = inf,0 */
	    return (hy < 0) ? -y : zero;
	}
      if (iy == 0x3fff0000)
	{			/* y is  +-1 */
	  if (hy < 0)
	    return one / x;
	  else
	    return x;
	}
      if (hy == 0x40000000)
	return x * x;		/* y is  2 */
      if (hy == 0x3ffe0000)
	{			/* y is  0.5 */
	  if (hx >= 0)		/* x >= +0 */
	    return sqrtl (x);
	}
    }

  ax = fabsl (x);
  /* special value of x */
  if ((p.parts32.mswlo | p.parts32.lswhi | p.parts32.lswlo) == 0)
    {
      if (ix == 0x7fff0000 || ix == 0 || ix == 0x3fff0000)
	{
	  z = ax;		/*x is +-0,+-inf,+-1 */
	  if (hy < 0)
	    z = one / z;	/* z = (1/|x|) */
	  if (hx < 0)
	    {
	      if (((ix - 0x3fff0000) | yisint) == 0)
		{
		  z = (z - z) / (z - z);	/* (-1)**non-int is NaN */
		}
	      else if (yisint == 1)
		z = -z;		/* (x<0)**odd = -(|x|**odd) */
	    }
	  return z;
	}
    }

  /* (x<0)**(non-int) is NaN */
  if (((((u_int32_t) hx >> 31) - 1) | yisint) == 0)
    return (x - x) / (x - x);

  /* |y| is huge.
     2^-16495 = 1/2 of smallest representable value.
     If (1 - 1/131072)^y underflows, y > 1.4986e9 */
  if (iy > 0x401d654b)
    {
      /* if (1 - 2^-113)^y underflows, y > 1.1873e38 */
      if (iy > 0x407d654b)
	{
	  if (ix <= 0x3ffeffff)
	    return (hy < 0) ? huge * huge : tiny * tiny;
	  if (ix >= 0x3fff0000)
	    return (hy > 0) ? huge * huge : tiny * tiny;
	}
      /* over/underflow if x is not close to one */
      if (ix < 0x3ffeffff)
	return (hy < 0) ? huge * huge : tiny * tiny;
      if (ix > 0x3fff0000)
	return (hy > 0) ? huge * huge : tiny * tiny;
    }

  n = 0;
  /* take care subnormal number */
  if (ix < 0x00010000)
    {
      ax *= two113;
      n -= 113;
      o.value = ax;
      ix = o.parts32.mswhi;
    }
  n += ((ix) >> 16) - 0x3fff;
  j = ix & 0x0000ffff;
  /* determine interval */
  ix = j | 0x3fff0000;		/* normalize ix */
  if (j <= 0x3988)
    k = 0;			/* |x|<sqrt(3/2) */
  else if (j < 0xbb67)
    k = 1;			/* |x|<sqrt(3)   */
  else
    {
      k = 0;
      n += 1;
      ix -= 0x00010000;
    }

  o.value = ax;
  o.parts32.mswhi = ix;
  ax = o.value;

  /* compute s = s_h+s_l = (x-1)/(x+1) or (x-1.5)/(x+1.5) */
  u = ax - bp[k];		/* bp[0]=1.0, bp[1]=1.5 */
  v = one / (ax + bp[k]);
  s = u * v;
  s_h = s;

  o.value = s_h;
  o.parts32.lswlo = 0;
  o.parts32.lswhi &= 0xf8000000;
  s_h = o.value;
  /* t_h=ax+bp[k] High */
  t_h = ax + bp[k];
  o.value = t_h;
  o.parts32.lswlo = 0;
  o.parts32.lswhi &= 0xf8000000;
  t_h = o.value;
  t_l = ax - (t_h - bp[k]);
  s_l = v * ((u - s_h * t_h) - s_h * t_l);
  /* compute log(ax) */
  s2 = s * s;
  u = LN[0] + s2 * (LN[1] + s2 * (LN[2] + s2 * (LN[3] + s2 * LN[4])));
  v = LD[0] + s2 * (LD[1] + s2 * (LD[2] + s2 * (LD[3] + s2 * (LD[4] + s2))));
  r = s2 * s2 * u / v;
  r += s_l * (s_h + s);
  s2 = s_h * s_h;
  t_h = 3.0 + s2 + r;
  o.value = t_h;
  o.parts32.lswlo = 0;
  o.parts32.lswhi &= 0xf8000000;
  t_h = o.value;
  t_l = r - ((t_h - 3.0) - s2);
  /* u+v = s*(1+...) */
  u = s_h * t_h;
  v = s_l * t_h + t_l * s;
  /* 2/(3log2)*(s+...) */
  p_h = u + v;
  o.value = p_h;
  o.parts32.lswlo = 0;
  o.parts32.lswhi &= 0xf8000000;
  p_h = o.value;
  p_l = v - (p_h - u);
  z_h = cp_h * p_h;		/* cp_h+cp_l = 2/(3*log2) */
  z_l = cp_l * p_h + p_l * cp + dp_l[k];
  /* log2(ax) = (s+..)*2/(3*log2) = n + dp_h + z_h + z_l */
  t = (long double) n;
  t1 = (((z_h + z_l) + dp_h[k]) + t);
  o.value = t1;
  o.parts32.lswlo = 0;
  o.parts32.lswhi &= 0xf8000000;
  t1 = o.value;
  t2 = z_l - (((t1 - t) - dp_h[k]) - z_h);

  /* s (sign of result -ve**odd) = -1 else = 1 */
  s = one;
  if (((((u_int32_t) hx >> 31) - 1) | (yisint - 1)) == 0)
    s = -one;			/* (-ve)**(odd int) */

  /* split up y into yy1+y2 and compute (yy1+y2)*(t1+t2) */
  yy1 = y;
  o.value = yy1;
  o.parts32.lswlo = 0;
  o.parts32.lswhi &= 0xf8000000;
  yy1 = o.value;
  p_l = (y - yy1) * t1 + y * t2;
  p_h = yy1 * t1;
  z = p_l + p_h;
  o.value = z;
  j = o.parts32.mswhi;
  if (j >= 0x400d0000) /* z >= 16384 */
    {
      /* if z > 16384 */
      if (((j - 0x400d0000) | o.parts32.mswlo | o.parts32.lswhi |
	o.parts32.lswlo) != 0)
	return s * huge * huge;	/* overflow */
      else
	{
	  if (p_l + ovt > z - p_h)
	    return s * huge * huge;	/* overflow */
	}
    }
  else if ((j & 0x7fffffff) >= 0x400d01b9)	/* z <= -16495 */
    {
      /* z < -16495 */
      if (((j - 0xc00d01bc) | o.parts32.mswlo | o.parts32.lswhi |
	o.parts32.lswlo)
	  != 0)
	return s * tiny * tiny;	/* underflow */
      else
	{
	  if (p_l <= z - p_h)
	    return s * tiny * tiny;	/* underflow */
	}
    }
  /* compute 2**(p_h+p_l) */
  i = j & 0x7fffffff;
  k = (i >> 16) - 0x3fff;
  n = 0;
  if (i > 0x3ffe0000)
    {				/* if |z| > 0.5, set n = [z+0.5] */
      n = floorl (z + 0.5L);
      t = n;
      p_h -= t;
    }
  t = p_l + p_h;
  o.value = t;
  o.parts32.lswlo = 0;
  o.parts32.lswhi &= 0xf8000000;
  t = o.value;
  u = t * lg2_h;
  v = (p_l - (t - p_h)) * lg2 + t * lg2_l;
  z = u + v;
  w = v - (z - u);
  /*  exp(z) */
  t = z * z;
  u = PN[0] + t * (PN[1] + t * (PN[2] + t * (PN[3] + t * PN[4])));
  v = PD[0] + t * (PD[1] + t * (PD[2] + t * (PD[3] + t)));
  t1 = z - t * u / v;
  r = (z * t1) / (t1 - two) - (w + z * w);
  z = one - (r - z);
  o.value = z;
  j = o.parts32.mswhi;
  j += (n << 16);
  if ((j >> 16) <= 0)
    z = scalbnl (z, n);	/* subnormal output */
  else
    {
      o.parts32.mswhi = j;
      z = o.value;
    }
  return s * z;
}