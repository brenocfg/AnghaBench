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
 float __ieee754_y0f (float) ; 
 int __ieee754_y1f (float) ; 
 float one ; 
 float vzero ; 
 float zero ; 

float
__ieee754_ynf(int n, float x)
{
	int32_t i,hx,ix,ib;
	int32_t sign;
	float a, b, temp;

	GET_FLOAT_WORD(hx,x);
	ix = 0x7fffffff&hx;
	if(ix>0x7f800000) return x+x;
	if(ix==0) return -one/vzero;
	if(hx<0) return vzero/vzero;
	sign = 1;
	if(n<0){
		n = -n;
		sign = 1 - ((n&1)<<1);
	}
	if(n==0) return(__ieee754_y0f(x));
	if(n==1) return(sign*__ieee754_y1f(x));
	if(ix==0x7f800000) return zero;

	a = __ieee754_y0f(x);
	b = __ieee754_y1f(x);
	/* quit if b is -inf */
	GET_FLOAT_WORD(ib,b);
	for(i=1;i<n&&ib!=0xff800000;i++){
	    temp = b;
	    b = ((float)(i+i)/x)*b - a;
	    GET_FLOAT_WORD(ib,b);
	    a = temp;
	}
	if(sign>0) return b; else return -b;
}