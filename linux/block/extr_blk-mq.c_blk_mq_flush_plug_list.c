#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct request_queue {int dummy; } ;
struct request {int /*<<< orphan*/  queuelist; struct blk_mq_hw_ctx* mq_hctx; struct blk_mq_ctx* mq_ctx; struct request_queue* q; } ;
struct blk_plug {int rq_count; scalar_t__ multiple_queues; int /*<<< orphan*/  mq_list; } ;
struct blk_mq_hw_ctx {int dummy; } ;
struct blk_mq_ctx {int dummy; } ;
struct TYPE_9__ {int /*<<< orphan*/  next; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  LIST_HEAD (TYPE_1__) ; 
 int /*<<< orphan*/  blk_mq_sched_insert_requests (struct blk_mq_hw_ctx*,struct blk_mq_ctx*,TYPE_1__*,int) ; 
 TYPE_1__ list ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_empty (TYPE_1__*) ; 
 struct request* list_entry_rq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_sort (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_splice_init (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  plug_rq_cmp ; 
 TYPE_1__ rq_list ; 
 int /*<<< orphan*/  trace_block_unplug (struct request_queue*,unsigned int,int) ; 

void blk_mq_flush_plug_list(struct blk_plug *plug, bool from_schedule)
{
	struct blk_mq_hw_ctx *this_hctx;
	struct blk_mq_ctx *this_ctx;
	struct request_queue *this_q;
	struct request *rq;
	LIST_HEAD(list);
	LIST_HEAD(rq_list);
	unsigned int depth;

	list_splice_init(&plug->mq_list, &list);

	if (plug->rq_count > 2 && plug->multiple_queues)
		list_sort(NULL, &list, plug_rq_cmp);

	plug->rq_count = 0;

	this_q = NULL;
	this_hctx = NULL;
	this_ctx = NULL;
	depth = 0;

	while (!list_empty(&list)) {
		rq = list_entry_rq(list.next);
		list_del_init(&rq->queuelist);
		BUG_ON(!rq->q);
		if (rq->mq_hctx != this_hctx || rq->mq_ctx != this_ctx) {
			if (this_hctx) {
				trace_block_unplug(this_q, depth, !from_schedule);
				blk_mq_sched_insert_requests(this_hctx, this_ctx,
								&rq_list,
								from_schedule);
			}

			this_q = rq->q;
			this_ctx = rq->mq_ctx;
			this_hctx = rq->mq_hctx;
			depth = 0;
		}

		depth++;
		list_add_tail(&rq->queuelist, &rq_list);
	}

	/*
	 * If 'this_hctx' is set, we know we have entries to complete
	 * on 'rq_list'. Do those.
	 */
	if (this_hctx) {
		trace_block_unplug(this_q, depth, !from_schedule);
		blk_mq_sched_insert_requests(this_hctx, this_ctx, &rq_list,
						from_schedule);
	}
}