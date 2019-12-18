#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct request {TYPE_3__* bio; TYPE_1__* q; } ;
struct loop_device {scalar_t__ lo_state; int use_dio; int /*<<< orphan*/  worker; } ;
struct loop_cmd {int use_aio; int /*<<< orphan*/  work; int /*<<< orphan*/ * css; } ;
struct blk_mq_queue_data {struct request* rq; } ;
struct blk_mq_hw_ctx {int dummy; } ;
typedef  int /*<<< orphan*/  blk_status_t ;
struct TYPE_6__ {scalar_t__ bi_blkg; } ;
struct TYPE_5__ {int /*<<< orphan*/  css; } ;
struct TYPE_4__ {struct loop_device* queuedata; } ;

/* Variables and functions */
 int /*<<< orphan*/  BLK_STS_IOERR ; 
 int /*<<< orphan*/  BLK_STS_OK ; 
 scalar_t__ Lo_bound ; 
#define  REQ_OP_DISCARD 130 
#define  REQ_OP_FLUSH 129 
#define  REQ_OP_WRITE_ZEROES 128 
 TYPE_2__* bio_blkcg (TYPE_3__*) ; 
 struct loop_cmd* blk_mq_rq_to_pdu (struct request*) ; 
 int /*<<< orphan*/  blk_mq_start_request (struct request*) ; 
 int /*<<< orphan*/  css_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kthread_queue_work (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int req_op (struct request*) ; 

__attribute__((used)) static blk_status_t loop_queue_rq(struct blk_mq_hw_ctx *hctx,
		const struct blk_mq_queue_data *bd)
{
	struct request *rq = bd->rq;
	struct loop_cmd *cmd = blk_mq_rq_to_pdu(rq);
	struct loop_device *lo = rq->q->queuedata;

	blk_mq_start_request(rq);

	if (lo->lo_state != Lo_bound)
		return BLK_STS_IOERR;

	switch (req_op(rq)) {
	case REQ_OP_FLUSH:
	case REQ_OP_DISCARD:
	case REQ_OP_WRITE_ZEROES:
		cmd->use_aio = false;
		break;
	default:
		cmd->use_aio = lo->use_dio;
		break;
	}

	/* always use the first bio's css */
#ifdef CONFIG_BLK_CGROUP
	if (cmd->use_aio && rq->bio && rq->bio->bi_blkg) {
		cmd->css = &bio_blkcg(rq->bio)->css;
		css_get(cmd->css);
	} else
#endif
		cmd->css = NULL;
	kthread_queue_work(&lo->worker, &cmd->work);

	return BLK_STS_OK;
}