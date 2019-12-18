#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct page {int dummy; } ;
struct agp_memory {struct page** pages; int /*<<< orphan*/  page_count; } ;
struct agp_bridge_data {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  current_memory_agp; } ;

/* Variables and functions */
 int ENOMEM ; 
 int GFP_DMA32 ; 
 int GFP_KERNEL ; 
 int __GFP_ZERO ; 
 TYPE_1__* agp_bridge ; 
 struct page* alloc_page (int) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_page (struct page*) ; 
 int /*<<< orphan*/  map_page_into_agp (struct page*) ; 
 int /*<<< orphan*/  set_pages_array_uc (struct page**,size_t) ; 

int agp_generic_alloc_pages(struct agp_bridge_data *bridge, struct agp_memory *mem, size_t num_pages)
{
	struct page * page;
	int i, ret = -ENOMEM;

	for (i = 0; i < num_pages; i++) {
		page = alloc_page(GFP_KERNEL | GFP_DMA32 | __GFP_ZERO);
		/* agp_free_memory() needs gart address */
		if (page == NULL)
			goto out;

#ifndef CONFIG_X86
		map_page_into_agp(page);
#endif
		get_page(page);
		atomic_inc(&agp_bridge->current_memory_agp);

		mem->pages[i] = page;
		mem->page_count++;
	}

#ifdef CONFIG_X86
	set_pages_array_uc(mem->pages, num_pages);
#endif
	ret = 0;
out:
	return ret;
}