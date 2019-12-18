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
typedef  enum pconfig_target { ____Placeholder_pconfig_target } pconfig_target ;

/* Variables and functions */
 int /*<<< orphan*/  BUILD_BUG_ON (int) ; 
 int PCONFIG_TARGET_NR ; 
 scalar_t__ WARN_ON_ONCE (int) ; 
 unsigned long long targets_supported ; 

int pconfig_target_supported(enum pconfig_target target)
{
	/*
	 * We would need to re-think the implementation once we get > 64
	 * PCONFIG targets. Spec allows up to 2^32 targets.
	 */
	BUILD_BUG_ON(PCONFIG_TARGET_NR >= 64);

	if (WARN_ON_ONCE(target >= 64))
		return 0;
	return targets_supported & (1ULL << target);
}