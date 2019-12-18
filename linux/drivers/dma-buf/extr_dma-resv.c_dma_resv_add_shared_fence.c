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
struct dma_resv_list {unsigned int shared_count; unsigned int shared_max; int /*<<< orphan*/ * shared; } ;
struct dma_resv {int /*<<< orphan*/  seq; } ;
struct dma_fence {scalar_t__ context; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  RCU_INIT_POINTER (int /*<<< orphan*/ ,struct dma_fence*) ; 
 int /*<<< orphan*/  dma_fence_get (struct dma_fence*) ; 
 scalar_t__ dma_fence_is_signaled (struct dma_fence*) ; 
 int /*<<< orphan*/  dma_fence_put (struct dma_fence*) ; 
 int /*<<< orphan*/  dma_resv_assert_held (struct dma_resv*) ; 
 struct dma_resv_list* dma_resv_get_list (struct dma_resv*) ; 
 int /*<<< orphan*/  dma_resv_held (struct dma_resv*) ; 
 int /*<<< orphan*/  preempt_disable () ; 
 int /*<<< orphan*/  preempt_enable () ; 
 struct dma_fence* rcu_dereference_protected (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smp_store_mb (unsigned int,unsigned int) ; 
 int /*<<< orphan*/  write_seqcount_begin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_seqcount_end (int /*<<< orphan*/ *) ; 

void dma_resv_add_shared_fence(struct dma_resv *obj, struct dma_fence *fence)
{
	struct dma_resv_list *fobj;
	struct dma_fence *old;
	unsigned int i, count;

	dma_fence_get(fence);

	dma_resv_assert_held(obj);

	fobj = dma_resv_get_list(obj);
	count = fobj->shared_count;

	preempt_disable();
	write_seqcount_begin(&obj->seq);

	for (i = 0; i < count; ++i) {

		old = rcu_dereference_protected(fobj->shared[i],
						dma_resv_held(obj));
		if (old->context == fence->context ||
		    dma_fence_is_signaled(old))
			goto replace;
	}

	BUG_ON(fobj->shared_count >= fobj->shared_max);
	old = NULL;
	count++;

replace:
	RCU_INIT_POINTER(fobj->shared[i], fence);
	/* pointer update must be visible before we extend the shared_count */
	smp_store_mb(fobj->shared_count, count);

	write_seqcount_end(&obj->seq);
	preempt_enable();
	dma_fence_put(old);
}