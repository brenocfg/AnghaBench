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
typedef  void* u64 ;
struct dma_fence_ops {int /*<<< orphan*/  get_timeline_name; int /*<<< orphan*/  get_driver_name; } ;
struct dma_fence {unsigned long flags; scalar_t__ error; void* seqno; void* context; int /*<<< orphan*/ * lock; int /*<<< orphan*/  cb_list; struct dma_fence_ops const* ops; int /*<<< orphan*/  refcount; } ;
typedef  int /*<<< orphan*/  spinlock_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kref_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_dma_fence_init (struct dma_fence*) ; 

void
dma_fence_init(struct dma_fence *fence, const struct dma_fence_ops *ops,
	       spinlock_t *lock, u64 context, u64 seqno)
{
	BUG_ON(!lock);
	BUG_ON(!ops || !ops->get_driver_name || !ops->get_timeline_name);

	kref_init(&fence->refcount);
	fence->ops = ops;
	INIT_LIST_HEAD(&fence->cb_list);
	fence->lock = lock;
	fence->context = context;
	fence->seqno = seqno;
	fence->flags = 0UL;
	fence->error = 0;

	trace_dma_fence_init(fence);
}