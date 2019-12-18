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

unsigned int dragonfly_min_pwe_loop_iter(int group)
{
	if (group == 22 || group == 23 || group == 24) {
		/* FFC groups for which pwd-value is likely to be >= p
		 * frequently */
		return 40;
	}

	if (group == 1 || group == 2 || group == 5 || group == 14 ||
	    group == 15 || group == 16 || group == 17 || group == 18) {
		/* FFC groups that have prime that is close to a power of two */
		return 1;
	}

	/* Default to 40 (this covers most ECC groups) */
	return 40;
}