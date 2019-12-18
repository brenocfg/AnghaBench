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
typedef  scalar_t__ u_int ;

/* Variables and functions */
 scalar_t__ FG_SENSOR_NOISE_THRESHOLD ; 

__attribute__((used)) static void
fg_get_pressures(int *p, const int *cur, const int *base, int n)
{
	int i;

	for (i = 0; i < n; i++) {
		p[i] = cur[i] - base[i];
		if (p[i] > 127)
			p[i] -= 256;
		if (p[i] < -127)
			p[i] += 256;
		if (p[i] < 0)
			p[i] = 0;

		/*
		 * Shave off pressures below the noise-pressure
		 * threshold; this will reduce the contribution from
		 * lower pressure readings.
		 */
		if ((u_int)p[i] <= FG_SENSOR_NOISE_THRESHOLD)
			p[i] = 0; /* filter away noise */
		else
			p[i] -= FG_SENSOR_NOISE_THRESHOLD;
	}
}