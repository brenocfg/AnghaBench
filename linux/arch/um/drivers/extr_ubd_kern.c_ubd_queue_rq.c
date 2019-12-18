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
typedef  int u64 ;
struct ubd {int /*<<< orphan*/  lock; } ;
struct request {int dummy; } ;
struct blk_mq_queue_data {struct request* rq; } ;
struct blk_mq_hw_ctx {TYPE_1__* queue; } ;
typedef  int blk_status_t ;
struct TYPE_2__ {struct ubd* queuedata; } ;

/* Variables and functions */
 int BLK_STS_DEV_RESOURCE ; 
 int BLK_STS_NOTSUPP ; 
 int BLK_STS_OK ; 
 int BLK_STS_RESOURCE ; 
 int ENOMEM ; 
#define  REQ_OP_DISCARD 132 
#define  REQ_OP_FLUSH 131 
#define  REQ_OP_READ 130 
#define  REQ_OP_WRITE 129 
#define  REQ_OP_WRITE_ZEROES 128 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  blk_mq_start_request (struct request*) ; 
 int /*<<< orphan*/  blk_rq_pos (struct request*) ; 
 int queue_rw_req (struct blk_mq_hw_ctx*,struct request*) ; 
 int req_op (struct request*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int ubd_queue_one_vec (struct blk_mq_hw_ctx*,struct request*,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static blk_status_t ubd_queue_rq(struct blk_mq_hw_ctx *hctx,
				 const struct blk_mq_queue_data *bd)
{
	struct ubd *ubd_dev = hctx->queue->queuedata;
	struct request *req = bd->rq;
	int ret = 0, res = BLK_STS_OK;

	blk_mq_start_request(req);

	spin_lock_irq(&ubd_dev->lock);

	switch (req_op(req)) {
	/* operations with no lentgth/offset arguments */
	case REQ_OP_FLUSH:
		ret = ubd_queue_one_vec(hctx, req, 0, NULL);
		break;
	case REQ_OP_READ:
	case REQ_OP_WRITE:
		ret = queue_rw_req(hctx, req);
		break;
	case REQ_OP_DISCARD:
	case REQ_OP_WRITE_ZEROES:
		ret = ubd_queue_one_vec(hctx, req, (u64)blk_rq_pos(req) << 9, NULL);
		break;
	default:
		WARN_ON_ONCE(1);
		res = BLK_STS_NOTSUPP;
	}

	spin_unlock_irq(&ubd_dev->lock);

	if (ret < 0) {
		if (ret == -ENOMEM)
			res = BLK_STS_RESOURCE;
		else
			res = BLK_STS_DEV_RESOURCE;
	}

	return res;
}