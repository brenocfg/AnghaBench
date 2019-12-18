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
 int /*<<< orphan*/  CONFIG_SMP ; 
 int /*<<< orphan*/  IS_ENABLED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  arch_irqs_disabled () ; 
 int /*<<< orphan*/  flush_data_cache () ; 
 int /*<<< orphan*/  flush_tlb_kernel_range (unsigned long,unsigned long) ; 
 unsigned long parisc_cache_flush_threshold ; 
 int /*<<< orphan*/  purge_kernel_dcache_range_asm (unsigned long,unsigned long) ; 

void invalidate_kernel_vmap_range(void *vaddr, int size)
{
	unsigned long start = (unsigned long)vaddr;
	unsigned long end = start + size;

	if ((!IS_ENABLED(CONFIG_SMP) || !arch_irqs_disabled()) &&
	    (unsigned long)size >= parisc_cache_flush_threshold) {
		flush_tlb_kernel_range(start, end);
		flush_data_cache();
		return;
	}

	purge_kernel_dcache_range_asm(start, end);
	flush_tlb_kernel_range(start, end);
}