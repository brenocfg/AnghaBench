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
 scalar_t__ PAGE_SIZE ; 
 int /*<<< orphan*/  arch_irqs_disabled () ; 
 int /*<<< orphan*/  flush_tlb_all () ; 
 int /*<<< orphan*/  mtsp (unsigned long,int) ; 
 unsigned long parisc_tlb_flush_threshold ; 
 int /*<<< orphan*/  pdtlb (unsigned long) ; 
 int /*<<< orphan*/  pitlb (unsigned long) ; 
 int /*<<< orphan*/  purge_tlb_end (unsigned long) ; 
 int /*<<< orphan*/  purge_tlb_start (unsigned long) ; 

int __flush_tlb_range(unsigned long sid, unsigned long start,
		      unsigned long end)
{
	unsigned long flags;

	if ((!IS_ENABLED(CONFIG_SMP) || !arch_irqs_disabled()) &&
	    end - start >= parisc_tlb_flush_threshold) {
		flush_tlb_all();
		return 1;
	}

	/* Purge TLB entries for small ranges using the pdtlb and
	   pitlb instructions.  These instructions execute locally
	   but cause a purge request to be broadcast to other TLBs.  */
	while (start < end) {
		purge_tlb_start(flags);
		mtsp(sid, 1);
		pdtlb(start);
		pitlb(start);
		purge_tlb_end(flags);
		start += PAGE_SIZE;
	}
	return 0;
}