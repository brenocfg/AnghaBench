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
 double C1 ; 
 double C2 ; 
 double C3 ; 
 double C4 ; 
 double C5 ; 
 double C6 ; 
 double S1 ; 
 double S2 ; 
 double S3 ; 
 double S4 ; 
 double S5 ; 
 double S6 ; 

__attribute__((used)) static inline void
__kernel_sincos(double x, double y, int iy, double *sn, double *cs)
{
	double hz, r, v, w, z;

	z = x * x;
	w = z * z;
	r = S2 + z * (S3 + z * S4) + z * w * (S5 + z * S6);
	v = z * x;

	if (iy == 0)
		*sn = x + v * (S1 + z * r);
	else
		*sn = x - ((z * (y / 2 - v * r) - y) - v * S1);

	r = z * (C1 + z * (C2 + z * C3)) + w * w * (C4 + z * (C5 + z * C6));
	hz = z / 2;
	w = 1 - hz;
	*cs = w + (((1 - w) - hz) + (z * r - x * y));
}