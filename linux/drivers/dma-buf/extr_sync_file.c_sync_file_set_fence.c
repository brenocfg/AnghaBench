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
struct sync_file {struct dma_fence* fence; } ;
struct dma_fence {int dummy; } ;
struct dma_fence_array {struct dma_fence base; } ;

/* Variables and functions */
 int ENOMEM ; 
 struct dma_fence_array* dma_fence_array_create (int,struct dma_fence**,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  dma_fence_context_alloc (int) ; 
 int /*<<< orphan*/  kfree (struct dma_fence**) ; 

__attribute__((used)) static int sync_file_set_fence(struct sync_file *sync_file,
			       struct dma_fence **fences, int num_fences)
{
	struct dma_fence_array *array;

	/*
	 * The reference for the fences in the new sync_file and held
	 * in add_fence() during the merge procedure, so for num_fences == 1
	 * we already own a new reference to the fence. For num_fence > 1
	 * we own the reference of the dma_fence_array creation.
	 */
	if (num_fences == 1) {
		sync_file->fence = fences[0];
		kfree(fences);
	} else {
		array = dma_fence_array_create(num_fences, fences,
					       dma_fence_context_alloc(1),
					       1, false);
		if (!array)
			return -ENOMEM;

		sync_file->fence = &array->base;
	}

	return 0;
}