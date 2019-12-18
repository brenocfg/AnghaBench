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
struct page {int dummy; } ;

/* Variables and functions */
 int PAGE_SIZE ; 
 scalar_t__ PageHighMem (struct page*) ; 
 int /*<<< orphan*/  __flush_tlb_all () ; 
 int /*<<< orphan*/  __set_pages_np (struct page*,int) ; 
 int /*<<< orphan*/  __set_pages_p (struct page*,int) ; 
 int /*<<< orphan*/  arch_flush_lazy_mmu_mode () ; 
 int /*<<< orphan*/  debug_check_no_locks_freed (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  page_address (struct page*) ; 
 int /*<<< orphan*/  preempt_disable () ; 
 int /*<<< orphan*/  preempt_enable () ; 

void __kernel_map_pages(struct page *page, int numpages, int enable)
{
	if (PageHighMem(page))
		return;
	if (!enable) {
		debug_check_no_locks_freed(page_address(page),
					   numpages * PAGE_SIZE);
	}

	/*
	 * The return value is ignored as the calls cannot fail.
	 * Large pages for identity mappings are not used at boot time
	 * and hence no memory allocations during large page split.
	 */
	if (enable)
		__set_pages_p(page, numpages);
	else
		__set_pages_np(page, numpages);

	/*
	 * We should perform an IPI and flush all tlbs,
	 * but that can deadlock->flush only current cpu.
	 * Preemption needs to be disabled around __flush_tlb_all() due to
	 * CR3 reload in __native_flush_tlb().
	 */
	preempt_disable();
	__flush_tlb_all();
	preempt_enable();

	arch_flush_lazy_mmu_mode();
}