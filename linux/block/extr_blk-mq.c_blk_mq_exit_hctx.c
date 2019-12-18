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
struct request_queue {int /*<<< orphan*/  unused_hctx_lock; int /*<<< orphan*/  unused_hctx_list; } ;
struct blk_mq_tag_set {TYPE_2__* ops; } ;
struct blk_mq_hw_ctx {int /*<<< orphan*/  hctx_list; TYPE_1__* fq; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* exit_hctx ) (struct blk_mq_hw_ctx*,unsigned int) ;int /*<<< orphan*/  (* exit_request ) (struct blk_mq_tag_set*,int /*<<< orphan*/ ,unsigned int) ;} ;
struct TYPE_3__ {int /*<<< orphan*/  flush_rq; } ;

/* Variables and functions */
 scalar_t__ blk_mq_hw_queue_mapped (struct blk_mq_hw_ctx*) ; 
 int /*<<< orphan*/  blk_mq_remove_cpuhp (struct blk_mq_hw_ctx*) ; 
 int /*<<< orphan*/  blk_mq_tag_idle (struct blk_mq_hw_ctx*) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct blk_mq_tag_set*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  stub2 (struct blk_mq_hw_ctx*,unsigned int) ; 

__attribute__((used)) static void blk_mq_exit_hctx(struct request_queue *q,
		struct blk_mq_tag_set *set,
		struct blk_mq_hw_ctx *hctx, unsigned int hctx_idx)
{
	if (blk_mq_hw_queue_mapped(hctx))
		blk_mq_tag_idle(hctx);

	if (set->ops->exit_request)
		set->ops->exit_request(set, hctx->fq->flush_rq, hctx_idx);

	if (set->ops->exit_hctx)
		set->ops->exit_hctx(hctx, hctx_idx);

	blk_mq_remove_cpuhp(hctx);

	spin_lock(&q->unused_hctx_lock);
	list_add(&hctx->hctx_list, &q->unused_hctx_list);
	spin_unlock(&q->unused_hctx_lock);
}