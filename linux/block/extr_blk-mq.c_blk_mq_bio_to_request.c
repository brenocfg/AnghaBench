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
struct request {int /*<<< orphan*/  write_hint; int /*<<< orphan*/  __sector; int /*<<< orphan*/  cmd_flags; } ;
struct TYPE_2__ {int /*<<< orphan*/  bi_sector; } ;
struct bio {int bi_opf; int /*<<< orphan*/  bi_write_hint; TYPE_1__ bi_iter; } ;

/* Variables and functions */
 int /*<<< orphan*/  REQ_FAILFAST_MASK ; 
 int REQ_RAHEAD ; 
 int /*<<< orphan*/  blk_account_io_start (struct request*,int) ; 
 int /*<<< orphan*/  blk_rq_bio_prep (struct request*,struct bio*,unsigned int) ; 

__attribute__((used)) static void blk_mq_bio_to_request(struct request *rq, struct bio *bio,
		unsigned int nr_segs)
{
	if (bio->bi_opf & REQ_RAHEAD)
		rq->cmd_flags |= REQ_FAILFAST_MASK;

	rq->__sector = bio->bi_iter.bi_sector;
	rq->write_hint = bio->bi_write_hint;
	blk_rq_bio_prep(rq, bio, nr_segs);

	blk_account_io_start(rq, true);
}