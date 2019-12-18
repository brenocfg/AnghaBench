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
struct dma_resv_list {unsigned int shared_count; int /*<<< orphan*/ * shared; int /*<<< orphan*/  flags; } ;
struct dma_resv {int /*<<< orphan*/  seq; int /*<<< orphan*/  fence; int /*<<< orphan*/  fence_excl; } ;
struct dma_fence {unsigned int shared_count; int /*<<< orphan*/ * shared; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_FENCE_FLAG_SIGNALED_BIT ; 
 int ENOMEM ; 
 int /*<<< orphan*/  RCU_INIT_POINTER (int /*<<< orphan*/ ,struct dma_resv_list*) ; 
 int /*<<< orphan*/  dma_fence_get_rcu (struct dma_resv_list*) ; 
 struct dma_resv_list* dma_fence_get_rcu_safe (int /*<<< orphan*/ *) ; 
 scalar_t__ dma_fence_is_signaled (struct dma_resv_list*) ; 
 int /*<<< orphan*/  dma_fence_put (struct dma_resv_list*) ; 
 int /*<<< orphan*/  dma_resv_assert_held (struct dma_resv*) ; 
 struct dma_resv_list* dma_resv_get_excl (struct dma_resv*) ; 
 struct dma_resv_list* dma_resv_get_list (struct dma_resv*) ; 
 struct dma_resv_list* dma_resv_list_alloc (unsigned int) ; 
 int /*<<< orphan*/  dma_resv_list_free (struct dma_resv_list*) ; 
 int /*<<< orphan*/  kfree (struct dma_resv_list*) ; 
 int /*<<< orphan*/  preempt_disable () ; 
 int /*<<< orphan*/  preempt_enable () ; 
 int /*<<< orphan*/  rcu_assign_pointer (int /*<<< orphan*/ ,struct dma_resv_list*) ; 
 struct dma_resv_list* rcu_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_seqcount_begin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_seqcount_end (int /*<<< orphan*/ *) ; 

int dma_resv_copy_fences(struct dma_resv *dst, struct dma_resv *src)
{
	struct dma_resv_list *src_list, *dst_list;
	struct dma_fence *old, *new;
	unsigned i;

	dma_resv_assert_held(dst);

	rcu_read_lock();
	src_list = rcu_dereference(src->fence);

retry:
	if (src_list) {
		unsigned shared_count = src_list->shared_count;

		rcu_read_unlock();

		dst_list = dma_resv_list_alloc(shared_count);
		if (!dst_list)
			return -ENOMEM;

		rcu_read_lock();
		src_list = rcu_dereference(src->fence);
		if (!src_list || src_list->shared_count > shared_count) {
			kfree(dst_list);
			goto retry;
		}

		dst_list->shared_count = 0;
		for (i = 0; i < src_list->shared_count; ++i) {
			struct dma_fence *fence;

			fence = rcu_dereference(src_list->shared[i]);
			if (test_bit(DMA_FENCE_FLAG_SIGNALED_BIT,
				     &fence->flags))
				continue;

			if (!dma_fence_get_rcu(fence)) {
				dma_resv_list_free(dst_list);
				src_list = rcu_dereference(src->fence);
				goto retry;
			}

			if (dma_fence_is_signaled(fence)) {
				dma_fence_put(fence);
				continue;
			}

			rcu_assign_pointer(dst_list->shared[dst_list->shared_count++], fence);
		}
	} else {
		dst_list = NULL;
	}

	new = dma_fence_get_rcu_safe(&src->fence_excl);
	rcu_read_unlock();

	src_list = dma_resv_get_list(dst);
	old = dma_resv_get_excl(dst);

	preempt_disable();
	write_seqcount_begin(&dst->seq);
	/* write_seqcount_begin provides the necessary memory barrier */
	RCU_INIT_POINTER(dst->fence_excl, new);
	RCU_INIT_POINTER(dst->fence, dst_list);
	write_seqcount_end(&dst->seq);
	preempt_enable();

	dma_resv_list_free(src_list);
	dma_fence_put(old);

	return 0;
}