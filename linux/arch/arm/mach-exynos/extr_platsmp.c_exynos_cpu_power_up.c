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
 int /*<<< orphan*/  EXYNOS_ARM_CORE_CONFIGURATION (int) ; 
 int /*<<< orphan*/  S5P_CORE_AUTOWAKEUP_EN ; 
 int /*<<< orphan*/  S5P_CORE_LOCAL_PWR_EN ; 
 int /*<<< orphan*/  pmu_raw_writel (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ soc_is_exynos3250 () ; 

void exynos_cpu_power_up(int cpu)
{
	u32 core_conf = S5P_CORE_LOCAL_PWR_EN;

	if (soc_is_exynos3250())
		core_conf |= S5P_CORE_AUTOWAKEUP_EN;

	pmu_raw_writel(core_conf,
			EXYNOS_ARM_CORE_CONFIGURATION(cpu));
}