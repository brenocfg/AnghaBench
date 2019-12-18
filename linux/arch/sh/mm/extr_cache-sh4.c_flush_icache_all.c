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
 unsigned long CCR_CACHE_ICI ; 
 int /*<<< orphan*/  SH_CCR ; 
 unsigned long __raw_readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __raw_writel (unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  back_to_cached () ; 
 int /*<<< orphan*/  jump_to_uncached () ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 

__attribute__((used)) static void flush_icache_all(void)
{
	unsigned long flags, ccr;

	local_irq_save(flags);
	jump_to_uncached();

	/* Flush I-cache */
	ccr = __raw_readl(SH_CCR);
	ccr |= CCR_CACHE_ICI;
	__raw_writel(ccr, SH_CCR);

	/*
	 * back_to_cached() will take care of the barrier for us, don't add
	 * another one!
	 */

	back_to_cached();
	local_irq_restore(flags);
}