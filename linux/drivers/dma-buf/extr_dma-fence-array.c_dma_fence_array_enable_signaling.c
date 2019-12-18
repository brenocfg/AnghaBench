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
struct dma_fence_array_cb {int /*<<< orphan*/  cb; struct dma_fence_array* array; } ;
struct dma_fence_array {unsigned int num_fences; int /*<<< orphan*/  num_pending; int /*<<< orphan*/  base; TYPE_1__** fences; } ;
struct dma_fence {int dummy; } ;
struct TYPE_2__ {int error; } ;

/* Variables and functions */
 scalar_t__ atomic_dec_and_test (int /*<<< orphan*/ *) ; 
 scalar_t__ dma_fence_add_callback (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_fence_array_cb_func ; 
 int /*<<< orphan*/  dma_fence_array_clear_pending_error (struct dma_fence_array*) ; 
 int /*<<< orphan*/  dma_fence_array_set_pending_error (struct dma_fence_array*,int) ; 
 int /*<<< orphan*/  dma_fence_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dma_fence_put (int /*<<< orphan*/ *) ; 
 struct dma_fence_array* to_dma_fence_array (struct dma_fence*) ; 

__attribute__((used)) static bool dma_fence_array_enable_signaling(struct dma_fence *fence)
{
	struct dma_fence_array *array = to_dma_fence_array(fence);
	struct dma_fence_array_cb *cb = (void *)(&array[1]);
	unsigned i;

	for (i = 0; i < array->num_fences; ++i) {
		cb[i].array = array;
		/*
		 * As we may report that the fence is signaled before all
		 * callbacks are complete, we need to take an additional
		 * reference count on the array so that we do not free it too
		 * early. The core fence handling will only hold the reference
		 * until we signal the array as complete (but that is now
		 * insufficient).
		 */
		dma_fence_get(&array->base);
		if (dma_fence_add_callback(array->fences[i], &cb[i].cb,
					   dma_fence_array_cb_func)) {
			int error = array->fences[i]->error;

			dma_fence_array_set_pending_error(array, error);
			dma_fence_put(&array->base);
			if (atomic_dec_and_test(&array->num_pending)) {
				dma_fence_array_clear_pending_error(array);
				return false;
			}
		}
	}

	return true;
}