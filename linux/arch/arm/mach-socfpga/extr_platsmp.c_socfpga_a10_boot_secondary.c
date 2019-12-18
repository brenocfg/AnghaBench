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
struct task_struct {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  RSTMGR_MPUMODRST_CPU1 ; 
 scalar_t__ SOCFPGA_A10_RSTMGR_MODMPURST ; 
 int /*<<< orphan*/  __pa_symbol (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  flush_cache_all () ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  outer_clean_range (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  phys_to_virt (int /*<<< orphan*/ ) ; 
 scalar_t__ rst_manager_base_addr ; 
 int /*<<< orphan*/  secondary_startup ; 
 int /*<<< orphan*/  secondary_trampoline ; 
 int /*<<< orphan*/  secondary_trampoline_end ; 
 int /*<<< orphan*/  smp_wmb () ; 
 int socfpga_cpu1start_addr ; 
 scalar_t__ sys_manager_base_addr ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int socfpga_a10_boot_secondary(unsigned int cpu, struct task_struct *idle)
{
	int trampoline_size = &secondary_trampoline_end - &secondary_trampoline;

	if (socfpga_cpu1start_addr) {
		writel(RSTMGR_MPUMODRST_CPU1, rst_manager_base_addr +
		       SOCFPGA_A10_RSTMGR_MODMPURST);
		memcpy(phys_to_virt(0), &secondary_trampoline, trampoline_size);

		writel(__pa_symbol(secondary_startup),
		       sys_manager_base_addr + (socfpga_cpu1start_addr & 0x00000fff));

		flush_cache_all();
		smp_wmb();
		outer_clean_range(0, trampoline_size);

		/* This will release CPU #1 out of reset. */
		writel(0, rst_manager_base_addr + SOCFPGA_A10_RSTMGR_MODMPURST);
	}

	return 0;
}