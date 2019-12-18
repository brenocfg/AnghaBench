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
struct gmap {int edat_level; int /*<<< orphan*/  guest_table_lock; int /*<<< orphan*/  crst_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  CRST_ALLOC_ORDER ; 
 int EAGAIN ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 unsigned long GMAP_SHADOW_FAKE_TABLE ; 
 unsigned long PAGE_SIZE ; 
 unsigned long _REGION3_ENTRY_LARGE ; 
 unsigned long _REGION3_MASK ; 
 unsigned long _REGION_ENTRY_INVALID ; 
 unsigned long _REGION_ENTRY_LENGTH ; 
 unsigned long _REGION_ENTRY_OFFSET ; 
 unsigned long _REGION_ENTRY_ORIGIN ; 
 unsigned long _REGION_ENTRY_PROTECT ; 
 unsigned long _REGION_ENTRY_TYPE_R3 ; 
 int /*<<< orphan*/  _SEGMENT_ENTRY_EMPTY ; 
 unsigned long _SHADOW_RMAP_REGION3 ; 
 int /*<<< orphan*/  __free_pages (struct page*,int /*<<< orphan*/ ) ; 
 struct page* alloc_pages (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  crst_table_init (unsigned long*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gmap_is_shadow (struct gmap*) ; 
 int gmap_protect_rmap (struct gmap*,unsigned long,unsigned long,unsigned long) ; 
 unsigned long* gmap_table_walk (struct gmap*,unsigned long,int) ; 
 int /*<<< orphan*/  gmap_unshadow_sgt (struct gmap*,unsigned long) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ page_to_phys (struct page*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

int gmap_shadow_sgt(struct gmap *sg, unsigned long saddr, unsigned long sgt,
		    int fake)
{
	unsigned long raddr, origin, offset, len;
	unsigned long *s_sgt, *table;
	struct page *page;
	int rc;

	BUG_ON(!gmap_is_shadow(sg) || (sgt & _REGION3_ENTRY_LARGE));
	/* Allocate a shadow segment table */
	page = alloc_pages(GFP_KERNEL, CRST_ALLOC_ORDER);
	if (!page)
		return -ENOMEM;
	page->index = sgt & _REGION_ENTRY_ORIGIN;
	if (fake)
		page->index |= GMAP_SHADOW_FAKE_TABLE;
	s_sgt = (unsigned long *) page_to_phys(page);
	/* Install shadow region second table */
	spin_lock(&sg->guest_table_lock);
	table = gmap_table_walk(sg, saddr, 2); /* get region-3 pointer */
	if (!table) {
		rc = -EAGAIN;		/* Race with unshadow */
		goto out_free;
	}
	if (!(*table & _REGION_ENTRY_INVALID)) {
		rc = 0;			/* Already established */
		goto out_free;
	} else if (*table & _REGION_ENTRY_ORIGIN) {
		rc = -EAGAIN;		/* Race with shadow */
		goto out_free;
	}
	crst_table_init(s_sgt, _SEGMENT_ENTRY_EMPTY);
	/* mark as invalid as long as the parent table is not protected */
	*table = (unsigned long) s_sgt | _REGION_ENTRY_LENGTH |
		 _REGION_ENTRY_TYPE_R3 | _REGION_ENTRY_INVALID;
	if (sg->edat_level >= 1)
		*table |= sgt & _REGION_ENTRY_PROTECT;
	list_add(&page->lru, &sg->crst_list);
	if (fake) {
		/* nothing to protect for fake tables */
		*table &= ~_REGION_ENTRY_INVALID;
		spin_unlock(&sg->guest_table_lock);
		return 0;
	}
	spin_unlock(&sg->guest_table_lock);
	/* Make sgt read-only in parent gmap page table */
	raddr = (saddr & _REGION3_MASK) | _SHADOW_RMAP_REGION3;
	origin = sgt & _REGION_ENTRY_ORIGIN;
	offset = ((sgt & _REGION_ENTRY_OFFSET) >> 6) * PAGE_SIZE;
	len = ((sgt & _REGION_ENTRY_LENGTH) + 1) * PAGE_SIZE - offset;
	rc = gmap_protect_rmap(sg, raddr, origin + offset, len);
	spin_lock(&sg->guest_table_lock);
	if (!rc) {
		table = gmap_table_walk(sg, saddr, 2);
		if (!table || (*table & _REGION_ENTRY_ORIGIN) !=
			      (unsigned long) s_sgt)
			rc = -EAGAIN;		/* Race with unshadow */
		else
			*table &= ~_REGION_ENTRY_INVALID;
	} else {
		gmap_unshadow_sgt(sg, raddr);
	}
	spin_unlock(&sg->guest_table_lock);
	return rc;
out_free:
	spin_unlock(&sg->guest_table_lock);
	__free_pages(page, CRST_ALLOC_ORDER);
	return rc;
}