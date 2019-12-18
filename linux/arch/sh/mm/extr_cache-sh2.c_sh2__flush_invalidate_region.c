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
 unsigned long CACHE_OC_ADDRESS_ARRAY ; 
 unsigned long CACHE_PHYSADDR_MASK ; 
 unsigned long CCR_CACHE_INVALIDATE ; 
 int L1_CACHE_BYTES ; 
 unsigned long SH_CCR ; 
 unsigned long __raw_readl (unsigned long) ; 
 int /*<<< orphan*/  __raw_writel (unsigned long,unsigned long) ; 
 int /*<<< orphan*/  back_to_cached () ; 
 int /*<<< orphan*/  jump_to_uncached () ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 

__attribute__((used)) static void sh2__flush_invalidate_region(void *start, int size)
{
#ifdef CONFIG_CACHE_WRITEBACK
	/*
	 * SH-2 does not support individual line invalidation, only a
	 * global invalidate.
	 */
	unsigned long ccr;
	unsigned long flags;
	local_irq_save(flags);
	jump_to_uncached();

	ccr = __raw_readl(SH_CCR);
	ccr |= CCR_CACHE_INVALIDATE;
	__raw_writel(ccr, SH_CCR);

	back_to_cached();
	local_irq_restore(flags);
#else
	unsigned long v;
	unsigned long begin, end;

	begin = (unsigned long)start & ~(L1_CACHE_BYTES-1);
	end = ((unsigned long)start + size + L1_CACHE_BYTES-1)
		& ~(L1_CACHE_BYTES-1);

	for (v = begin; v < end; v+=L1_CACHE_BYTES)
		__raw_writel((v & CACHE_PHYSADDR_MASK),
			  CACHE_OC_ADDRESS_ARRAY | (v & 0x00000ff0) | 0x00000008);
#endif
}