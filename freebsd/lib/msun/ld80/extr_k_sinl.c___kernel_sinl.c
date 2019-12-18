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

/* Variables and functions */
 long double S1 ; 
 long double S2 ; 
 long double S3 ; 
 long double S4 ; 
 long double S5 ; 
 long double S6 ; 
 long double S7 ; 
 long double S8 ; 
 long double half ; 

long double
__kernel_sinl(long double x, long double y, int iy)
{
	long double z,r,v;

	z	=  x*x;
	v	=  z*x;
	r	=  S2+z*(S3+z*(S4+z*(S5+z*(S6+z*(S7+z*S8)))));
	if(iy==0) return x+v*(S1+z*r);
	else      return x-((z*(half*y-v*r)-y)-v*S1);
}