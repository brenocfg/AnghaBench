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
typedef  size_t u32 ;
struct dma_resv_list {size_t shared_count; int /*<<< orphan*/ * shared; } ;
struct dma_resv {int /*<<< orphan*/  seq; int /*<<< orphan*/  fence_excl; } ;
struct dma_fence {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  RCU_INIT_POINTER (int /*<<< orphan*/ ,struct dma_fence*) ; 
 int /*<<< orphan*/  dma_fence_get (struct dma_fence*) ; 
 int /*<<< orphan*/  dma_fence_put (struct dma_fence*) ; 
 int /*<<< orphan*/  dma_resv_assert_held (struct dma_resv*) ; 
 struct dma_fence* dma_resv_get_excl (struct dma_resv*) ; 
 struct dma_resv_list* dma_resv_get_list (struct dma_resv*) ; 
 int /*<<< orphan*/  dma_resv_held (struct dma_resv*) ; 
 int /*<<< orphan*/  preempt_disable () ; 
 int /*<<< orphan*/  preempt_enable () ; 
 struct dma_fence* rcu_dereference_protected (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_seqcount_begin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_seqcount_end (int /*<<< orphan*/ *) ; 

void dma_resv_add_excl_fence(struct dma_resv *obj, struct dma_fence *fence)
{
	struct dma_fence *old_fence = dma_resv_get_excl(obj);
	struct dma_resv_list *old;
	u32 i = 0;

	dma_resv_assert_held(obj);

	old = dma_resv_get_list(obj);
	if (old)
		i = old->shared_count;

	if (fence)
		dma_fence_get(fence);

	preempt_disable();
	write_seqcount_begin(&obj->seq);
	/* write_seqcount_begin provides the necessary memory barrier */
	RCU_INIT_POINTER(obj->fence_excl, fence);
	if (old)
		old->shared_count = 0;
	write_seqcount_end(&obj->seq);
	preempt_enable();

	/* inplace update, no shared fences */
	while (i--)
		dma_fence_put(rcu_dereference_protected(old->shared[i],
						dma_resv_held(obj)));

	dma_fence_put(old_fence);
}