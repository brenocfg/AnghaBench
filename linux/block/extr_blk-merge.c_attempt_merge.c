#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct request_queue {int dummy; } ;
struct request {scalar_t__ rq_disk; scalar_t__ write_hint; scalar_t__ ioprio; int rq_flags; int cmd_flags; scalar_t__ start_time_ns; int /*<<< orphan*/ * bio; int /*<<< orphan*/  __data_len; TYPE_1__* biotail; } ;
struct TYPE_2__ {int /*<<< orphan*/ * bi_next; } ;

/* Variables and functions */
#define  ELEVATOR_BACK_MERGE 129 
#define  ELEVATOR_DISCARD_MERGE 128 
 int REQ_FAILFAST_MASK ; 
 scalar_t__ REQ_OP_WRITE_SAME ; 
 int RQF_MIXED_MERGE ; 
 int /*<<< orphan*/  blk_account_io_merge (struct request*) ; 
 int /*<<< orphan*/  blk_discard_mergable (struct request*) ; 
 scalar_t__ blk_rq_bytes (struct request*) ; 
 int /*<<< orphan*/  blk_rq_set_mixed_merge (struct request*) ; 
 int blk_try_req_merge (struct request*,struct request*) ; 
 int /*<<< orphan*/  blk_write_same_mergeable (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  elv_merge_requests (struct request_queue*,struct request*,struct request*) ; 
 int /*<<< orphan*/  ll_merge_requests_fn (struct request_queue*,struct request*,struct request*) ; 
 int /*<<< orphan*/  req_attempt_discard_merge (struct request_queue*,struct request*,struct request*) ; 
 scalar_t__ req_op (struct request*) ; 
 scalar_t__ rq_data_dir (struct request*) ; 
 int /*<<< orphan*/  rq_mergeable (struct request*) ; 

__attribute__((used)) static struct request *attempt_merge(struct request_queue *q,
				     struct request *req, struct request *next)
{
	if (!rq_mergeable(req) || !rq_mergeable(next))
		return NULL;

	if (req_op(req) != req_op(next))
		return NULL;

	if (rq_data_dir(req) != rq_data_dir(next)
	    || req->rq_disk != next->rq_disk)
		return NULL;

	if (req_op(req) == REQ_OP_WRITE_SAME &&
	    !blk_write_same_mergeable(req->bio, next->bio))
		return NULL;

	/*
	 * Don't allow merge of different write hints, or for a hint with
	 * non-hint IO.
	 */
	if (req->write_hint != next->write_hint)
		return NULL;

	if (req->ioprio != next->ioprio)
		return NULL;

	/*
	 * If we are allowed to merge, then append bio list
	 * from next to rq and release next. merge_requests_fn
	 * will have updated segment counts, update sector
	 * counts here. Handle DISCARDs separately, as they
	 * have separate settings.
	 */

	switch (blk_try_req_merge(req, next)) {
	case ELEVATOR_DISCARD_MERGE:
		if (!req_attempt_discard_merge(q, req, next))
			return NULL;
		break;
	case ELEVATOR_BACK_MERGE:
		if (!ll_merge_requests_fn(q, req, next))
			return NULL;
		break;
	default:
		return NULL;
	}

	/*
	 * If failfast settings disagree or any of the two is already
	 * a mixed merge, mark both as mixed before proceeding.  This
	 * makes sure that all involved bios have mixable attributes
	 * set properly.
	 */
	if (((req->rq_flags | next->rq_flags) & RQF_MIXED_MERGE) ||
	    (req->cmd_flags & REQ_FAILFAST_MASK) !=
	    (next->cmd_flags & REQ_FAILFAST_MASK)) {
		blk_rq_set_mixed_merge(req);
		blk_rq_set_mixed_merge(next);
	}

	/*
	 * At this point we have either done a back merge or front merge. We
	 * need the smaller start_time_ns of the merged requests to be the
	 * current request for accounting purposes.
	 */
	if (next->start_time_ns < req->start_time_ns)
		req->start_time_ns = next->start_time_ns;

	req->biotail->bi_next = next->bio;
	req->biotail = next->biotail;

	req->__data_len += blk_rq_bytes(next);

	if (!blk_discard_mergable(req))
		elv_merge_requests(q, req, next);

	/*
	 * 'next' is going away, so update stats accordingly
	 */
	blk_account_io_merge(next);

	/*
	 * ownership of bio passed from next to req, return 'next' for
	 * the caller to free
	 */
	next->bio = NULL;
	return next;
}