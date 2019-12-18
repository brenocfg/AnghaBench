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
struct page {int dummy; } ;
struct drbd_bitmap {struct page** bm_pages; } ;

/* Variables and functions */
 scalar_t__ kmap_atomic (struct page*) ; 

__attribute__((used)) static unsigned long *__bm_map_pidx(struct drbd_bitmap *b, unsigned int idx)
{
	struct page *page = b->bm_pages[idx];
	return (unsigned long *) kmap_atomic(page);
}