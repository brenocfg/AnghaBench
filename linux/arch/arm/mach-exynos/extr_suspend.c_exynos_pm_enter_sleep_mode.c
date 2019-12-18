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
 int /*<<< orphan*/  EXYNOS_SLEEP_MAGIC ; 
 int /*<<< orphan*/  S5P_INFORM1 ; 
 int /*<<< orphan*/  SYS_SLEEP ; 
 int /*<<< orphan*/  exynos_sys_powerdown_conf (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pmu_raw_writel (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void exynos_pm_enter_sleep_mode(void)
{
	/* Set value of power down register for sleep mode */
	exynos_sys_powerdown_conf(SYS_SLEEP);
	pmu_raw_writel(EXYNOS_SLEEP_MAGIC, S5P_INFORM1);
}