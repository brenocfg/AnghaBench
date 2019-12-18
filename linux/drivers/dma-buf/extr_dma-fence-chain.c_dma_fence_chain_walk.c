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
struct dma_fence_chain {int /*<<< orphan*/  prev; struct dma_fence* fence; } ;
struct dma_fence {int dummy; } ;

/* Variables and functions */
 struct dma_fence* cmpxchg (void**,void*,void*) ; 
 struct dma_fence* dma_fence_chain_get_prev (struct dma_fence_chain*) ; 
 int /*<<< orphan*/  dma_fence_is_signaled (struct dma_fence*) ; 
 int /*<<< orphan*/  dma_fence_put (struct dma_fence*) ; 
 struct dma_fence_chain* to_dma_fence_chain (struct dma_fence*) ; 

struct dma_fence *dma_fence_chain_walk(struct dma_fence *fence)
{
	struct dma_fence_chain *chain, *prev_chain;
	struct dma_fence *prev, *replacement, *tmp;

	chain = to_dma_fence_chain(fence);
	if (!chain) {
		dma_fence_put(fence);
		return NULL;
	}

	while ((prev = dma_fence_chain_get_prev(chain))) {

		prev_chain = to_dma_fence_chain(prev);
		if (prev_chain) {
			if (!dma_fence_is_signaled(prev_chain->fence))
				break;

			replacement = dma_fence_chain_get_prev(prev_chain);
		} else {
			if (!dma_fence_is_signaled(prev))
				break;

			replacement = NULL;
		}

		tmp = cmpxchg((void **)&chain->prev, (void *)prev, (void *)replacement);
		if (tmp == prev)
			dma_fence_put(tmp);
		else
			dma_fence_put(replacement);
		dma_fence_put(prev);
	}

	dma_fence_put(fence);
	return prev;
}