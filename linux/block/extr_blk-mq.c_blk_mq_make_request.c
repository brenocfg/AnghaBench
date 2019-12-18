#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct request_queue {int nr_hw_queues; scalar_t__ elevator; TYPE_1__* mq_ops; } ;
struct request {TYPE_2__* mq_hctx; int /*<<< orphan*/  queuelist; } ;
struct TYPE_8__ {int /*<<< orphan*/  prev; } ;
struct blk_plug {unsigned int rq_count; TYPE_3__ mq_list; } ;
struct blk_mq_alloc_data {int cmd_flags; TYPE_2__* hctx; int /*<<< orphan*/  flags; } ;
struct bio {int bi_opf; } ;
typedef  int /*<<< orphan*/  blk_qc_t ;
struct TYPE_7__ {int /*<<< orphan*/  dispatch_busy; } ;
struct TYPE_6__ {scalar_t__ commit_rqs; } ;

/* Variables and functions */
 unsigned int BLK_MAX_REQUEST_COUNT ; 
 scalar_t__ BLK_PLUG_FLUSH_SIZE ; 
 int /*<<< orphan*/  BLK_QC_T_NONE ; 
 int REQ_NOWAIT ; 
 int /*<<< orphan*/  __blk_queue_split (struct request_queue*,struct bio**,unsigned int*) ; 
 int /*<<< orphan*/  bio_integrity_prep (struct bio*) ; 
 int /*<<< orphan*/  bio_wouldblock_error (struct bio*) ; 
 int /*<<< orphan*/  blk_add_rq_to_plug (struct blk_plug*,struct request*) ; 
 scalar_t__ blk_attempt_plug_merge (struct request_queue*,struct bio*,unsigned int,struct request**) ; 
 int /*<<< orphan*/  blk_flush_plug_list (struct blk_plug*,int) ; 
 int /*<<< orphan*/  blk_insert_flush (struct request*) ; 
 int /*<<< orphan*/  blk_mq_bio_to_request (struct request*,struct bio*,unsigned int) ; 
 struct request* blk_mq_get_request (struct request_queue*,struct bio*,struct blk_mq_alloc_data*) ; 
 struct blk_plug* blk_mq_plug (struct request_queue*,struct bio*) ; 
 int /*<<< orphan*/  blk_mq_run_hw_queue (TYPE_2__*,int) ; 
 scalar_t__ blk_mq_sched_bio_merge (struct request_queue*,struct bio*,unsigned int) ; 
 int /*<<< orphan*/  blk_mq_sched_insert_request (struct request*,int,int,int) ; 
 int /*<<< orphan*/  blk_mq_try_issue_directly (TYPE_2__*,struct request*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  blk_queue_bounce (struct request_queue*,struct bio**) ; 
 int /*<<< orphan*/  blk_queue_nomerges (struct request_queue*) ; 
 int /*<<< orphan*/  blk_queue_nonrot (struct request_queue*) ; 
 scalar_t__ blk_rq_bytes (struct request*) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 scalar_t__ list_empty (TYPE_3__*) ; 
 struct request* list_entry_rq (int /*<<< orphan*/ ) ; 
 int op_is_flush (int) ; 
 int op_is_sync (int) ; 
 int /*<<< orphan*/  request_to_qc_t (TYPE_2__*,struct request*) ; 
 int /*<<< orphan*/  rq_qos_cleanup (struct request_queue*,struct bio*) ; 
 int /*<<< orphan*/  rq_qos_throttle (struct request_queue*,struct bio*) ; 
 int /*<<< orphan*/  rq_qos_track (struct request_queue*,struct request*,struct bio*) ; 
 int /*<<< orphan*/  trace_block_getrq (struct request_queue*,struct bio*,int) ; 
 int /*<<< orphan*/  trace_block_plug (struct request_queue*) ; 
 int /*<<< orphan*/  trace_block_unplug (struct request_queue*,int,int) ; 
 scalar_t__ unlikely (int const) ; 

__attribute__((used)) static blk_qc_t blk_mq_make_request(struct request_queue *q, struct bio *bio)
{
	const int is_sync = op_is_sync(bio->bi_opf);
	const int is_flush_fua = op_is_flush(bio->bi_opf);
	struct blk_mq_alloc_data data = { .flags = 0};
	struct request *rq;
	struct blk_plug *plug;
	struct request *same_queue_rq = NULL;
	unsigned int nr_segs;
	blk_qc_t cookie;

	blk_queue_bounce(q, &bio);
	__blk_queue_split(q, &bio, &nr_segs);

	if (!bio_integrity_prep(bio))
		return BLK_QC_T_NONE;

	if (!is_flush_fua && !blk_queue_nomerges(q) &&
	    blk_attempt_plug_merge(q, bio, nr_segs, &same_queue_rq))
		return BLK_QC_T_NONE;

	if (blk_mq_sched_bio_merge(q, bio, nr_segs))
		return BLK_QC_T_NONE;

	rq_qos_throttle(q, bio);

	data.cmd_flags = bio->bi_opf;
	rq = blk_mq_get_request(q, bio, &data);
	if (unlikely(!rq)) {
		rq_qos_cleanup(q, bio);
		if (bio->bi_opf & REQ_NOWAIT)
			bio_wouldblock_error(bio);
		return BLK_QC_T_NONE;
	}

	trace_block_getrq(q, bio, bio->bi_opf);

	rq_qos_track(q, rq, bio);

	cookie = request_to_qc_t(data.hctx, rq);

	blk_mq_bio_to_request(rq, bio, nr_segs);

	plug = blk_mq_plug(q, bio);
	if (unlikely(is_flush_fua)) {
		/* bypass scheduler for flush rq */
		blk_insert_flush(rq);
		blk_mq_run_hw_queue(data.hctx, true);
	} else if (plug && (q->nr_hw_queues == 1 || q->mq_ops->commit_rqs ||
				!blk_queue_nonrot(q))) {
		/*
		 * Use plugging if we have a ->commit_rqs() hook as well, as
		 * we know the driver uses bd->last in a smart fashion.
		 *
		 * Use normal plugging if this disk is slow HDD, as sequential
		 * IO may benefit a lot from plug merging.
		 */
		unsigned int request_count = plug->rq_count;
		struct request *last = NULL;

		if (!request_count)
			trace_block_plug(q);
		else
			last = list_entry_rq(plug->mq_list.prev);

		if (request_count >= BLK_MAX_REQUEST_COUNT || (last &&
		    blk_rq_bytes(last) >= BLK_PLUG_FLUSH_SIZE)) {
			blk_flush_plug_list(plug, false);
			trace_block_plug(q);
		}

		blk_add_rq_to_plug(plug, rq);
	} else if (q->elevator) {
		blk_mq_sched_insert_request(rq, false, true, true);
	} else if (plug && !blk_queue_nomerges(q)) {
		/*
		 * We do limited plugging. If the bio can be merged, do that.
		 * Otherwise the existing request in the plug list will be
		 * issued. So the plug list will have one request at most
		 * The plug list might get flushed before this. If that happens,
		 * the plug list is empty, and same_queue_rq is invalid.
		 */
		if (list_empty(&plug->mq_list))
			same_queue_rq = NULL;
		if (same_queue_rq) {
			list_del_init(&same_queue_rq->queuelist);
			plug->rq_count--;
		}
		blk_add_rq_to_plug(plug, rq);
		trace_block_plug(q);

		if (same_queue_rq) {
			data.hctx = same_queue_rq->mq_hctx;
			trace_block_unplug(q, 1, true);
			blk_mq_try_issue_directly(data.hctx, same_queue_rq,
					&cookie);
		}
	} else if ((q->nr_hw_queues > 1 && is_sync) ||
			!data.hctx->dispatch_busy) {
		blk_mq_try_issue_directly(data.hctx, rq, &cookie);
	} else {
		blk_mq_sched_insert_request(rq, false, true, true);
	}

	return cookie;
}