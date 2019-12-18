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
struct flusher_data {int addr1; int addr2; } ;

/* Variables and functions */
 int /*<<< orphan*/  CACHE_IC_ADDRESS_ARRAY ; 
 int CCR_ICACHE_INVALIDATE ; 
 int L1_CACHE_BYTES ; 
 unsigned long MAX_ICACHE_PAGES ; 
 unsigned long PAGE_SHIFT ; 
 int /*<<< orphan*/  SH_CCR ; 
 int __raw_readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __raw_writel (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  back_to_cached () ; 
 int /*<<< orphan*/  jump_to_uncached () ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 int /*<<< orphan*/  sh2a__flush_wback_region (void*,unsigned long) ; 
 int /*<<< orphan*/  sh2a_invalidate_line (int /*<<< orphan*/ ,unsigned long) ; 

__attribute__((used)) static void sh2a_flush_icache_range(void *args)
{
	struct flusher_data *data = args;
	unsigned long start, end;
	unsigned long v;
	unsigned long flags;

	start = data->addr1 & ~(L1_CACHE_BYTES-1);
	end = (data->addr2 + L1_CACHE_BYTES-1) & ~(L1_CACHE_BYTES-1);

#ifdef CONFIG_CACHE_WRITEBACK
	sh2a__flush_wback_region((void *)start, end-start);
#endif

	local_irq_save(flags);
	jump_to_uncached();

	/* I-Cache invalidate */
	/* If there are too many pages then just blow the cache */
	if (((end - start) >> PAGE_SHIFT) >= MAX_ICACHE_PAGES) {
		__raw_writel(__raw_readl(SH_CCR) | CCR_ICACHE_INVALIDATE,
			     SH_CCR);
	} else {
		for (v = start; v < end; v += L1_CACHE_BYTES)
			sh2a_invalidate_line(CACHE_IC_ADDRESS_ARRAY, v);
	}

	back_to_cached();
	local_irq_restore(flags);
}