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
 int /*<<< orphan*/  PM_SUSPEND_MEM ; 
 int /*<<< orphan*/  pr_err (char*,int) ; 
 int regulator_suspend_prepare (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int exynos_suspend_prepare(void)
{
	int ret;

	/*
	 * REVISIT: It would be better if struct platform_suspend_ops
	 * .prepare handler get the suspend_state_t as a parameter to
	 * avoid hard-coding the suspend to mem state. It's safe to do
	 * it now only because the suspend_valid_only_mem function is
	 * used as the .valid callback used to check if a given state
	 * is supported by the platform anyways.
	 */
	ret = regulator_suspend_prepare(PM_SUSPEND_MEM);
	if (ret) {
		pr_err("Failed to prepare regulators for suspend (%d)\n", ret);
		return ret;
	}

	return 0;
}