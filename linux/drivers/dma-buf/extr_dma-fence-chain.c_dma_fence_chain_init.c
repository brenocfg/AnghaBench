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
typedef  int /*<<< orphan*/  uint64_t ;
struct dma_fence_chain {int /*<<< orphan*/  lock; int /*<<< orphan*/  base; scalar_t__ prev_seqno; int /*<<< orphan*/  work; struct dma_fence* fence; int /*<<< orphan*/  prev; } ;
struct dma_fence {scalar_t__ seqno; int /*<<< orphan*/  context; int /*<<< orphan*/  ops; } ;

/* Variables and functions */
 scalar_t__ __dma_fence_is_later (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_fence_chain_irq_work ; 
 int /*<<< orphan*/  dma_fence_chain_ops ; 
 int /*<<< orphan*/  dma_fence_context_alloc (int) ; 
 int /*<<< orphan*/  dma_fence_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_irq_work (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  max (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_assign_pointer (int /*<<< orphan*/ ,struct dma_fence*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 struct dma_fence_chain* to_dma_fence_chain (struct dma_fence*) ; 

void dma_fence_chain_init(struct dma_fence_chain *chain,
			  struct dma_fence *prev,
			  struct dma_fence *fence,
			  uint64_t seqno)
{
	struct dma_fence_chain *prev_chain = to_dma_fence_chain(prev);
	uint64_t context;

	spin_lock_init(&chain->lock);
	rcu_assign_pointer(chain->prev, prev);
	chain->fence = fence;
	chain->prev_seqno = 0;
	init_irq_work(&chain->work, dma_fence_chain_irq_work);

	/* Try to reuse the context of the previous chain node. */
	if (prev_chain && __dma_fence_is_later(seqno, prev->seqno, prev->ops)) {
		context = prev->context;
		chain->prev_seqno = prev->seqno;
	} else {
		context = dma_fence_context_alloc(1);
		/* Make sure that we always have a valid sequence number. */
		if (prev_chain)
			seqno = max(prev->seqno, seqno);
	}

	dma_fence_init(&chain->base, &dma_fence_chain_ops,
		       &chain->lock, context, seqno);
}