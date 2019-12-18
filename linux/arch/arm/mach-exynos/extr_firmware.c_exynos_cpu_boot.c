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
 int /*<<< orphan*/  SMC_CMD_CPU1BOOT ; 
 int /*<<< orphan*/  exynos_smc (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ soc_is_exynos3250 () ; 

__attribute__((used)) static int exynos_cpu_boot(int cpu)
{
	/*
	 * Exynos3250 doesn't need to send smc command for secondary CPU boot
	 * because Exynos3250 removes WFE in secure mode.
	 */
	if (soc_is_exynos3250())
		return 0;

	/*
	 * The second parameter of SMC_CMD_CPU1BOOT command means CPU id.
	 */
	exynos_smc(SMC_CMD_CPU1BOOT, cpu, 0, 0);
	return 0;
}