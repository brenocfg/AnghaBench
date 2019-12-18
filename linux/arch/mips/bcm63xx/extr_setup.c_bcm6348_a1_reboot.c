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
 int /*<<< orphan*/  CONF_CM_CMASK ; 
 int /*<<< orphan*/  CONF_CM_UNCACHED ; 
 int /*<<< orphan*/  PERF_SOFTRESET_REG ; 
 int /*<<< orphan*/  SOFTRESET_6348_ALL ; 
 int ST0_BEV ; 
 int ST0_ERL ; 
 int /*<<< orphan*/  __flush_cache_all () ; 
 int /*<<< orphan*/  bcm_perf_readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bcm_perf_writel (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  change_c0_config (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int /*<<< orphan*/  pr_info (char*) ; 
 int /*<<< orphan*/  set_c0_status (int) ; 
 int /*<<< orphan*/  write_c0_wired (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void bcm6348_a1_reboot(void)
{
	u32 reg;

	/* soft reset all blocks */
	pr_info("soft-resetting all blocks ...\n");
	reg = bcm_perf_readl(PERF_SOFTRESET_REG);
	reg &= ~SOFTRESET_6348_ALL;
	bcm_perf_writel(reg, PERF_SOFTRESET_REG);
	mdelay(10);

	reg = bcm_perf_readl(PERF_SOFTRESET_REG);
	reg |= SOFTRESET_6348_ALL;
	bcm_perf_writel(reg, PERF_SOFTRESET_REG);
	mdelay(10);

	/* Jump to the power on address. */
	pr_info("jumping to reset vector.\n");
	/* set high vectors (base at 0xbfc00000 */
	set_c0_status(ST0_BEV | ST0_ERL);
	/* run uncached in kseg0 */
	change_c0_config(CONF_CM_CMASK, CONF_CM_UNCACHED);
	__flush_cache_all();
	/* remove all wired TLB entries */
	write_c0_wired(0);
	__asm__ __volatile__(
		"jr\t%0"
		:
		: "r" (0xbfc00000));
	while (1)
		;
}