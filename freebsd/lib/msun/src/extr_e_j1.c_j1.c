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
typedef  int int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  GET_HIGH_WORD (int,double) ; 
 double cos (double) ; 
 double fabs (double) ; 
 double huge ; 
 double invsqrtpi ; 
 double one ; 
 double pone (double) ; 
 double qone (double) ; 
 double r00 ; 
 double r01 ; 
 double r02 ; 
 double r03 ; 
 double s01 ; 
 double s02 ; 
 double s03 ; 
 double s04 ; 
 double s05 ; 
 int /*<<< orphan*/  sincos (double,double*,double*) ; 
 double sqrt (double) ; 
 double zero ; 

double
__ieee754_j1(double x)
{
	double z, s,c,ss,cc,r,u,v,y;
	int32_t hx,ix;

	GET_HIGH_WORD(hx,x);
	ix = hx&0x7fffffff;
	if(ix>=0x7ff00000) return one/x;
	y = fabs(x);
	if(ix >= 0x40000000) {	/* |x| >= 2.0 */
		sincos(y, &s, &c);
		ss = -s-c;
		cc = s-c;
		if(ix<0x7fe00000) {  /* make sure y+y not overflow */
		    z = cos(y+y);
		    if ((s*c)>zero) cc = z/ss;
		    else 	    ss = z/cc;
		}
	/*
	 * j1(x) = 1/sqrt(pi) * (P(1,x)*cc - Q(1,x)*ss) / sqrt(x)
	 * y1(x) = 1/sqrt(pi) * (P(1,x)*ss + Q(1,x)*cc) / sqrt(x)
	 */
		if(ix>0x48000000) z = (invsqrtpi*cc)/sqrt(y);
		else {
		    u = pone(y); v = qone(y);
		    z = invsqrtpi*(u*cc-v*ss)/sqrt(y);
		}
		if(hx<0) return -z;
		else  	 return  z;
	}
	if(ix<0x3e400000) {	/* |x|<2**-27 */
	    if(huge+x>one) return 0.5*x;/* inexact if x!=0 necessary */
	}
	z = x*x;
	r =  z*(r00+z*(r01+z*(r02+z*r03)));
	s =  one+z*(s01+z*(s02+z*(s03+z*(s04+z*s05))));
	r *= x;
	return(x*0.5+r/s);
}