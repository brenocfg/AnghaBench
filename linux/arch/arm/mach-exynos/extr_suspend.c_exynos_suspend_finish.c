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
 int /*<<< orphan*/  pr_warn (char*,int) ; 
 int regulator_suspend_finish () ; 

__attribute__((used)) static void exynos_suspend_finish(void)
{
	int ret;

	ret = regulator_suspend_finish();
	if (ret)
		pr_warn("Failed to resume regulators from suspend (%d)\n", ret);
}