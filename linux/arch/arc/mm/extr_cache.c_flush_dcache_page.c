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
struct page {unsigned long index; int /*<<< orphan*/  flags; } ;
struct address_space {int dummy; } ;
typedef  unsigned long phys_addr_t ;

/* Variables and functions */
 unsigned long PAGE_SHIFT ; 
 int /*<<< orphan*/  PG_dc_clean ; 
 int /*<<< orphan*/  __flush_dcache_page (unsigned long,unsigned long) ; 
 scalar_t__ addr_not_cache_congruent (unsigned long,unsigned long) ; 
 int /*<<< orphan*/  cache_is_vipt_aliasing () ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mapping_mapped (struct address_space*) ; 
 scalar_t__ page_address (struct page*) ; 
 scalar_t__ page_mapcount (struct page*) ; 
 struct address_space* page_mapping_file (struct page*) ; 

void flush_dcache_page(struct page *page)
{
	struct address_space *mapping;

	if (!cache_is_vipt_aliasing()) {
		clear_bit(PG_dc_clean, &page->flags);
		return;
	}

	/* don't handle anon pages here */
	mapping = page_mapping_file(page);
	if (!mapping)
		return;

	/*
	 * pagecache page, file not yet mapped to userspace
	 * Make a note that K-mapping is dirty
	 */
	if (!mapping_mapped(mapping)) {
		clear_bit(PG_dc_clean, &page->flags);
	} else if (page_mapcount(page)) {

		/* kernel reading from page with U-mapping */
		phys_addr_t paddr = (unsigned long)page_address(page);
		unsigned long vaddr = page->index << PAGE_SHIFT;

		if (addr_not_cache_congruent(paddr, vaddr))
			__flush_dcache_page(paddr, vaddr);
	}
}