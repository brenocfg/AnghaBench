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
struct request {struct bio* bio; } ;
struct loop_cmd {scalar_t__ ret; scalar_t__ use_aio; } ;
struct bio {struct bio* bi_next; } ;
typedef  int /*<<< orphan*/  blk_status_t ;

/* Variables and functions */
 int /*<<< orphan*/  BLK_STS_IOERR ; 
 int /*<<< orphan*/  BLK_STS_OK ; 
 scalar_t__ REQ_OP_READ ; 
 int /*<<< orphan*/  blk_mq_end_request (struct request*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blk_mq_requeue_request (struct request*,int) ; 
 struct loop_cmd* blk_mq_rq_to_pdu (struct request*) ; 
 scalar_t__ blk_rq_bytes (struct request*) ; 
 int /*<<< orphan*/  blk_update_request (struct request*,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ req_op (struct request*) ; 
 int /*<<< orphan*/  zero_fill_bio (struct bio*) ; 

__attribute__((used)) static void lo_complete_rq(struct request *rq)
{
	struct loop_cmd *cmd = blk_mq_rq_to_pdu(rq);
	blk_status_t ret = BLK_STS_OK;

	if (!cmd->use_aio || cmd->ret < 0 || cmd->ret == blk_rq_bytes(rq) ||
	    req_op(rq) != REQ_OP_READ) {
		if (cmd->ret < 0)
			ret = BLK_STS_IOERR;
		goto end_io;
	}

	/*
	 * Short READ - if we got some data, advance our request and
	 * retry it. If we got no data, end the rest with EIO.
	 */
	if (cmd->ret) {
		blk_update_request(rq, BLK_STS_OK, cmd->ret);
		cmd->ret = 0;
		blk_mq_requeue_request(rq, true);
	} else {
		if (cmd->use_aio) {
			struct bio *bio = rq->bio;

			while (bio) {
				zero_fill_bio(bio);
				bio = bio->bi_next;
			}
		}
		ret = BLK_STS_IOERR;
end_io:
		blk_mq_end_request(rq, ret);
	}
}