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
typedef  int /*<<< orphan*/  phys_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_BOOKE ; 
 scalar_t__ IS_ENABLED (int /*<<< orphan*/ ) ; 
 int PAGE_SHIFT ; 
 scalar_t__ PageCompound (struct page*) ; 
 int /*<<< orphan*/  __flush_dcache_icache (void*) ; 
 int /*<<< orphan*/  __flush_dcache_icache_phys (int) ; 
 int /*<<< orphan*/  flush_dcache_icache_hugepage (struct page*) ; 
 void* kmap_atomic (struct page*) ; 
 int /*<<< orphan*/  kunmap_atomic (void*) ; 
 void* page_address (struct page*) ; 
 int page_to_pfn (struct page*) ; 

void flush_dcache_icache_page(struct page *page)
{
#ifdef CONFIG_HUGETLB_PAGE
	if (PageCompound(page)) {
		flush_dcache_icache_hugepage(page);
		return;
	}
#endif
#if defined(CONFIG_PPC_8xx) || defined(CONFIG_PPC64)
	/* On 8xx there is no need to kmap since highmem is not supported */
	__flush_dcache_icache(page_address(page));
#else
	if (IS_ENABLED(CONFIG_BOOKE) || sizeof(phys_addr_t) > sizeof(void *)) {
		void *start = kmap_atomic(page);
		__flush_dcache_icache(start);
		kunmap_atomic(start);
	} else {
		__flush_dcache_icache_phys(page_to_pfn(page) << PAGE_SHIFT);
	}
#endif
}