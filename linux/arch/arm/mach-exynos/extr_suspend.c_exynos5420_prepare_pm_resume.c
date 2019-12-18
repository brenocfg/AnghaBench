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
 int /*<<< orphan*/  CONFIG_EXYNOS_MCPM ; 
 int /*<<< orphan*/  CONFIG_HW_PERF_EVENTS ; 
 int /*<<< orphan*/  EXYNOS_COMMON_CONFIGURATION (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ENABLED (int /*<<< orphan*/ ) ; 
 unsigned int MPIDR_AFFINITY_LEVEL (unsigned int,int) ; 
 int /*<<< orphan*/  S5P_CORE_LOCAL_PWR_EN ; 
 int /*<<< orphan*/  WARN_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mcpm_cpu_powered_up () ; 
 int /*<<< orphan*/  pmu_raw_writel (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned int read_cpuid_mpidr () ; 

__attribute__((used)) static void exynos5420_prepare_pm_resume(void)
{
	unsigned int mpidr, cluster;

	mpidr = read_cpuid_mpidr();
	cluster = MPIDR_AFFINITY_LEVEL(mpidr, 1);

	if (IS_ENABLED(CONFIG_EXYNOS_MCPM))
		WARN_ON(mcpm_cpu_powered_up());

	if (IS_ENABLED(CONFIG_HW_PERF_EVENTS) && cluster != 0) {
		/*
		 * When system is resumed on the LITTLE/KFC core (cluster 1),
		 * the DSCR is not properly updated until the power is turned
		 * on also for the cluster 0. Enable it for a while to
		 * propagate the SPNIDEN and SPIDEN signals from Secure JTAG
		 * block and avoid undefined instruction issue on CP14 reset.
		 */
		pmu_raw_writel(S5P_CORE_LOCAL_PWR_EN,
				EXYNOS_COMMON_CONFIGURATION(0));
		pmu_raw_writel(0,
				EXYNOS_COMMON_CONFIGURATION(0));
	}
}