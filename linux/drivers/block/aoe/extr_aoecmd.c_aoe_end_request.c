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
struct request_queue {int dummy; } ;
struct request {struct bio* bio; } ;
struct TYPE_3__ {int /*<<< orphan*/  bi_size; } ;
struct bio {int /*<<< orphan*/  bi_status; TYPE_1__ bi_iter; } ;
struct TYPE_4__ {struct request* rq; } ;
struct aoedev {TYPE_2__ ip; struct request_queue* blkq; } ;
typedef  int /*<<< orphan*/  blk_status_t ;

/* Variables and functions */
 int /*<<< orphan*/  BLK_STS_IOERR ; 
 int /*<<< orphan*/  BLK_STS_OK ; 
 int /*<<< orphan*/  __blk_mq_end_request (struct request*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blk_mq_run_hw_queues (struct request_queue*,int) ; 
 scalar_t__ blk_update_request (struct request*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
aoe_end_request(struct aoedev *d, struct request *rq, int fastfail)
{
	struct bio *bio;
	int bok;
	struct request_queue *q;
	blk_status_t err = BLK_STS_OK;

	q = d->blkq;
	if (rq == d->ip.rq)
		d->ip.rq = NULL;
	do {
		bio = rq->bio;
		bok = !fastfail && !bio->bi_status;
		if (!bok)
			err = BLK_STS_IOERR;
	} while (blk_update_request(rq, bok ? BLK_STS_OK : BLK_STS_IOERR, bio->bi_iter.bi_size));

	__blk_mq_end_request(rq, err);

	/* cf. http://lkml.org/lkml/2006/10/31/28 */
	if (!fastfail)
		blk_mq_run_hw_queues(q, true);
}