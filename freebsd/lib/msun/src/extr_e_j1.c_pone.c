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
 double one ; 
 double* pr2 ; 
 double* pr3 ; 
 double* pr5 ; 
 double* pr8 ; 
 double* ps2 ; 
 double* ps3 ; 
 double* ps5 ; 
 double* ps8 ; 

__attribute__((used)) static __inline double
pone(double x)
{
	const double *p,*q;
	double z,r,s;
        int32_t ix;
	GET_HIGH_WORD(ix,x);
	ix &= 0x7fffffff;
        if(ix>=0x40200000)     {p = pr8; q= ps8;}
        else if(ix>=0x40122E8B){p = pr5; q= ps5;}
        else if(ix>=0x4006DB6D){p = pr3; q= ps3;}
	else                   {p = pr2; q= ps2;}	/* ix>=0x40000000 */
        z = one/(x*x);
        r = p[0]+z*(p[1]+z*(p[2]+z*(p[3]+z*(p[4]+z*p[5]))));
        s = one+z*(q[0]+z*(q[1]+z*(q[2]+z*(q[3]+z*q[4]))));
        return one+ r/s;
}