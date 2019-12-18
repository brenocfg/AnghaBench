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
struct request {scalar_t__ rq_disk; scalar_t__ write_hint; scalar_t__ ioprio; int /*<<< orphan*/  bio; int /*<<< orphan*/  q; } ;
struct bio {scalar_t__ bi_disk; scalar_t__ bi_write_hint; } ;

/* Variables and functions */
 scalar_t__ REQ_OP_WRITE_SAME ; 
 scalar_t__ bio_data_dir (struct bio*) ; 
 int /*<<< orphan*/  bio_mergeable (struct bio*) ; 
 scalar_t__ bio_op (struct bio*) ; 
 scalar_t__ bio_prio (struct bio*) ; 
 int blk_integrity_merge_bio (int /*<<< orphan*/ ,struct request*,struct bio*) ; 
 int /*<<< orphan*/  blk_write_same_mergeable (int /*<<< orphan*/ ,struct bio*) ; 
 scalar_t__ req_op (struct request*) ; 
 scalar_t__ rq_data_dir (struct request*) ; 
 int /*<<< orphan*/  rq_mergeable (struct request*) ; 

bool blk_rq_merge_ok(struct request *rq, struct bio *bio)
{
	if (!rq_mergeable(rq) || !bio_mergeable(bio))
		return false;

	if (req_op(rq) != bio_op(bio))
		return false;

	/* different data direction or already started, don't merge */
	if (bio_data_dir(bio) != rq_data_dir(rq))
		return false;

	/* must be same device */
	if (rq->rq_disk != bio->bi_disk)
		return false;

	/* only merge integrity protected bio into ditto rq */
	if (blk_integrity_merge_bio(rq->q, rq, bio) == false)
		return false;

	/* must be using the same buffer */
	if (req_op(rq) == REQ_OP_WRITE_SAME &&
	    !blk_write_same_mergeable(rq->bio, bio))
		return false;

	/*
	 * Don't allow merge of different write hints, or for a hint with
	 * non-hint IO.
	 */
	if (rq->write_hint != bio->bi_write_hint)
		return false;

	if (rq->ioprio != bio_prio(bio))
		return false;

	return true;
}