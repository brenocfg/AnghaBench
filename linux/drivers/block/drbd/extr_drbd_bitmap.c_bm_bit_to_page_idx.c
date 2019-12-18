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
typedef  int u64 ;
struct drbd_bitmap {unsigned int bm_number_of_pages; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int PAGE_SHIFT ; 

__attribute__((used)) static unsigned int bm_bit_to_page_idx(struct drbd_bitmap *b, u64 bitnr)
{
	/* page_nr = (bitnr/8) >> PAGE_SHIFT; */
	unsigned int page_nr = bitnr >> (PAGE_SHIFT + 3);
	BUG_ON(page_nr >= b->bm_number_of_pages);
	return page_nr;
}