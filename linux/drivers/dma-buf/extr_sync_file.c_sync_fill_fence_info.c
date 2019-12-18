#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct sync_fence_info {int status; int /*<<< orphan*/  timestamp_ns; int /*<<< orphan*/  driver_name; int /*<<< orphan*/  obj_name; } ;
struct dma_fence {int /*<<< orphan*/  timestamp; int /*<<< orphan*/  flags; TYPE_1__* ops; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* get_driver_name ) (struct dma_fence*) ;int /*<<< orphan*/  (* get_timeline_name ) (struct dma_fence*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_FENCE_FLAG_SIGNALED_BIT ; 
 int /*<<< orphan*/  DMA_FENCE_FLAG_TIMESTAMP_BIT ; 
 int /*<<< orphan*/  cpu_relax () ; 
 int dma_fence_get_status (struct dma_fence*) ; 
 int /*<<< orphan*/  ktime_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ktime_to_ns (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (struct dma_fence*) ; 
 int /*<<< orphan*/  stub2 (struct dma_fence*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int sync_fill_fence_info(struct dma_fence *fence,
				 struct sync_fence_info *info)
{
	strlcpy(info->obj_name, fence->ops->get_timeline_name(fence),
		sizeof(info->obj_name));
	strlcpy(info->driver_name, fence->ops->get_driver_name(fence),
		sizeof(info->driver_name));

	info->status = dma_fence_get_status(fence);
	while (test_bit(DMA_FENCE_FLAG_SIGNALED_BIT, &fence->flags) &&
	       !test_bit(DMA_FENCE_FLAG_TIMESTAMP_BIT, &fence->flags))
		cpu_relax();
	info->timestamp_ns =
		test_bit(DMA_FENCE_FLAG_TIMESTAMP_BIT, &fence->flags) ?
		ktime_to_ns(fence->timestamp) :
		ktime_set(0, 0);

	return info->status;
}