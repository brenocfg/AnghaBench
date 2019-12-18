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
struct page {int /*<<< orphan*/  flags; } ;
struct address_space {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PG_dcache_clean ; 
 struct page* ZERO_PAGE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dcache_wbinv_all () ; 
 int /*<<< orphan*/  icache_inv_all () ; 
 int /*<<< orphan*/  page_mapcount (struct page*) ; 
 struct address_space* page_mapping_file (struct page*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void flush_dcache_page(struct page *page)
{
	struct address_space *mapping;

	if (page == ZERO_PAGE(0))
		return;

	mapping = page_mapping_file(page);

	if (mapping && !page_mapcount(page))
		clear_bit(PG_dcache_clean, &page->flags);
	else {
		dcache_wbinv_all();
		if (mapping)
			icache_inv_all();
		set_bit(PG_dcache_clean, &page->flags);
	}
}