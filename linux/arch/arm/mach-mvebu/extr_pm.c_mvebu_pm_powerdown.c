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
typedef  int u32 ;

/* Variables and functions */
 scalar_t__ SDRAM_CONFIG_OFFS ; 
 int SDRAM_CONFIG_SR_MODE_BIT ; 
 scalar_t__ SDRAM_DLB_EVICTION_OFFS ; 
 int SDRAM_DLB_EVICTION_THRESHOLD_MASK ; 
 scalar_t__ SDRAM_OPERATION_OFFS ; 
 int SDRAM_OPERATION_SELF_REFRESH ; 
 int /*<<< orphan*/  dsb () ; 
 int /*<<< orphan*/  flush_cache_all () ; 
 int /*<<< orphan*/  mvebu_board_pm_enter (scalar_t__,int) ; 
 int /*<<< orphan*/  outer_flush_all () ; 
 int readl (scalar_t__) ; 
 scalar_t__ sdram_ctrl ; 
 int /*<<< orphan*/  udelay (int) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static int mvebu_pm_powerdown(unsigned long data)
{
	u32 reg, srcmd;

	flush_cache_all();
	outer_flush_all();

	/*
	 * Issue a Data Synchronization Barrier instruction to ensure
	 * that all state saving has been completed.
	 */
	dsb();

	/* Flush the DLB and wait ~7 usec */
	reg = readl(sdram_ctrl + SDRAM_DLB_EVICTION_OFFS);
	reg &= ~SDRAM_DLB_EVICTION_THRESHOLD_MASK;
	writel(reg, sdram_ctrl + SDRAM_DLB_EVICTION_OFFS);

	udelay(7);

	/* Set DRAM in battery backup mode */
	reg = readl(sdram_ctrl + SDRAM_CONFIG_OFFS);
	reg &= ~SDRAM_CONFIG_SR_MODE_BIT;
	writel(reg, sdram_ctrl + SDRAM_CONFIG_OFFS);

	/* Prepare to go to self-refresh */

	srcmd = readl(sdram_ctrl + SDRAM_OPERATION_OFFS);
	srcmd &= ~0x1F;
	srcmd |= SDRAM_OPERATION_SELF_REFRESH;

	mvebu_board_pm_enter(sdram_ctrl + SDRAM_OPERATION_OFFS, srcmd);

	return 0;
}