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
typedef  int uint64_t ;
typedef  int uint16_t ;

/* Variables and functions */
 int /*<<< orphan*/  ENTERI () ; 
 int /*<<< orphan*/  EXTRACT_LDBL80_WORDS (int,int,long double) ; 
 int /*<<< orphan*/  RETURNI (long double) ; 
 int /*<<< orphan*/  a0 ; 
 int /*<<< orphan*/  a1 ; 
 int /*<<< orphan*/  a10 ; 
 int /*<<< orphan*/  a11 ; 
 long double a12 ; 
 long double a13 ; 
 int /*<<< orphan*/  a2 ; 
 int /*<<< orphan*/  a3 ; 
 int /*<<< orphan*/  a4 ; 
 int /*<<< orphan*/  a5 ; 
 int /*<<< orphan*/  a6 ; 
 int /*<<< orphan*/  a7 ; 
 int /*<<< orphan*/  a8 ; 
 int /*<<< orphan*/  a9 ; 
 long double fabsl (long double) ; 
 long double half ; 
 int logl (long double) ; 
 long double one ; 
 long double pi ; 
 long double r1 ; 
 long double r2 ; 
 long double r3 ; 
 long double r4 ; 
 long double r5 ; 
 long double r6 ; 
 long double r7 ; 
 long double s0 ; 
 long double s1 ; 
 long double s2 ; 
 long double s3 ; 
 long double s4 ; 
 long double s5 ; 
 long double s6 ; 
 long double sin_pil (long double) ; 
 int /*<<< orphan*/  t0 ; 
 long double t1 ; 
 int /*<<< orphan*/  t10 ; 
 int /*<<< orphan*/  t11 ; 
 int /*<<< orphan*/  t12 ; 
 int /*<<< orphan*/  t13 ; 
 int /*<<< orphan*/  t14 ; 
 int /*<<< orphan*/  t15 ; 
 int /*<<< orphan*/  t16 ; 
 int /*<<< orphan*/  t17 ; 
 long double t18 ; 
 int /*<<< orphan*/  t2 ; 
 int /*<<< orphan*/  t3 ; 
 int /*<<< orphan*/  t4 ; 
 int /*<<< orphan*/  t5 ; 
 int /*<<< orphan*/  t6 ; 
 int /*<<< orphan*/  t7 ; 
 int /*<<< orphan*/  t8 ; 
 int /*<<< orphan*/  t9 ; 
 int tc ; 
 int /*<<< orphan*/  tf ; 
 scalar_t__ tt ; 
 int /*<<< orphan*/  u0 ; 
 int /*<<< orphan*/  u1 ; 
 int /*<<< orphan*/  u2 ; 
 int /*<<< orphan*/  u3 ; 
 int /*<<< orphan*/  u4 ; 
 int /*<<< orphan*/  u5 ; 
 long double u6 ; 
 int /*<<< orphan*/  v1 ; 
 int /*<<< orphan*/  v2 ; 
 int /*<<< orphan*/  v3 ; 
 int /*<<< orphan*/  v4 ; 
 int /*<<< orphan*/  v5 ; 
 long double v6 ; 
 long double vzero ; 
 long double w0 ; 
 long double w1 ; 
 long double w2 ; 
 long double w3 ; 
 long double w4 ; 
 long double w5 ; 
 long double w6 ; 
 long double w7 ; 
 long double w8 ; 
 long double zero ; 

