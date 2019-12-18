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
struct address_space {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_HIGHMEM ; 
 int /*<<< orphan*/  IS_ENABLED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  __cpuc_flush_dcache_area (void*,int /*<<< orphan*/ ) ; 
 scalar_t__ cache_is_vipt_aliasing () ; 
 scalar_t__ cache_is_vivt () ; 
 scalar_t__ mapping_mapped (struct address_space*) ; 
 void* page_address (struct page*) ; 
 struct address_space* page_mapping_file (struct page*) ; 

void flush_kernel_dcache_page(struct page *page)
{
	if (cache_is_vivt() || cache_is_vipt_aliasing()) {
		struct address_space *mapping;

		mapping = page_mapping_file(page);

		if (!mapping || mapping_mapped(mapping)) {
			void *addr;

			addr = page_address(page);
			/*
			 * kmap_atomic() doesn't set the page virtual
			 * address for highmem pages, and
			 * kunmap_atomic() takes care of cache
			 * flushing already.
			 */
			if (!IS_ENABLED(CONFIG_HIGHMEM) || addr)
				__cpuc_flush_dcache_area(addr, PAGE_SIZE);
		}
	}
}