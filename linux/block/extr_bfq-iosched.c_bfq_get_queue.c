#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct bio {int dummy; } ;
struct bfq_queue {int /*<<< orphan*/  ref; int /*<<< orphan*/  entity; } ;
struct bfq_io_cq {int /*<<< orphan*/  ioprio; } ;
struct bfq_group {int dummy; } ;
struct bfq_data {struct bfq_queue oom_bfqq; TYPE_1__* queue; } ;
struct TYPE_4__ {int /*<<< orphan*/  pid; } ;
struct TYPE_3__ {int /*<<< orphan*/  node; } ;

/* Variables and functions */
 int GFP_NOWAIT ; 
 int IOPRIO_PRIO_CLASS (int /*<<< orphan*/ ) ; 
 int IOPRIO_PRIO_DATA (int /*<<< orphan*/ ) ; 
 int __GFP_NOWARN ; 
 int __GFP_ZERO ; 
 int /*<<< orphan*/  __bio_blkcg (struct bio*) ; 
 struct bfq_queue** bfq_async_queue_prio (struct bfq_data*,struct bfq_group*,int const,int const) ; 
 struct bfq_group* bfq_find_set_group (struct bfq_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfq_init_bfqq (struct bfq_data*,struct bfq_queue*,struct bfq_io_cq*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bfq_init_entity (int /*<<< orphan*/ *,struct bfq_group*) ; 
 int /*<<< orphan*/  bfq_log_bfqq (struct bfq_data*,struct bfq_queue*,char*,...) ; 
 int /*<<< orphan*/  bfq_pool ; 
 TYPE_2__* current ; 
 struct bfq_queue* kmem_cache_alloc_node (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 

__attribute__((used)) static struct bfq_queue *bfq_get_queue(struct bfq_data *bfqd,
				       struct bio *bio, bool is_sync,
				       struct bfq_io_cq *bic)
{
	const int ioprio = IOPRIO_PRIO_DATA(bic->ioprio);
	const int ioprio_class = IOPRIO_PRIO_CLASS(bic->ioprio);
	struct bfq_queue **async_bfqq = NULL;
	struct bfq_queue *bfqq;
	struct bfq_group *bfqg;

	rcu_read_lock();

	bfqg = bfq_find_set_group(bfqd, __bio_blkcg(bio));
	if (!bfqg) {
		bfqq = &bfqd->oom_bfqq;
		goto out;
	}

	if (!is_sync) {
		async_bfqq = bfq_async_queue_prio(bfqd, bfqg, ioprio_class,
						  ioprio);
		bfqq = *async_bfqq;
		if (bfqq)
			goto out;
	}

	bfqq = kmem_cache_alloc_node(bfq_pool,
				     GFP_NOWAIT | __GFP_ZERO | __GFP_NOWARN,
				     bfqd->queue->node);

	if (bfqq) {
		bfq_init_bfqq(bfqd, bfqq, bic, current->pid,
			      is_sync);
		bfq_init_entity(&bfqq->entity, bfqg);
		bfq_log_bfqq(bfqd, bfqq, "allocated");
	} else {
		bfqq = &bfqd->oom_bfqq;
		bfq_log_bfqq(bfqd, bfqq, "using oom bfqq");
		goto out;
	}

	/*
	 * Pin the queue now that it's allocated, scheduler exit will
	 * prune it.
	 */
	if (async_bfqq) {
		bfqq->ref++; /*
			      * Extra group reference, w.r.t. sync
			      * queue. This extra reference is removed
			      * only if bfqq->bfqg disappears, to
			      * guarantee that this queue is not freed
			      * until its group goes away.
			      */
		bfq_log_bfqq(bfqd, bfqq, "get_queue, bfqq not in async: %p, %d",
			     bfqq, bfqq->ref);
		*async_bfqq = bfqq;
	}

out:
	bfqq->ref++; /* get a process reference to this queue */
	bfq_log_bfqq(bfqd, bfqq, "get_queue, at end: %p, %d", bfqq, bfqq->ref);
	rcu_read_unlock();
	return bfqq;
}