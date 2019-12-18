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
struct dma_resv_list {int dummy; } ;
struct dma_resv {int /*<<< orphan*/  lock; int /*<<< orphan*/  fence; int /*<<< orphan*/  fence_excl; } ;
struct dma_fence {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dma_fence_put (struct dma_fence*) ; 
 int /*<<< orphan*/  dma_resv_list_free (struct dma_resv_list*) ; 
 void* rcu_dereference_protected (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ww_mutex_destroy (int /*<<< orphan*/ *) ; 

void dma_resv_fini(struct dma_resv *obj)
{
	struct dma_resv_list *fobj;
	struct dma_fence *excl;

	/*
	 * This object should be dead and all references must have
	 * been released to it, so no need to be protected with rcu.
	 */
	excl = rcu_dereference_protected(obj->fence_excl, 1);
	if (excl)
		dma_fence_put(excl);

	fobj = rcu_dereference_protected(obj->fence, 1);
	dma_resv_list_free(fobj);
	ww_mutex_destroy(&obj->lock);
}