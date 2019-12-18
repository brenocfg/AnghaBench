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
struct service_curve {scalar_t__ m2; scalar_t__ d; scalar_t__ m1; } ;

/* Variables and functions */

__attribute__((used)) static double
sc_x2y(struct service_curve *sc, double x)
{
	double	y;

	if (x <= (double)sc->d)
		/* y belongs to the 1st segment */
		y = x * (double)sc->m1;
	else
		/* y belongs to the 2nd segment */
		y = (double)sc->d * (double)sc->m1
			+ (x - (double)sc->d) * (double)sc->m2;
	return (y);
}