long double
lgammal_r(long double x, int *signgamp)
{
	long double nadj,p,p1,p2,q,r,t,w,y,z;
	uint64_t lx;
	int i;
	uint16_t hx,ix;

	EXTRACT_LDBL80_WORDS(hx,lx,x);

    /* purge +-Inf and NaNs */
	*signgamp = 1;
	ix = hx&0x7fff;
	if(ix==0x7fff) return x*x;

	ENTERI();

    /* purge +-0 and tiny arguments */
	*signgamp = 1-2*(hx>>15);
	if(ix<0x3fff-67) {		/* |x|<2**-(p+3), return -log(|x|) */
	    if((ix|lx)==0)
		RETURNI(one/vzero);
	    RETURNI(-logl(fabsl(x)));
	}

    /* purge negative integers and start evaluation for other x < 0 */
	if(hx&0x8000) {
	    *signgamp = 1;
	    if(ix>=0x3fff+63) 		/* |x|>=2**(p-1), must be -integer */
		RETURNI(one/vzero);
	    t = sin_pil(x);
	    if(t==zero) RETURNI(one/vzero); /* -integer */
	    nadj = logl(pi/fabsl(t*x));
	    if(t<zero) *signgamp = -1;
	    x = -x;
	}

    /* purge 1 and 2 */
	if((ix==0x3fff || ix==0x4000) && lx==0x8000000000000000ULL) r = 0;
    /* for x < 2.0 */
	else if(ix<0x4000) {
    /*
     * XXX Supposedly, one can use the following information to replace the
     * XXX FP rational expressions.  A similar approach is appropriate
     * XXX for ld128, but one (may need?) needs to consider llx, too.
     *
     * 8.9999961853027344e-01 3ffe e666600000000000
     * 7.3159980773925781e-01 3ffe bb4a200000000000
     * 2.3163998126983643e-01 3ffc ed33080000000000
     * 1.7316312789916992e+00 3fff dda6180000000000
     * 1.2316322326660156e+00 3fff 9da6200000000000
     */
	    if(x<8.9999961853027344e-01) {
		r = -logl(x);
		if(x>=7.3159980773925781e-01) {y = 1-x; i= 0;}
		else if(x>=2.3163998126983643e-01) {y= x-(tc-1); i=1;}
		else {y = x; i=2;}
	    } else {
		r = 0;
		if(x>=1.7316312789916992e+00) {y=2-x;i=0;}
		else if(x>=1.2316322326660156e+00) {y=x-tc;i=1;}
		else {y=x-1;i=2;}
	    }
	    switch(i) {
	      case 0:
		z = y*y;
		p1 = a0+z*(a2+z*(a4+z*(a6+z*(a8+z*(a10+z*a12)))));
		p2 = z*(a1+z*(a3+z*(a5+z*(a7+z*(a9+z*(a11+z*a13))))));
		p  = y*p1+p2;
		r  += p-y/2; break;
	      case 1:
		p = t0+y*t1+tt+y*y*(t2+y*(t3+y*(t4+y*(t5+y*(t6+y*(t7+y*(t8+
		    y*(t9+y*(t10+y*(t11+y*(t12+y*(t13+y*(t14+y*(t15+y*(t16+
		    y*(t17+y*t18))))))))))))))));
		r += tf + p; break;
	      case 2:
		p1 = y*(u0+y*(u1+y*(u2+y*(u3+y*(u4+y*(u5+y*u6))))));
		p2 = 1+y*(v1+y*(v2+y*(v3+y*(v4+y*(v5+y*v6)))));
		r += p1/p2-y/2;
	    }
	}
    /* x < 8.0 */
	else if(ix<0x4002) {
	    i = x;
	    y = x-i;
	    p = y*(s0+y*(s1+y*(s2+y*(s3+y*(s4+y*(s5+y*s6))))));
	    q = 1+y*(r1+y*(r2+y*(r3+y*(r4+y*(r5+y*(r6+y*r7))))));
	    r = y/2+p/q;
	    z = 1;	/* lgamma(1+s) = log(s) + lgamma(s) */
	    switch(i) {
	    case 7: z *= (y+6);		/* FALLTHRU */
	    case 6: z *= (y+5);		/* FALLTHRU */
	    case 5: z *= (y+4);		/* FALLTHRU */
	    case 4: z *= (y+3);		/* FALLTHRU */
	    case 3: z *= (y+2);		/* FALLTHRU */
		    r += logl(z); break;
	    }
    /* 8.0 <= x < 2**(p+3) */
	} else if (ix<0x3fff+67) {
	    t = logl(x);
	    z = one/x;
	    y = z*z;
	    w = w0+z*(w1+y*(w2+y*(w3+y*(w4+y*(w5+y*(w6+y*(w7+y*w8)))))));
	    r = (x-half)*(t-one)+w;
    /* 2**(p+3) <= x <= inf */
	} else 
	    r =  x*(logl(x)-1);
	if(hx&0x8000) r = nadj - r;
	RETURNI(r);
}