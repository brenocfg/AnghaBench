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
 int M_SQRT2 ; 
 double exp (double) ; 
 int fabs (double) ; 

double kf_erfc(double x)
{
	const double p0 = 220.2068679123761;
	const double p1 = 221.2135961699311;
	const double p2 = 112.0792914978709;
	const double p3 = 33.912866078383;
	const double p4 = 6.37396220353165;
	const double p5 = .7003830644436881;
	const double p6 = .03526249659989109;
	const double q0 = 440.4137358247522;
	const double q1 = 793.8265125199484;
	const double q2 = 637.3336333788311;
	const double q3 = 296.5642487796737;
	const double q4 = 86.78073220294608;
	const double q5 = 16.06417757920695;
	const double q6 = 1.755667163182642;
	const double q7 = .08838834764831844;
	double expntl, z, p;
	z = fabs(x) * M_SQRT2;
	if (z > 37.) return x > 0.? 0. : 2.;
	expntl = exp(z * z * - .5);
	if (z < 10. / M_SQRT2) // for small z
	    p = expntl * ((((((p6 * z + p5) * z + p4) * z + p3) * z + p2) * z + p1) * z + p0)
			/ (((((((q7 * z + q6) * z + q5) * z + q4) * z + q3) * z + q2) * z + q1) * z + q0);
	else p = expntl / 2.506628274631001 / (z + 1. / (z + 2. / (z + 3. / (z + 4. / (z + .65)))));
	return x > 0.? 2. * p : 2. * (1. - p);
}