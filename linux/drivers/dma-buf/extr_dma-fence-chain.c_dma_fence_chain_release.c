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
struct dma_fence_chain {struct dma_fence* fence; int /*<<< orphan*/  prev; } ;
struct dma_fence {int /*<<< orphan*/  refcount; } ;

/* Variables and functions */
 int /*<<< orphan*/  RCU_INIT_POINTER (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dma_fence_free (struct dma_fence*) ; 
 int /*<<< orphan*/  dma_fence_put (struct dma_fence*) ; 
 int kref_read (int /*<<< orphan*/ *) ; 
 struct dma_fence* rcu_dereference_protected (int /*<<< orphan*/ ,int) ; 
 struct dma_fence_chain* to_dma_fence_chain (struct dma_fence*) ; 

__attribute__((used)) static void dma_fence_chain_release(struct dma_fence *fence)
{
	struct dma_fence_chain *chain = to_dma_fence_chain(fence);
	struct dma_fence *prev;

	/* Manually unlink the chain as much as possible to avoid recursion
	 * and potential stack overflow.
	 */
	while ((prev = rcu_dereference_protected(chain->prev, true))) {
		struct dma_fence_chain *prev_chain;

		if (kref_read(&prev->refcount) > 1)
		       break;

		prev_chain = to_dma_fence_chain(prev);
		if (!prev_chain)
			break;

		/* No need for atomic operations since we hold the last
		 * reference to prev_chain.
		 */
		chain->prev = prev_chain->prev;
		RCU_INIT_POINTER(prev_chain->prev, NULL);
		dma_fence_put(prev);
	}
	dma_fence_put(prev);

	dma_fence_put(chain->fence);
	dma_fence_free(fence);
}