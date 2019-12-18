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
 scalar_t__ EXYNOS_BOOT_FLAG ; 
 int /*<<< orphan*/  SMC_CMD_SLEEP ; 
 int /*<<< orphan*/  exynos_smc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  flush_cache_all () ; 
 int /*<<< orphan*/  outer_flush_all () ; 
 int /*<<< orphan*/  pr_info (char*) ; 
 scalar_t__ sysram_ns_base_addr ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int exynos_cpu_suspend(unsigned long arg)
{
	flush_cache_all();
	outer_flush_all();

	exynos_smc(SMC_CMD_SLEEP, 0, 0, 0);

	pr_info("Failed to suspend the system\n");
	writel(0, sysram_ns_base_addr + EXYNOS_BOOT_FLAG);
	return 1;
}