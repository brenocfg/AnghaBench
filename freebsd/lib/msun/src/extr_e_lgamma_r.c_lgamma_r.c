#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int uint32_t ;
typedef  int int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  EXTRACT_WORDS (int,int,double) ; 
 double __ieee754_log (double) ; 
 int /*<<< orphan*/  a0 ; 
 int /*<<< orphan*/  a1 ; 
 double a10 ; 
 double a11 ; 
 int /*<<< orphan*/  a2 ; 
 int /*<<< orphan*/  a3 ; 
 int /*<<< orphan*/  a4 ; 
 int /*<<< orphan*/  a5 ; 
 int /*<<< orphan*/  a6 ; 
 int /*<<< orphan*/  a7 ; 
 int /*<<< orphan*/  a8 ; 
 int /*<<< orphan*/  a9 ; 
 double fabs (double) ; 
 double half ; 
 double one ; 
 double pi ; 
 double r1 ; 
 double r2 ; 
 double r3 ; 
 double r4 ; 
 double r5 ; 
 double r6 ; 
 double s0 ; 
 double s1 ; 
 double s2 ; 
 double s3 ; 
 double s4 ; 
 double s5 ; 
 double s6 ; 
 double sin_pi (double) ; 
 int /*<<< orphan*/  t0 ; 
 int /*<<< orphan*/  t1 ; 
 int /*<<< orphan*/  t10 ; 
 int /*<<< orphan*/  t11 ; 
 double t12 ; 
 double t13 ; 
 double t14 ; 
 int /*<<< orphan*/  t2 ; 
 int /*<<< orphan*/  t3 ; 
 int /*<<< orphan*/  t4 ; 
 int /*<<< orphan*/  t5 ; 
 int /*<<< orphan*/  t6 ; 
 int /*<<< orphan*/  t7 ; 
 int /*<<< orphan*/  t8 ; 
 int /*<<< orphan*/  t9 ; 
 double tc ; 
 int /*<<< orphan*/  tf ; 
 int /*<<< orphan*/  tt ; 
 int /*<<< orphan*/  u0 ; 
 int /*<<< orphan*/  u1 ; 
 int /*<<< orphan*/  u2 ; 
 int /*<<< orphan*/  u3 ; 
 int /*<<< orphan*/  u4 ; 
 double u5 ; 
 int /*<<< orphan*/  v1 ; 
 int /*<<< orphan*/  v2 ; 
 int /*<<< orphan*/  v3 ; 
 int /*<<< orphan*/  v4 ; 
 double v5 ; 
 double vzero ; 
 double w0 ; 
 double w1 ; 
 double w2 ; 
 double w3 ; 
 double w4 ; 
 double w5 ; 
 double w6 ; 
 double zero ; 

double
__ieee754_lgamma_r(double x, int *signgamp)
{
	double nadj,p,p1,p2,p3,q,r,t,w,y,z;
	int32_t hx;
	int i,ix,lx;

	EXTRACT_WORDS(hx,lx,x);

    /* purge +-Inf and NaNs */
	*signgamp = 1;
	ix = hx&0x7fffffff;
	if(ix>=0x7ff00000) return x*x;

    /* purge +-0 and tiny arguments */
	*signgamp = 1-2*((uint32_t)hx>>31);
	if(ix<0x3c700000) {	/* |x|<2**-56, return -log(|x|) */
	    if((ix|lx)==0)
	        return one/vzero;
	    return -__ieee754_log(fabs(x));
	}

    /* purge negative integers and start evaluation for other x < 0 */
	if(hx<0) {
	    *signgamp = 1;
	    if(ix>=0x43300000) 	/* |x|>=2**52, must be -integer */
		return one/vzero;
	    t = sin_pi(x);
	    if(t==zero) return one/vzero; /* -integer */
	    nadj = __ieee754_log(pi/fabs(t*x));
	    if(t<zero) *signgamp = -1;
	    x = -x;
	}

    /* purge 1 and 2 */
	if((((ix-0x3ff00000)|lx)==0)||(((ix-0x40000000)|lx)==0)) r = 0;
    /* for x < 2.0 */
	else if(ix<0x40000000) {
	    if(ix<=0x3feccccc) { 	/* lgamma(x) = lgamma(x+1)-log(x) */
		r = -__ieee754_log(x);
		if(ix>=0x3FE76944) {y = one-x; i= 0;}
		else if(ix>=0x3FCDA661) {y= x-(tc-one); i=1;}
	  	else {y = x; i=2;}
	    } else {
	  	r = zero;
	        if(ix>=0x3FFBB4C3) {y=2.0-x;i=0;} /* [1.7316,2] */
	        else if(ix>=0x3FF3B4C4) {y=x-tc;i=1;} /* [1.23,1.73] */
		else {y=x-one;i=2;}
	    }
	    switch(i) {
	      case 0:
		z = y*y;
		p1 = a0+z*(a2+z*(a4+z*(a6+z*(a8+z*a10))));
		p2 = z*(a1+z*(a3+z*(a5+z*(a7+z*(a9+z*a11)))));
		p  = y*p1+p2;
		r  += p-y/2; break;
	      case 1:
		z = y*y;
		w = z*y;
		p1 = t0+w*(t3+w*(t6+w*(t9 +w*t12)));	/* parallel comp */
		p2 = t1+w*(t4+w*(t7+w*(t10+w*t13)));
		p3 = t2+w*(t5+w*(t8+w*(t11+w*t14)));
		p  = z*p1-(tt-w*(p2+y*p3));
		r += tf + p; break;
	      case 2:
		p1 = y*(u0+y*(u1+y*(u2+y*(u3+y*(u4+y*u5)))));
		p2 = one+y*(v1+y*(v2+y*(v3+y*(v4+y*v5))));
		r += p1/p2-y/2;
	    }
	}
    /* x < 8.0 */
	else if(ix<0x40200000) {
	    i = x;
	    y = x-i;
	    p = y*(s0+y*(s1+y*(s2+y*(s3+y*(s4+y*(s5+y*s6))))));
	    q = one+y*(r1+y*(r2+y*(r3+y*(r4+y*(r5+y*r6)))));
	    r = y/2+p/q;
	    z = one;	/* lgamma(1+s) = log(s) + lgamma(s) */
	    switch(i) {
	    case 7: z *= (y+6);		/* FALLTHRU */
	    case 6: z *= (y+5);		/* FALLTHRU */
	    case 5: z *= (y+4);		/* FALLTHRU */
	    case 4: z *= (y+3);		/* FALLTHRU */
	    case 3: z *= (y+2);		/* FALLTHRU */
		    r += __ieee754_log(z); break;
	    }
    /* 8.0 <= x < 2**56 */
	} else if (ix < 0x43700000) {
	    t = __ieee754_log(x);
	    z = one/x;
	    y = z*z;
	    w = w0+z*(w1+y*(w2+y*(w3+y*(w4+y*(w5+y*w6)))));
	    r = (x-half)*(t-one)+w;
	} else
    /* 2**56 <= x <= inf */
	    r =  x*(__ieee754_log(x)-one);
	if(hx<0) r = nadj - r;
	return r;
}