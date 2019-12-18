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
struct dma_resv_list {int shared_max; unsigned int shared_count; int /*<<< orphan*/ * shared; } ;
struct dma_resv {int /*<<< orphan*/  seq; int /*<<< orphan*/  fence; int /*<<< orphan*/  fence_excl; } ;
struct dma_fence {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int GFP_KERNEL ; 
 int GFP_NOWAIT ; 
 int __GFP_NOWARN ; 
 int /*<<< orphan*/  dma_fence_get_rcu (struct dma_fence*) ; 
 int /*<<< orphan*/  dma_fence_put (struct dma_fence*) ; 
 int /*<<< orphan*/  kfree (struct dma_fence**) ; 
 struct dma_fence** krealloc (struct dma_fence**,size_t,int) ; 
 void* rcu_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 unsigned int read_seqcount_begin (int /*<<< orphan*/ *) ; 
 scalar_t__ read_seqcount_retry (int /*<<< orphan*/ *,unsigned int) ; 

int dma_resv_get_fences_rcu(struct dma_resv *obj,
			    struct dma_fence **pfence_excl,
			    unsigned *pshared_count,
			    struct dma_fence ***pshared)
{
	struct dma_fence **shared = NULL;
	struct dma_fence *fence_excl;
	unsigned int shared_count;
	int ret = 1;

	do {
		struct dma_resv_list *fobj;
		unsigned int i, seq;
		size_t sz = 0;

		shared_count = i = 0;

		rcu_read_lock();
		seq = read_seqcount_begin(&obj->seq);

		fence_excl = rcu_dereference(obj->fence_excl);
		if (fence_excl && !dma_fence_get_rcu(fence_excl))
			goto unlock;

		fobj = rcu_dereference(obj->fence);
		if (fobj)
			sz += sizeof(*shared) * fobj->shared_max;

		if (!pfence_excl && fence_excl)
			sz += sizeof(*shared);

		if (sz) {
			struct dma_fence **nshared;

			nshared = krealloc(shared, sz,
					   GFP_NOWAIT | __GFP_NOWARN);
			if (!nshared) {
				rcu_read_unlock();

				dma_fence_put(fence_excl);
				fence_excl = NULL;

				nshared = krealloc(shared, sz, GFP_KERNEL);
				if (nshared) {
					shared = nshared;
					continue;
				}

				ret = -ENOMEM;
				break;
			}
			shared = nshared;
			shared_count = fobj ? fobj->shared_count : 0;
			for (i = 0; i < shared_count; ++i) {
				shared[i] = rcu_dereference(fobj->shared[i]);
				if (!dma_fence_get_rcu(shared[i]))
					break;
			}
		}

		if (i != shared_count || read_seqcount_retry(&obj->seq, seq)) {
			while (i--)
				dma_fence_put(shared[i]);
			dma_fence_put(fence_excl);
			goto unlock;
		}

		ret = 0;
unlock:
		rcu_read_unlock();
	} while (ret);

	if (pfence_excl)
		*pfence_excl = fence_excl;
	else if (fence_excl)
		shared[shared_count++] = fence_excl;

	if (!shared_count) {
		kfree(shared);
		shared = NULL;
	}

	*pshared_count = shared_count;
	*pshared = shared;
	return ret;
}