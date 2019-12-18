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
struct blkfront_ring_info {int /*<<< orphan*/  ring_lock; int /*<<< orphan*/  dev_info; int /*<<< orphan*/  ring; } ;
struct blkfront_info {int nr_rings; struct blkfront_ring_info* rinfo; } ;
struct blk_mq_queue_data {int /*<<< orphan*/  rq; } ;
struct blk_mq_hw_ctx {int queue_num; TYPE_1__* queue; } ;
typedef  int /*<<< orphan*/  blk_status_t ;
struct TYPE_2__ {struct blkfront_info* queuedata; } ;

/* Variables and functions */
 int /*<<< orphan*/  BLK_STS_DEV_RESOURCE ; 
 int /*<<< orphan*/  BLK_STS_IOERR ; 
 int /*<<< orphan*/  BLK_STS_OK ; 
 int /*<<< orphan*/  BUG_ON (int) ; 
 scalar_t__ RING_FULL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  blk_mq_start_request (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blk_mq_stop_hw_queue (struct blk_mq_hw_ctx*) ; 
 scalar_t__ blkif_queue_request (int /*<<< orphan*/ ,struct blkfront_ring_info*) ; 
 scalar_t__ blkif_request_flush_invalid (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  flush_requests (struct blkfront_ring_info*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static blk_status_t blkif_queue_rq(struct blk_mq_hw_ctx *hctx,
			  const struct blk_mq_queue_data *qd)
{
	unsigned long flags;
	int qid = hctx->queue_num;
	struct blkfront_info *info = hctx->queue->queuedata;
	struct blkfront_ring_info *rinfo = NULL;

	BUG_ON(info->nr_rings <= qid);
	rinfo = &info->rinfo[qid];
	blk_mq_start_request(qd->rq);
	spin_lock_irqsave(&rinfo->ring_lock, flags);
	if (RING_FULL(&rinfo->ring))
		goto out_busy;

	if (blkif_request_flush_invalid(qd->rq, rinfo->dev_info))
		goto out_err;

	if (blkif_queue_request(qd->rq, rinfo))
		goto out_busy;

	flush_requests(rinfo);
	spin_unlock_irqrestore(&rinfo->ring_lock, flags);
	return BLK_STS_OK;

out_err:
	spin_unlock_irqrestore(&rinfo->ring_lock, flags);
	return BLK_STS_IOERR;

out_busy:
	blk_mq_stop_hw_queue(hctx);
	spin_unlock_irqrestore(&rinfo->ring_lock, flags);
	return BLK_STS_DEV_RESOURCE;
}