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
 double C0 ; 
 double C1 ; 
 double C2 ; 
 double C3 ; 
 double S1 ; 
 double S2 ; 
 double S3 ; 
 double S4 ; 

__attribute__((used)) static inline void
__kernel_sincosdf(double x, float *sn, float *cs)
{
	double r, s, w, z;

	z = x * x;
	w = z * z;
	r = S3 + z * S4;
	s = z * x;
	*sn = (x + s * (S1 + z * S2)) + s * w * r;
	r = C2 + z * C3;
	*cs = ((1 + z * C0) + w * C1) + (w * z) * r;
}