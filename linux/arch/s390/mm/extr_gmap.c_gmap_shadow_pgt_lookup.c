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
struct page {unsigned long index; } ;
struct gmap {int /*<<< orphan*/  guest_table_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int EAGAIN ; 
 unsigned long GMAP_SHADOW_FAKE_TABLE ; 
 unsigned long PAGE_SHIFT ; 
 unsigned long _SEGMENT_ENTRY_INVALID ; 
 unsigned long _SEGMENT_ENTRY_PROTECT ; 
 int /*<<< orphan*/  gmap_is_shadow (struct gmap*) ; 
 unsigned long* gmap_table_walk (struct gmap*,unsigned long,int) ; 
 struct page* pfn_to_page (unsigned long) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

int gmap_shadow_pgt_lookup(struct gmap *sg, unsigned long saddr,
			   unsigned long *pgt, int *dat_protection,
			   int *fake)
{
	unsigned long *table;
	struct page *page;
	int rc;

	BUG_ON(!gmap_is_shadow(sg));
	spin_lock(&sg->guest_table_lock);
	table = gmap_table_walk(sg, saddr, 1); /* get segment pointer */
	if (table && !(*table & _SEGMENT_ENTRY_INVALID)) {
		/* Shadow page tables are full pages (pte+pgste) */
		page = pfn_to_page(*table >> PAGE_SHIFT);
		*pgt = page->index & ~GMAP_SHADOW_FAKE_TABLE;
		*dat_protection = !!(*table & _SEGMENT_ENTRY_PROTECT);
		*fake = !!(page->index & GMAP_SHADOW_FAKE_TABLE);
		rc = 0;
	} else  {
		rc = -EAGAIN;
	}
	spin_unlock(&sg->guest_table_lock);
	return rc;

}