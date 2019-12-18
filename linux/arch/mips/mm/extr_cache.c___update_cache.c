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
typedef  int /*<<< orphan*/  pte_t ;

/* Variables and functions */
 int /*<<< orphan*/  ClearPageDcacheDirty (struct page*) ; 
 unsigned long PAGE_MASK ; 
 scalar_t__ PageHighMem (struct page*) ; 
 scalar_t__ Page_dcache_dirty (struct page*) ; 
 int /*<<< orphan*/  __kunmap_atomic (void*) ; 
 int /*<<< orphan*/  cpu_has_ic_fills_f_dc ; 
 int /*<<< orphan*/  flush_data_cache_page (unsigned long) ; 
 scalar_t__ kmap_atomic (struct page*) ; 
 scalar_t__ page_address (struct page*) ; 
 scalar_t__ pages_do_alias (unsigned long,unsigned long) ; 
 struct page* pfn_to_page (unsigned long) ; 
 int /*<<< orphan*/  pfn_valid (unsigned long) ; 
 int /*<<< orphan*/  pte_no_exec (int /*<<< orphan*/ ) ; 
 unsigned long pte_pfn (int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

void __update_cache(unsigned long address, pte_t pte)
{
	struct page *page;
	unsigned long pfn, addr;
	int exec = !pte_no_exec(pte) && !cpu_has_ic_fills_f_dc;

	pfn = pte_pfn(pte);
	if (unlikely(!pfn_valid(pfn)))
		return;
	page = pfn_to_page(pfn);
	if (Page_dcache_dirty(page)) {
		if (PageHighMem(page))
			addr = (unsigned long)kmap_atomic(page);
		else
			addr = (unsigned long)page_address(page);

		if (exec || pages_do_alias(addr, address & PAGE_MASK))
			flush_data_cache_page(addr);

		if (PageHighMem(page))
			__kunmap_atomic((void *)addr);

		ClearPageDcacheDirty(page);
	}
}