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
struct page {int /*<<< orphan*/  lru; scalar_t__ index; } ;
struct gmap {unsigned long* table; unsigned long asce; unsigned long asce_end; int /*<<< orphan*/  crst_list; int /*<<< orphan*/  ref_count; int /*<<< orphan*/  shadow_lock; int /*<<< orphan*/  guest_table_lock; int /*<<< orphan*/  host_to_rmap; int /*<<< orphan*/  host_to_guest; int /*<<< orphan*/  guest_to_host; int /*<<< orphan*/  pt_list; int /*<<< orphan*/  children; } ;

/* Variables and functions */
 int /*<<< orphan*/  CRST_ALLOC_ORDER ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INIT_RADIX_TREE (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 unsigned long _ASCE_TABLE_LENGTH ; 
 unsigned long _ASCE_TYPE_REGION1 ; 
 unsigned long _ASCE_TYPE_REGION2 ; 
 unsigned long _ASCE_TYPE_REGION3 ; 
 unsigned long _ASCE_TYPE_SEGMENT ; 
 unsigned long _ASCE_USER_BITS ; 
 unsigned long _REGION1_ENTRY_EMPTY ; 
 unsigned long _REGION1_SIZE ; 
 unsigned long _REGION2_ENTRY_EMPTY ; 
 unsigned long _REGION2_SIZE ; 
 unsigned long _REGION3_ENTRY_EMPTY ; 
 unsigned long _REGION3_SIZE ; 
 unsigned long _SEGMENT_ENTRY_EMPTY ; 
 unsigned long __pa (unsigned long*) ; 
 struct page* alloc_pages (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  crst_table_init (unsigned long*,unsigned long) ; 
 int /*<<< orphan*/  kfree (struct gmap*) ; 
 struct gmap* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ page_to_phys (struct page*) ; 
 int /*<<< orphan*/  refcount_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct gmap *gmap_alloc(unsigned long limit)
{
	struct gmap *gmap;
	struct page *page;
	unsigned long *table;
	unsigned long etype, atype;

	if (limit < _REGION3_SIZE) {
		limit = _REGION3_SIZE - 1;
		atype = _ASCE_TYPE_SEGMENT;
		etype = _SEGMENT_ENTRY_EMPTY;
	} else if (limit < _REGION2_SIZE) {
		limit = _REGION2_SIZE - 1;
		atype = _ASCE_TYPE_REGION3;
		etype = _REGION3_ENTRY_EMPTY;
	} else if (limit < _REGION1_SIZE) {
		limit = _REGION1_SIZE - 1;
		atype = _ASCE_TYPE_REGION2;
		etype = _REGION2_ENTRY_EMPTY;
	} else {
		limit = -1UL;
		atype = _ASCE_TYPE_REGION1;
		etype = _REGION1_ENTRY_EMPTY;
	}
	gmap = kzalloc(sizeof(struct gmap), GFP_KERNEL);
	if (!gmap)
		goto out;
	INIT_LIST_HEAD(&gmap->crst_list);
	INIT_LIST_HEAD(&gmap->children);
	INIT_LIST_HEAD(&gmap->pt_list);
	INIT_RADIX_TREE(&gmap->guest_to_host, GFP_KERNEL);
	INIT_RADIX_TREE(&gmap->host_to_guest, GFP_ATOMIC);
	INIT_RADIX_TREE(&gmap->host_to_rmap, GFP_ATOMIC);
	spin_lock_init(&gmap->guest_table_lock);
	spin_lock_init(&gmap->shadow_lock);
	refcount_set(&gmap->ref_count, 1);
	page = alloc_pages(GFP_KERNEL, CRST_ALLOC_ORDER);
	if (!page)
		goto out_free;
	page->index = 0;
	list_add(&page->lru, &gmap->crst_list);
	table = (unsigned long *) page_to_phys(page);
	crst_table_init(table, etype);
	gmap->table = table;
	gmap->asce = atype | _ASCE_TABLE_LENGTH |
		_ASCE_USER_BITS | __pa(table);
	gmap->asce_end = limit;
	return gmap;

out_free:
	kfree(gmap);
out:
	return NULL;
}