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
 int /*<<< orphan*/  GET_FLOAT_WORD (int,float) ; 
 float __ieee754_logf (float) ; 
 int /*<<< orphan*/  a0 ; 
 int /*<<< orphan*/  a1 ; 
 int /*<<< orphan*/  a2 ; 
 int /*<<< orphan*/  a3 ; 
 float a4 ; 
 float a5 ; 
 float fabsf (float) ; 
 float half ; 
 float one ; 
 float pi ; 
 float r1 ; 
 float r2 ; 
 float r3 ; 
 float s0 ; 
 float s1 ; 
 float s2 ; 
 float s3 ; 
 float sin_pif (float) ; 
 int /*<<< orphan*/  t0 ; 
 float t1 ; 
 int /*<<< orphan*/  t2 ; 
 int /*<<< orphan*/  t3 ; 
 int /*<<< orphan*/  t4 ; 
 int /*<<< orphan*/  t5 ; 
 int /*<<< orphan*/  t6 ; 
 float t7 ; 
 float tc ; 
 int /*<<< orphan*/  tf ; 
 int /*<<< orphan*/  u0 ; 
 int /*<<< orphan*/  u1 ; 
 float u2 ; 
 int /*<<< orphan*/  v1 ; 
 int /*<<< orphan*/  v2 ; 
 float v3 ; 
 float vzero ; 
 float w0 ; 
 float w1 ; 
 float w2 ; 
 float zero ; 

float
__ieee754_lgammaf_r(float x, int *signgamp)
{
	float nadj,p,p1,p2,q,r,t,w,y,z;
	int32_t hx;
	int i,ix;

	GET_FLOAT_WORD(hx,x);

    /* purge +-Inf and NaNs */
	*signgamp = 1;
	ix = hx&0x7fffffff;
	if(ix>=0x7f800000) return x*x;

    /* purge +-0 and tiny arguments */
	*signgamp = 1-2*((uint32_t)hx>>31);
	if(ix<0x32000000) {		/* |x|<2**-27, return -log(|x|) */
	    if(ix==0)
	        return one/vzero;
	    return -__ieee754_logf(fabsf(x));
	}

    /* purge negative integers and start evaluation for other x < 0 */
	if(hx<0) {
	    *signgamp = 1;
	    if(ix>=0x4b000000) 		/* |x|>=2**23, must be -integer */
		return one/vzero;
	    t = sin_pif(x);
	    if(t==zero) return one/vzero; /* -integer */
	    nadj = __ieee754_logf(pi/fabsf(t*x));
	    if(t<zero) *signgamp = -1;
	    x = -x;
	}

    /* purge 1 and 2 */
	if (ix==0x3f800000||ix==0x40000000) r = 0;
    /* for x < 2.0 */
	else if(ix<0x40000000) {
	    if(ix<=0x3f666666) { 	/* lgamma(x) = lgamma(x+1)-log(x) */
		r = -__ieee754_logf(x);
		if(ix>=0x3f3b4a20) {y = one-x; i= 0;}
		else if(ix>=0x3e6d3308) {y= x-(tc-one); i=1;}
	  	else {y = x; i=2;}
	    } else {
	  	r = zero;
	        if(ix>=0x3fdda618) {y=2-x;i=0;} /* [1.7316,2] */
	        else if(ix>=0x3F9da620) {y=x-tc;i=1;} /* [1.23,1.73] */
		else {y=x-one;i=2;}
	    }
	    switch(i) {
	      case 0:
		z = y*y;
		p1 = a0+z*(a2+z*a4);
		p2 = z*(a1+z*(a3+z*a5));
		p  = y*p1+p2;
		r  += p-y/2; break;
	      case 1:
		p = t0+y*t1+y*y*(t2+y*(t3+y*(t4+y*(t5+y*(t6+y*t7)))));
		r += tf + p; break;
	      case 2:
		p1 = y*(u0+y*(u1+y*u2));
		p2 = one+y*(v1+y*(v2+y*v3));
		r += p1/p2-y/2;
	    }
	}
    /* x < 8.0 */
	else if(ix<0x41000000) {
	    i = x;
	    y = x-i;
	    p = y*(s0+y*(s1+y*(s2+y*s3)));
	    q = one+y*(r1+y*(r2+y*r3));
	    r = y/2+p/q;
	    z = one;	/* lgamma(1+s) = log(s) + lgamma(s) */
	    switch(i) {
	    case 7: z *= (y+6);		/* FALLTHRU */
	    case 6: z *= (y+5);		/* FALLTHRU */
	    case 5: z *= (y+4);		/* FALLTHRU */
	    case 4: z *= (y+3);		/* FALLTHRU */
	    case 3: z *= (y+2);		/* FALLTHRU */
		    r += __ieee754_logf(z); break;
	    }
    /* 8.0 <= x < 2**27 */
	} else if (ix < 0x4d000000) {
	    t = __ieee754_logf(x);
	    z = one/x;
	    y = z*z;
	    w = w0+z*(w1+y*w2);
	    r = (x-half)*(t-one)+w;
	} else
    /* 2**27 <= x <= inf */
	    r =  x*(__ieee754_logf(x)-one);
	if(hx<0) r = nadj - r;
	return r;
}