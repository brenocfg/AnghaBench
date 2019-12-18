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
 int JZ_CORESTS_MIRQ0P ; 
 int JZ_REIM_MIRQ0M ; 
 unsigned int hard_int_mask (int /*<<< orphan*/ ) ; 
 unsigned int mips_rd_xburst_reim () ; 
 int /*<<< orphan*/  mips_wr_xburst_core_sts (int) ; 
 int /*<<< orphan*/  mips_wr_xburst_reim (unsigned int) ; 
 int /*<<< orphan*/  platform_ipi_hardintr_num () ; 
 int /*<<< orphan*/  set_intr_mask (unsigned int) ; 

void
platform_init_ap(int cpuid)
{
	unsigned reg;

	/*
	 * Clear any pending IPIs.
	 */
	mips_wr_xburst_core_sts(~(JZ_CORESTS_MIRQ0P << cpuid));

	/* Allow IPI mbox for this core */
	reg = mips_rd_xburst_reim();
	reg |= (JZ_REIM_MIRQ0M << cpuid);
	mips_wr_xburst_reim(reg);

	/*
	 * Unmask the ipi interrupts.
	 */
	reg = hard_int_mask(platform_ipi_hardintr_num());
	set_intr_mask(reg);
}