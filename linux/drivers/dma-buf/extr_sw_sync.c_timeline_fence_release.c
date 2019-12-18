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
struct sync_timeline {int /*<<< orphan*/  pt_tree; } ;
struct sync_pt {int /*<<< orphan*/  node; int /*<<< orphan*/  link; } ;
struct dma_fence {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  dma_fence_free (struct dma_fence*) ; 
 struct sync_timeline* dma_fence_parent (struct dma_fence*) ; 
 struct sync_pt* dma_fence_to_sync_pt (struct dma_fence*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rb_erase (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  sync_timeline_put (struct sync_timeline*) ; 

__attribute__((used)) static void timeline_fence_release(struct dma_fence *fence)
{
	struct sync_pt *pt = dma_fence_to_sync_pt(fence);
	struct sync_timeline *parent = dma_fence_parent(fence);
	unsigned long flags;

	spin_lock_irqsave(fence->lock, flags);
	if (!list_empty(&pt->link)) {
		list_del(&pt->link);
		rb_erase(&pt->node, &parent->pt_tree);
	}
	spin_unlock_irqrestore(fence->lock, flags);

	sync_timeline_put(parent);
	dma_fence_free(fence);
}