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
struct page_change_data {int /*<<< orphan*/  clear_mask; int /*<<< orphan*/  set_mask; } ;
struct page {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PAGE_SIZE ; 
 int PTE_RDONLY ; 
 int PTE_VALID ; 
 int PTE_WRITE ; 
 int /*<<< orphan*/  __pgprot (int) ; 
 int apply_to_page_range (int /*<<< orphan*/ *,unsigned long,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct page_change_data*) ; 
 int /*<<< orphan*/  change_page_range ; 
 int /*<<< orphan*/  init_mm ; 
 scalar_t__ page_address (struct page*) ; 
 int /*<<< orphan*/  rodata_full ; 

int set_direct_map_default_noflush(struct page *page)
{
	struct page_change_data data = {
		.set_mask = __pgprot(PTE_VALID | PTE_WRITE),
		.clear_mask = __pgprot(PTE_RDONLY),
	};

	if (!rodata_full)
		return 0;

	return apply_to_page_range(&init_mm,
				   (unsigned long)page_address(page),
				   PAGE_SIZE, change_page_range, &data);
}