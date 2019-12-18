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
 float one ; 
 float* pr2 ; 
 float* pr3 ; 
 float* pr5 ; 
 float* pr8 ; 
 float* ps2 ; 
 float* ps3 ; 
 float* ps5 ; 
 float* ps8 ; 

__attribute__((used)) static __inline float
ponef(float x)
{
	const float *p,*q;
	float z,r,s;
        int32_t ix;
	GET_FLOAT_WORD(ix,x);
	ix &= 0x7fffffff;
        if(ix>=0x41000000)     {p = pr8; q= ps8;}
        else if(ix>=0x409173eb){p = pr5; q= ps5;}
        else if(ix>=0x4036d917){p = pr3; q= ps3;}
	else                   {p = pr2; q= ps2;}	/* ix>=0x40000000 */
        z = one/(x*x);
        r = p[0]+z*(p[1]+z*(p[2]+z*(p[3]+z*(p[4]+z*p[5]))));
        s = one+z*(q[0]+z*(q[1]+z*(q[2]+z*(q[3]+z*q[4]))));
        return one+ r/s;
}