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
struct dma_fence {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int EINVAL ; 
 int dma_fence_signal_locked (struct dma_fence*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ ,unsigned long) ; 

int dma_fence_signal(struct dma_fence *fence)
{
	unsigned long flags;
	int ret;

	if (!fence)
		return -EINVAL;

	spin_lock_irqsave(fence->lock, flags);
	ret = dma_fence_signal_locked(fence);
	spin_unlock_irqrestore(fence->lock, flags);

	return ret;
}