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
typedef  int u_int8_t ;

/* Variables and functions */

__attribute__((used)) static u_int8_t
ess_calcfilter(int spd)
{
	int cutoff;

	/* cutoff = 7160000 / (256 - divisor) */
	/* divisor = 256 - (7160000 / cutoff) */
	cutoff = (spd * 9 * 82) / 20;
	return (256 - (7160000 / cutoff));
}