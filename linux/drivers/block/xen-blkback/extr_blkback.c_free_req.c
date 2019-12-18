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
struct xen_blkif_ring {int /*<<< orphan*/  pending_free_wq; int /*<<< orphan*/  pending_free_lock; int /*<<< orphan*/  pending_free; } ;
struct pending_req {int /*<<< orphan*/  free_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void free_req(struct xen_blkif_ring *ring, struct pending_req *req)
{
	unsigned long flags;
	int was_empty;

	spin_lock_irqsave(&ring->pending_free_lock, flags);
	was_empty = list_empty(&ring->pending_free);
	list_add(&req->free_list, &ring->pending_free);
	spin_unlock_irqrestore(&ring->pending_free_lock, flags);
	if (was_empty)
		wake_up(&ring->pending_free_wq);
}