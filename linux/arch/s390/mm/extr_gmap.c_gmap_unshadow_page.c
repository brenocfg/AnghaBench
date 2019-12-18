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
struct gmap {int /*<<< orphan*/  mm; } ;
typedef  int /*<<< orphan*/  pte_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 unsigned long _PAGE_INVALID ; 
 scalar_t__ _PAGE_SIZE ; 
 int /*<<< orphan*/  gmap_call_notifier (struct gmap*,unsigned long,scalar_t__) ; 
 int /*<<< orphan*/  gmap_is_shadow (struct gmap*) ; 
 unsigned long* gmap_table_walk (struct gmap*,unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ptep_unshadow_pte (int /*<<< orphan*/ ,unsigned long,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void gmap_unshadow_page(struct gmap *sg, unsigned long raddr)
{
	unsigned long *table;

	BUG_ON(!gmap_is_shadow(sg));
	table = gmap_table_walk(sg, raddr, 0); /* get page table pointer */
	if (!table || *table & _PAGE_INVALID)
		return;
	gmap_call_notifier(sg, raddr, raddr + _PAGE_SIZE - 1);
	ptep_unshadow_pte(sg->mm, raddr, (pte_t *) table);
}