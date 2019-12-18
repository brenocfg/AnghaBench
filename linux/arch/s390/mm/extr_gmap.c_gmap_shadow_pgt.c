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
struct gmap {int /*<<< orphan*/  guest_table_lock; int /*<<< orphan*/  pt_list; int /*<<< orphan*/  mm; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int EAGAIN ; 
 int ENOMEM ; 
 unsigned long GMAP_SHADOW_FAKE_TABLE ; 
 unsigned long PAGE_MASK ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 unsigned long _SEGMENT_ENTRY ; 
 unsigned long _SEGMENT_ENTRY_INVALID ; 
 unsigned long _SEGMENT_ENTRY_LARGE ; 
 unsigned long _SEGMENT_ENTRY_ORIGIN ; 
 unsigned long _SEGMENT_ENTRY_PROTECT ; 
 unsigned long _SEGMENT_MASK ; 
 unsigned long _SHADOW_RMAP_SEGMENT ; 
 int /*<<< orphan*/  gmap_is_shadow (struct gmap*) ; 
 int gmap_protect_rmap (struct gmap*,unsigned long,unsigned long,int /*<<< orphan*/ ) ; 
 unsigned long* gmap_table_walk (struct gmap*,unsigned long,int) ; 
 int /*<<< orphan*/  gmap_unshadow_pgt (struct gmap*,unsigned long) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct page* page_table_alloc_pgste (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  page_table_free_pgste (struct page*) ; 
 scalar_t__ page_to_phys (struct page*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

int gmap_shadow_pgt(struct gmap *sg, unsigned long saddr, unsigned long pgt,
		    int fake)
{
	unsigned long raddr, origin;
	unsigned long *s_pgt, *table;
	struct page *page;
	int rc;

	BUG_ON(!gmap_is_shadow(sg) || (pgt & _SEGMENT_ENTRY_LARGE));
	/* Allocate a shadow page table */
	page = page_table_alloc_pgste(sg->mm);
	if (!page)
		return -ENOMEM;
	page->index = pgt & _SEGMENT_ENTRY_ORIGIN;
	if (fake)
		page->index |= GMAP_SHADOW_FAKE_TABLE;
	s_pgt = (unsigned long *) page_to_phys(page);
	/* Install shadow page table */
	spin_lock(&sg->guest_table_lock);
	table = gmap_table_walk(sg, saddr, 1); /* get segment pointer */
	if (!table) {
		rc = -EAGAIN;		/* Race with unshadow */
		goto out_free;
	}
	if (!(*table & _SEGMENT_ENTRY_INVALID)) {
		rc = 0;			/* Already established */
		goto out_free;
	} else if (*table & _SEGMENT_ENTRY_ORIGIN) {
		rc = -EAGAIN;		/* Race with shadow */
		goto out_free;
	}
	/* mark as invalid as long as the parent table is not protected */
	*table = (unsigned long) s_pgt | _SEGMENT_ENTRY |
		 (pgt & _SEGMENT_ENTRY_PROTECT) | _SEGMENT_ENTRY_INVALID;
	list_add(&page->lru, &sg->pt_list);
	if (fake) {
		/* nothing to protect for fake tables */
		*table &= ~_SEGMENT_ENTRY_INVALID;
		spin_unlock(&sg->guest_table_lock);
		return 0;
	}
	spin_unlock(&sg->guest_table_lock);
	/* Make pgt read-only in parent gmap page table (not the pgste) */
	raddr = (saddr & _SEGMENT_MASK) | _SHADOW_RMAP_SEGMENT;
	origin = pgt & _SEGMENT_ENTRY_ORIGIN & PAGE_MASK;
	rc = gmap_protect_rmap(sg, raddr, origin, PAGE_SIZE);
	spin_lock(&sg->guest_table_lock);
	if (!rc) {
		table = gmap_table_walk(sg, saddr, 1);
		if (!table || (*table & _SEGMENT_ENTRY_ORIGIN) !=
			      (unsigned long) s_pgt)
			rc = -EAGAIN;		/* Race with unshadow */
		else
			*table &= ~_SEGMENT_ENTRY_INVALID;
	} else {
		gmap_unshadow_pgt(sg, raddr);
	}
	spin_unlock(&sg->guest_table_lock);
	return rc;
out_free:
	spin_unlock(&sg->guest_table_lock);
	page_table_free_pgste(page);
	return rc;

}