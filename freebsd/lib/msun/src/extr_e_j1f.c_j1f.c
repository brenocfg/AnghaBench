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
 int /*<<< orphan*/  GET_FLOAT_WORD (int,float) ; 
 float cosf (float) ; 
 float fabsf (float) ; 
 float huge ; 
 float invsqrtpi ; 
 float one ; 
 float ponef (float) ; 
 float qonef (float) ; 
 float r00 ; 
 float r01 ; 
 float r02 ; 
 float r03 ; 
 float s01 ; 
 float s02 ; 
 float s03 ; 
 float s04 ; 
 float s05 ; 
 int /*<<< orphan*/  sincosf (float,float*,float*) ; 
 float sqrtf (float) ; 
 float zero ; 

float
__ieee754_j1f(float x)
{
	float z, s,c,ss,cc,r,u,v,y;
	int32_t hx,ix;

	GET_FLOAT_WORD(hx,x);
	ix = hx&0x7fffffff;
	if(ix>=0x7f800000) return one/x;
	y = fabsf(x);
	if(ix >= 0x40000000) {	/* |x| >= 2.0 */
		sincosf(y, &s, &c);
		ss = -s-c;
		cc = s-c;
		if(ix<0x7f000000) {  /* make sure y+y not overflow */
		    z = cosf(y+y);
		    if ((s*c)>zero) cc = z/ss;
		    else 	    ss = z/cc;
		}
	/*
	 * j1(x) = 1/sqrt(pi) * (P(1,x)*cc - Q(1,x)*ss) / sqrt(x)
	 * y1(x) = 1/sqrt(pi) * (P(1,x)*ss + Q(1,x)*cc) / sqrt(x)
	 */
		if(ix>0x58000000) z = (invsqrtpi*cc)/sqrtf(y); /* |x|>2**49 */
		else {
		    u = ponef(y); v = qonef(y);
		    z = invsqrtpi*(u*cc-v*ss)/sqrtf(y);
		}
		if(hx<0) return -z;
		else  	 return  z;
	}
	if(ix<0x39000000) {	/* |x|<2**-13 */
	    if(huge+x>one) return (float)0.5*x;/* inexact if x!=0 necessary */
	}
	z = x*x;
	r =  z*(r00+z*(r01+z*(r02+z*r03)));
	s =  one+z*(s01+z*(s02+z*(s03+z*(s04+z*s05))));
	r *= x;
	return(x*(float)0.5+r/s);
}