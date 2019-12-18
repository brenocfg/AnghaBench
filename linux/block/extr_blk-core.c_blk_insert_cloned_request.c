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
struct request {TYPE_1__* rq_disk; } ;
typedef  int /*<<< orphan*/  blk_status_t ;
struct TYPE_2__ {int /*<<< orphan*/  part0; } ;

/* Variables and functions */
 int /*<<< orphan*/  BLK_STS_IOERR ; 
 int /*<<< orphan*/  blk_account_io_start (struct request*,int) ; 
 scalar_t__ blk_cloned_rq_check_limits (struct request_queue*,struct request*) ; 
 int /*<<< orphan*/  blk_mq_request_issue_directly (struct request*,int) ; 
 scalar_t__ blk_queue_io_stat (struct request_queue*) ; 
 int /*<<< orphan*/  blk_rq_bytes (struct request*) ; 
 scalar_t__ should_fail_request (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

blk_status_t blk_insert_cloned_request(struct request_queue *q, struct request *rq)
{
	if (blk_cloned_rq_check_limits(q, rq))
		return BLK_STS_IOERR;

	if (rq->rq_disk &&
	    should_fail_request(&rq->rq_disk->part0, blk_rq_bytes(rq)))
		return BLK_STS_IOERR;

	if (blk_queue_io_stat(q))
		blk_account_io_start(rq, true);

	/*
	 * Since we have a scheduler attached on the top device,
	 * bypass a potential scheduler on the bottom device for
	 * insert.
	 */
	return blk_mq_request_issue_directly(rq, true);
}