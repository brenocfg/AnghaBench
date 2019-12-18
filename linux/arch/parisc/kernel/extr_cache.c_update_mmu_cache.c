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
struct vm_area_struct {int dummy; } ;
struct page {int /*<<< orphan*/  flags; } ;
typedef  int /*<<< orphan*/  pte_t ;

/* Variables and functions */
 int /*<<< orphan*/  PG_dcache_dirty ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  flush_kernel_dcache_page_addr (int /*<<< orphan*/ ) ; 
 scalar_t__ page_mapping_file (struct page*) ; 
 scalar_t__ parisc_requires_coherency () ; 
 struct page* pfn_to_page (unsigned long) ; 
 int /*<<< orphan*/  pfn_va (unsigned long) ; 
 int /*<<< orphan*/  pfn_valid (unsigned long) ; 
 unsigned long pte_pfn (int /*<<< orphan*/ ) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void
update_mmu_cache(struct vm_area_struct *vma, unsigned long address, pte_t *ptep)
{
	unsigned long pfn = pte_pfn(*ptep);
	struct page *page;

	/* We don't have pte special.  As a result, we can be called with
	   an invalid pfn and we don't need to flush the kernel dcache page.
	   This occurs with FireGL card in C8000.  */
	if (!pfn_valid(pfn))
		return;

	page = pfn_to_page(pfn);
	if (page_mapping_file(page) &&
	    test_bit(PG_dcache_dirty, &page->flags)) {
		flush_kernel_dcache_page_addr(pfn_va(pfn));
		clear_bit(PG_dcache_dirty, &page->flags);
	} else if (parisc_requires_coherency())
		flush_kernel_dcache_page_addr(pfn_va(pfn));
}