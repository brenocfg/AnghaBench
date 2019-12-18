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
 unsigned long S5P_CENTRAL_LOWPWR_CFG ; 
 int /*<<< orphan*/  S5P_CENTRAL_SEQ_CONFIGURATION ; 
 unsigned long pmu_raw_readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pmu_raw_writel (unsigned long,int /*<<< orphan*/ ) ; 

void exynos_pm_central_suspend(void)
{
	unsigned long tmp;

	/* Setting Central Sequence Register for power down mode */
	tmp = pmu_raw_readl(S5P_CENTRAL_SEQ_CONFIGURATION);
	tmp &= ~S5P_CENTRAL_LOWPWR_CFG;
	pmu_raw_writel(tmp, S5P_CENTRAL_SEQ_CONFIGURATION);
}