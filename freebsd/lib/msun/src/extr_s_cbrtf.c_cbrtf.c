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
 int B1 ; 
 int B2 ; 
 int /*<<< orphan*/  GET_FLOAT_WORD (int,float) ; 
 int /*<<< orphan*/  SET_FLOAT_WORD (float,int) ; 

float
cbrtf(float x)
{
	double r,T;
	float t;
	int32_t hx;
	u_int32_t sign;
	u_int32_t high;

	GET_FLOAT_WORD(hx,x);
	sign=hx&0x80000000; 		/* sign= sign(x) */
	hx  ^=sign;
	if(hx>=0x7f800000) return(x+x); /* cbrt(NaN,INF) is itself */

    /* rough cbrt to 5 bits */
	if(hx<0x00800000) { 		/* zero or subnormal? */
	    if(hx==0)
		return(x);		/* cbrt(+-0) is itself */
	    SET_FLOAT_WORD(t,0x4b800000); /* set t= 2**24 */
	    t*=x;
	    GET_FLOAT_WORD(high,t);
	    SET_FLOAT_WORD(t,sign|((high&0x7fffffff)/3+B2));
	} else
	    SET_FLOAT_WORD(t,sign|(hx/3+B1));

    /*
     * First step Newton iteration (solving t*t-x/t == 0) to 16 bits.  In
     * double precision so that its terms can be arranged for efficiency
     * without causing overflow or underflow.
     */
	T=t;
	r=T*T*T;
	T=T*((double)x+x+r)/(x+r+r);

    /*
     * Second step Newton iteration to 47 bits.  In double precision for
     * efficiency and accuracy.
     */
	r=T*T*T;
	T=T*((double)x+x+r)/(x+r+r);

    /* rounding to 24 bits is perfect in round-to-nearest mode */
	return(T);
}