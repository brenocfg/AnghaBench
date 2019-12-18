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
typedef  int /*<<< orphan*/  u32 ;

/* Variables and functions */
 int /*<<< orphan*/  EXYNOS5420_ARM_USE_STANDBY_WFI0 ; 
 int /*<<< orphan*/  EXYNOS5420_KFC_USE_STANDBY_WFI0 ; 
 int /*<<< orphan*/  MPIDR_AFFINITY_LEVEL (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  S5P_CENTRAL_SEQ_OPTION ; 
 int /*<<< orphan*/  exynos_pm_central_suspend () ; 
 int /*<<< orphan*/  pmu_raw_writel (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  read_cpuid_mpidr () ; 

__attribute__((used)) static int exynos5420_pm_suspend(void)
{
	u32 this_cluster;

	exynos_pm_central_suspend();

	/* Setting SEQ_OPTION register */

	this_cluster = MPIDR_AFFINITY_LEVEL(read_cpuid_mpidr(), 1);
	if (!this_cluster)
		pmu_raw_writel(EXYNOS5420_ARM_USE_STANDBY_WFI0,
				S5P_CENTRAL_SEQ_OPTION);
	else
		pmu_raw_writel(EXYNOS5420_KFC_USE_STANDBY_WFI0,
				S5P_CENTRAL_SEQ_OPTION);
	return 0;
}