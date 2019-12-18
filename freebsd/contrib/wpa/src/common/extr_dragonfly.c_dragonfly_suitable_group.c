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

int dragonfly_suitable_group(int group, int ecc_only)
{
	/* Enforce REVmd rules on which SAE groups are suitable for production
	 * purposes: FFC groups whose prime is >= 3072 bits and ECC groups
	 * defined over a prime field whose prime is >= 256 bits. Furthermore,
	 * ECC groups defined over a characteristic 2 finite field and ECC
	 * groups with a co-factor greater than 1 are not suitable. Disable
	 * groups that use Brainpool curves as well for now since they leak more
	 * timing information due to the prime not being close to a power of
	 * two. */
	return group == 19 || group == 20 || group == 21 ||
		(!ecc_only &&
		 (group == 15 || group == 16 || group == 17 || group == 18));
}