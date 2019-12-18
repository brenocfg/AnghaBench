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
struct page {unsigned long index; int /*<<< orphan*/  lru; } ;
struct gmap {int /*<<< orphan*/  guest_table_lock; int /*<<< orphan*/  crst_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  CRST_ALLOC_ORDER ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 unsigned long _REGION_ENTRY_INVALID ; 
 unsigned long _REGION_ENTRY_LENGTH ; 
 unsigned long _REGION_ENTRY_TYPE_MASK ; 
 int /*<<< orphan*/  __free_pages (struct page*,int /*<<< orphan*/ ) ; 
 struct page* alloc_pages (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  crst_table_init (unsigned long*,unsigned long) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ page_to_phys (struct page*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int gmap_alloc_table(struct gmap *gmap, unsigned long *table,
			    unsigned long init, unsigned long gaddr)
{
	struct page *page;
	unsigned long *new;

	/* since we dont free the gmap table until gmap_free we can unlock */
	page = alloc_pages(GFP_KERNEL, CRST_ALLOC_ORDER);
	if (!page)
		return -ENOMEM;
	new = (unsigned long *) page_to_phys(page);
	crst_table_init(new, init);
	spin_lock(&gmap->guest_table_lock);
	if (*table & _REGION_ENTRY_INVALID) {
		list_add(&page->lru, &gmap->crst_list);
		*table = (unsigned long) new | _REGION_ENTRY_LENGTH |
			(*table & _REGION_ENTRY_TYPE_MASK);
		page->index = gaddr;
		page = NULL;
	}
	spin_unlock(&gmap->guest_table_lock);
	if (page)
		__free_pages(page, CRST_ALLOC_ORDER);
	return 0;
}