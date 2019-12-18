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
struct dma_fence {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_FENCE_FLAG_SIGNALED_BIT ; 
 struct dma_fence* dma_fence_get_rcu (struct dma_fence*) ; 
 int /*<<< orphan*/  dma_fence_is_signaled (struct dma_fence*) ; 
 int /*<<< orphan*/  dma_fence_put (struct dma_fence*) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline int dma_resv_test_signaled_single(struct dma_fence *passed_fence)
{
	struct dma_fence *fence, *lfence = passed_fence;
	int ret = 1;

	if (!test_bit(DMA_FENCE_FLAG_SIGNALED_BIT, &lfence->flags)) {
		fence = dma_fence_get_rcu(lfence);
		if (!fence)
			return -1;

		ret = !!dma_fence_is_signaled(fence);
		dma_fence_put(fence);
	}
	return ret;
}