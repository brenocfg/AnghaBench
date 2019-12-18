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
 scalar_t__ ARM_CPU_PART_CORTEX_A9 ; 
 int /*<<< orphan*/  S5P_CENTRAL_SEQ_OPTION ; 
 int S5P_USE_STANDBY_WFE0 ; 
 int S5P_USE_STANDBY_WFI0 ; 
 int /*<<< orphan*/  exynos_cpu_save_register () ; 
 int /*<<< orphan*/  exynos_pm_central_suspend () ; 
 int /*<<< orphan*/  pmu_raw_writel (int,int /*<<< orphan*/ ) ; 
 scalar_t__ read_cpuid_part () ; 

__attribute__((used)) static int exynos_pm_suspend(void)
{
	exynos_pm_central_suspend();

	/* Setting SEQ_OPTION register */
	pmu_raw_writel(S5P_USE_STANDBY_WFI0 | S5P_USE_STANDBY_WFE0,
		       S5P_CENTRAL_SEQ_OPTION);

	if (read_cpuid_part() == ARM_CPU_PART_CORTEX_A9)
		exynos_cpu_save_register();

	return 0;
}