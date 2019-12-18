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
 float* qr2 ; 
 float* qr3 ; 
 float* qr5 ; 
 float* qr8 ; 
 float* qs2 ; 
 float* qs3 ; 
 float* qs5 ; 
 float* qs8 ; 

__attribute__((used)) static __inline float
qonef(float x)
{
	const float *p,*q;
	float  s,r,z;
	int32_t ix;
	GET_FLOAT_WORD(ix,x);
	ix &= 0x7fffffff;
	if(ix>=0x41000000)     {p = qr8; q= qs8;}
	else if(ix>=0x409173eb){p = qr5; q= qs5;}
	else if(ix>=0x4036d917){p = qr3; q= qs3;}
	else                   {p = qr2; q= qs2;}	/* ix>=0x40000000 */
	z = one/(x*x);
	r = p[0]+z*(p[1]+z*(p[2]+z*(p[3]+z*(p[4]+z*p[5]))));
	s = one+z*(q[0]+z*(q[1]+z*(q[2]+z*(q[3]+z*(q[4]+z*q[5])))));
	return ((float).375 + r/s)/x;
}