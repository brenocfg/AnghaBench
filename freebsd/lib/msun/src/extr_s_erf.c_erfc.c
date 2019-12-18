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
typedef  int u_int32_t ;
typedef  int int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  GET_HIGH_WORD (int,double) ; 
 int /*<<< orphan*/  SET_LOW_WORD (double,int /*<<< orphan*/ ) ; 
 double __ieee754_exp (double) ; 
 double erx ; 
 double fabs (double) ; 
 double half ; 
 double one ; 
 double pa0 ; 
 double pa1 ; 
 double pa2 ; 
 double pa3 ; 
 double pa4 ; 
 double pa5 ; 
 double pa6 ; 
 double pp0 ; 
 double pp1 ; 
 double pp2 ; 
 double pp3 ; 
 double pp4 ; 
 double qa1 ; 
 double qa2 ; 
 double qa3 ; 
 double qa4 ; 
 double qa5 ; 
 double qa6 ; 
 double qq1 ; 
 double qq2 ; 
 double qq3 ; 
 double qq4 ; 
 double qq5 ; 
 double ra0 ; 
 double ra1 ; 
 double ra2 ; 
 double ra3 ; 
 double ra4 ; 
 double ra5 ; 
 double ra6 ; 
 double ra7 ; 
 double rb0 ; 
 double rb1 ; 
 double rb2 ; 
 double rb3 ; 
 double rb4 ; 
 double rb5 ; 
 double rb6 ; 
 double sa1 ; 
 double sa2 ; 
 double sa3 ; 
 double sa4 ; 
 double sa5 ; 
 double sa6 ; 
 double sa7 ; 
 double sa8 ; 
 double sb1 ; 
 double sb2 ; 
 double sb3 ; 
 double sb4 ; 
 double sb5 ; 
 double sb6 ; 
 double sb7 ; 
 double tiny ; 
 double two ; 

double
erfc(double x)
{
	int32_t hx,ix;
	double R,S,P,Q,s,y,z,r;
	GET_HIGH_WORD(hx,x);
	ix = hx&0x7fffffff;
	if(ix>=0x7ff00000) {			/* erfc(nan)=nan */
						/* erfc(+-inf)=0,2 */
	    return (double)(((u_int32_t)hx>>31)<<1)+one/x;
	}

	if(ix < 0x3feb0000) {		/* |x|<0.84375 */
	    if(ix < 0x3c700000)  	/* |x|<2**-56 */
		return one-x;
	    z = x*x;
	    r = pp0+z*(pp1+z*(pp2+z*(pp3+z*pp4)));
	    s = one+z*(qq1+z*(qq2+z*(qq3+z*(qq4+z*qq5))));
	    y = r/s;
	    if(hx < 0x3fd00000) {  	/* x<1/4 */
		return one-(x+x*y);
	    } else {
		r = x*y;
		r += (x-half);
	        return half - r ;
	    }
	}
	if(ix < 0x3ff40000) {		/* 0.84375 <= |x| < 1.25 */
	    s = fabs(x)-one;
	    P = pa0+s*(pa1+s*(pa2+s*(pa3+s*(pa4+s*(pa5+s*pa6)))));
	    Q = one+s*(qa1+s*(qa2+s*(qa3+s*(qa4+s*(qa5+s*qa6)))));
	    if(hx>=0) {
	        z  = one-erx; return z - P/Q;
	    } else {
		z = erx+P/Q; return one+z;
	    }
	}
	if (ix < 0x403c0000) {		/* |x|<28 */
	    x = fabs(x);
 	    s = one/(x*x);
	    if(ix< 0x4006DB6D) {	/* |x| < 1/.35 ~ 2.857143*/
		R=ra0+s*(ra1+s*(ra2+s*(ra3+s*(ra4+s*(ra5+s*(ra6+s*ra7))))));
		S=one+s*(sa1+s*(sa2+s*(sa3+s*(sa4+s*(sa5+s*(sa6+s*(sa7+
		    s*sa8)))))));
	    } else {			/* |x| >= 1/.35 ~ 2.857143 */
		if(hx<0&&ix>=0x40180000) return two-tiny;/* x < -6 */
		R=rb0+s*(rb1+s*(rb2+s*(rb3+s*(rb4+s*(rb5+s*rb6)))));
		S=one+s*(sb1+s*(sb2+s*(sb3+s*(sb4+s*(sb5+s*(sb6+s*sb7))))));
	    }
	    z  = x;
	    SET_LOW_WORD(z,0);
	    r  =  __ieee754_exp(-z*z-0.5625)*__ieee754_exp((z-x)*(z+x)+R/S);
	    if(hx>0) return r/x; else return two-r/x;
	} else {
	    if(hx>0) return tiny*tiny; else return two-tiny;
	}
}