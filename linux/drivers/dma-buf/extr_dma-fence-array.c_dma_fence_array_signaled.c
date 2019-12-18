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
struct dma_fence_array {int /*<<< orphan*/  num_pending; } ;
struct dma_fence {int dummy; } ;

/* Variables and functions */
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 struct dma_fence_array* to_dma_fence_array (struct dma_fence*) ; 

__attribute__((used)) static bool dma_fence_array_signaled(struct dma_fence *fence)
{
	struct dma_fence_array *array = to_dma_fence_array(fence);

	return atomic_read(&array->num_pending) <= 0;
}