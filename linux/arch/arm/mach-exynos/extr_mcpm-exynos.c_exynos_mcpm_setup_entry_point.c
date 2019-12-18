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
 int __pa_symbol (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __raw_writel (int,scalar_t__) ; 
 int /*<<< orphan*/  mcpm_entry_point ; 
 scalar_t__ ns_sram_base_addr ; 

__attribute__((used)) static void exynos_mcpm_setup_entry_point(void)
{
	/*
	 * U-Boot SPL is hardcoded to jump to the start of ns_sram_base_addr
	 * as part of secondary_cpu_start().  Let's redirect it to the
	 * mcpm_entry_point(). This is done during both secondary boot-up as
	 * well as system resume.
	 */
	__raw_writel(0xe59f0000, ns_sram_base_addr);     /* ldr r0, [pc, #0] */
	__raw_writel(0xe12fff10, ns_sram_base_addr + 4); /* bx  r0 */
	__raw_writel(__pa_symbol(mcpm_entry_point), ns_sram_base_addr + 8);
}