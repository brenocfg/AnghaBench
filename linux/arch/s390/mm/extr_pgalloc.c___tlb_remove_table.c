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
struct page {int /*<<< orphan*/  _refcount; } ;

/* Variables and functions */
 int PAGE_SHIFT ; 
 int /*<<< orphan*/  __free_page (struct page*) ; 
 int __pa (void*) ; 
 unsigned int atomic_xor_bits (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  free_pages (unsigned long,int) ; 
 struct page* pfn_to_page (int) ; 
 int /*<<< orphan*/  pgtable_pte_page_dtor (struct page*) ; 

void __tlb_remove_table(void *_table)
{
	unsigned int mask = (unsigned long) _table & 3;
	void *table = (void *)((unsigned long) _table ^ mask);
	struct page *page = pfn_to_page(__pa(table) >> PAGE_SHIFT);

	switch (mask) {
	case 0:		/* pmd, pud, or p4d */
		free_pages((unsigned long) table, 2);
		break;
	case 1:		/* lower 2K of a 4K page table */
	case 2:		/* higher 2K of a 4K page table */
		mask = atomic_xor_bits(&page->_refcount, mask << (4 + 24));
		mask >>= 24;
		if (mask != 0)
			break;
		/* fallthrough */
	case 3:		/* 4K page table with pgstes */
		if (mask & 3)
			atomic_xor_bits(&page->_refcount, 3 << 24);
		pgtable_pte_page_dtor(page);
		__free_page(page);
		break;
	}
}