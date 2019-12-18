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
typedef  int /*<<< orphan*/  uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  JZ_CORESTS_MIRQ0P ; 
 int /*<<< orphan*/  JZ_REIM_MIRQ0M ; 
 int /*<<< orphan*/  mips_rd_xburst_reim () ; 
 int /*<<< orphan*/  mips_wr_xburst_core_sts (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mips_wr_xburst_mbox0 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mips_wr_xburst_mbox1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mips_wr_xburst_reim (int /*<<< orphan*/ ) ; 

void
platform_cpu_init(void)
{
	uint32_t reg;

	/*
	 * Do not expect mbox interrups while writing
	 * mbox
	 */
	reg = mips_rd_xburst_reim();
	reg &= ~JZ_REIM_MIRQ0M;
	mips_wr_xburst_reim(reg);

	/* Clean mailboxes */
	mips_wr_xburst_mbox0(0);
	mips_wr_xburst_mbox1(0);
	mips_wr_xburst_core_sts(~JZ_CORESTS_MIRQ0P);

	/* Unmask mbox interrupts */
	reg |= JZ_REIM_MIRQ0M;
	mips_wr_xburst_reim(reg);
}