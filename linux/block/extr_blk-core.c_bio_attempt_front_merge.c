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
struct request {int const cmd_flags; int /*<<< orphan*/  __data_len; int /*<<< orphan*/  __sector; struct bio* bio; int /*<<< orphan*/  q; } ;
struct TYPE_2__ {scalar_t__ bi_size; int /*<<< orphan*/  bi_sector; } ;
struct bio {int const bi_opf; TYPE_1__ bi_iter; struct bio* bi_next; } ;

/* Variables and functions */
 int const REQ_FAILFAST_MASK ; 
 int /*<<< orphan*/  blk_account_io_start (struct request*,int) ; 
 int /*<<< orphan*/  blk_rq_set_mixed_merge (struct request*) ; 
 int /*<<< orphan*/  ll_front_merge_fn (struct request*,struct bio*,unsigned int) ; 
 int /*<<< orphan*/  rq_qos_merge (int /*<<< orphan*/ ,struct request*,struct bio*) ; 
 int /*<<< orphan*/  trace_block_bio_frontmerge (int /*<<< orphan*/ ,struct request*,struct bio*) ; 

bool bio_attempt_front_merge(struct request *req, struct bio *bio,
		unsigned int nr_segs)
{
	const int ff = bio->bi_opf & REQ_FAILFAST_MASK;

	if (!ll_front_merge_fn(req, bio, nr_segs))
		return false;

	trace_block_bio_frontmerge(req->q, req, bio);
	rq_qos_merge(req->q, req, bio);

	if ((req->cmd_flags & REQ_FAILFAST_MASK) != ff)
		blk_rq_set_mixed_merge(req);

	bio->bi_next = req->bio;
	req->bio = bio;

	req->__sector = bio->bi_iter.bi_sector;
	req->__data_len += bio->bi_iter.bi_size;

	blk_account_io_start(req, false);
	return true;
}