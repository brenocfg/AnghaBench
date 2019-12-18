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
struct page {int index; } ;
struct address_space {int dummy; } ;

/* Variables and functions */
 int PAGE_SHIFT ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  PageHighMem (struct page*) ; 
 int /*<<< orphan*/  __cpuc_flush_dcache_area (void*,int /*<<< orphan*/ ) ; 
 scalar_t__ cache_is_vipt_aliasing () ; 
 scalar_t__ cache_is_vipt_nonaliasing () ; 
 unsigned long compound_nr (struct page*) ; 
 int /*<<< orphan*/  flush_pfn_alias (int /*<<< orphan*/ ,int) ; 
 void* kmap_atomic (struct page*) ; 
 void* kmap_high_get (struct page*) ; 
 int /*<<< orphan*/  kunmap_atomic (void*) ; 
 int /*<<< orphan*/  kunmap_high (struct page*) ; 
 void* page_address (struct page*) ; 
 int /*<<< orphan*/  page_size (struct page*) ; 
 int /*<<< orphan*/  page_to_pfn (struct page*) ; 

void __flush_dcache_page(struct address_space *mapping, struct page *page)
{
	/*
	 * Writeback any data associated with the kernel mapping of this
	 * page.  This ensures that data in the physical page is mutually
	 * coherent with the kernels mapping.
	 */
	if (!PageHighMem(page)) {
		__cpuc_flush_dcache_area(page_address(page), page_size(page));
	} else {
		unsigned long i;
		if (cache_is_vipt_nonaliasing()) {
			for (i = 0; i < compound_nr(page); i++) {
				void *addr = kmap_atomic(page + i);
				__cpuc_flush_dcache_area(addr, PAGE_SIZE);
				kunmap_atomic(addr);
			}
		} else {
			for (i = 0; i < compound_nr(page); i++) {
				void *addr = kmap_high_get(page + i);
				if (addr) {
					__cpuc_flush_dcache_area(addr, PAGE_SIZE);
					kunmap_high(page + i);
				}
			}
		}
	}

	/*
	 * If this is a page cache page, and we have an aliasing VIPT cache,
	 * we only need to do one flush - which would be at the relevant
	 * userspace colour, which is congruent with page->index.
	 */
	if (mapping && cache_is_vipt_aliasing())
		flush_pfn_alias(page_to_pfn(page),
				page->index << PAGE_SHIFT);
}