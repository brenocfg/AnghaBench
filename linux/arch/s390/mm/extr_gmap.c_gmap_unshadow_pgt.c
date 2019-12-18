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
struct page {int /*<<< orphan*/  lru; } ;
struct gmap {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int PAGE_SHIFT ; 
 unsigned long _ASCE_TYPE_SEGMENT ; 
 unsigned long _SEGMENT_ENTRY_EMPTY ; 
 unsigned long _SEGMENT_ENTRY_ORIGIN ; 
 unsigned long _SEGMENT_INDEX ; 
 unsigned long _SEGMENT_SHIFT ; 
 scalar_t__ _SEGMENT_SIZE ; 
 int /*<<< orphan*/  __gmap_unshadow_pgt (struct gmap*,unsigned long,unsigned long*) ; 
 int __pa (unsigned long*) ; 
 int /*<<< orphan*/  gmap_call_notifier (struct gmap*,unsigned long,scalar_t__) ; 
 int /*<<< orphan*/  gmap_idte_one (unsigned long,unsigned long) ; 
 int /*<<< orphan*/  gmap_is_shadow (struct gmap*) ; 
 unsigned long* gmap_table_walk (struct gmap*,unsigned long,int) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  page_table_free_pgste (struct page*) ; 
 struct page* pfn_to_page (int) ; 

__attribute__((used)) static void gmap_unshadow_pgt(struct gmap *sg, unsigned long raddr)
{
	unsigned long sto, *ste, *pgt;
	struct page *page;

	BUG_ON(!gmap_is_shadow(sg));
	ste = gmap_table_walk(sg, raddr, 1); /* get segment pointer */
	if (!ste || !(*ste & _SEGMENT_ENTRY_ORIGIN))
		return;
	gmap_call_notifier(sg, raddr, raddr + _SEGMENT_SIZE - 1);
	sto = (unsigned long) (ste - ((raddr & _SEGMENT_INDEX) >> _SEGMENT_SHIFT));
	gmap_idte_one(sto | _ASCE_TYPE_SEGMENT, raddr);
	pgt = (unsigned long *)(*ste & _SEGMENT_ENTRY_ORIGIN);
	*ste = _SEGMENT_ENTRY_EMPTY;
	__gmap_unshadow_pgt(sg, raddr, pgt);
	/* Free page table */
	page = pfn_to_page(__pa(pgt) >> PAGE_SHIFT);
	list_del(&page->lru);
	page_table_free_pgste(page);
}