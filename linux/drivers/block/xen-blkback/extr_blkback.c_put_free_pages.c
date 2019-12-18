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
struct xen_blkif_ring {int free_pages_num; int /*<<< orphan*/  free_pages_lock; int /*<<< orphan*/  free_pages; } ;
struct page {int /*<<< orphan*/  lru; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static inline void put_free_pages(struct xen_blkif_ring *ring, struct page **page,
                                  int num)
{
	unsigned long flags;
	int i;

	spin_lock_irqsave(&ring->free_pages_lock, flags);
	for (i = 0; i < num; i++)
		list_add(&page[i]->lru, &ring->free_pages);
	ring->free_pages_num += num;
	spin_unlock_irqrestore(&ring->free_pages_lock, flags);
}