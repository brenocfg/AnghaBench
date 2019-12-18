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
 size_t NR_DTL_PAGE ; 
 unsigned long PHYS_PFN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  __pa (void*) ; 
 size_t dtl_nr_pages ; 
 struct page** dtl_page_store ; 
 int /*<<< orphan*/  is_dtl_page_shared (struct page*) ; 
 struct page* pfn_to_page (unsigned long) ; 
 int /*<<< orphan*/  uv_share_page (unsigned long,int) ; 

void dtl_cache_ctor(void *addr)
{
	unsigned long pfn = PHYS_PFN(__pa(addr));
	struct page *page = pfn_to_page(pfn);

	if (!is_dtl_page_shared(page)) {
		dtl_page_store[dtl_nr_pages] = page;
		dtl_nr_pages++;
		WARN_ON(dtl_nr_pages >= NR_DTL_PAGE);
		uv_share_page(pfn, 1);
	}
}