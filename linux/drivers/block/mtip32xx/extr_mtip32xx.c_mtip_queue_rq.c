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
struct request {int dummy; } ;
struct mtip_cmd {int dummy; } ;
struct driver_data {int dummy; } ;
struct blk_mq_queue_data {struct request* rq; } ;
struct blk_mq_hw_ctx {TYPE_1__* queue; } ;
typedef  int /*<<< orphan*/  blk_status_t ;
struct TYPE_2__ {struct driver_data* queuedata; } ;

/* Variables and functions */
 int /*<<< orphan*/  BLK_STS_DEV_RESOURCE ; 
 int /*<<< orphan*/  BLK_STS_IOERR ; 
 int /*<<< orphan*/  BLK_STS_OK ; 
 struct mtip_cmd* blk_mq_rq_to_pdu (struct request*) ; 
 int /*<<< orphan*/  blk_mq_start_request (struct request*) ; 
 scalar_t__ blk_rq_is_passthrough (struct request*) ; 
 scalar_t__ is_se_active (struct driver_data*) ; 
 scalar_t__ is_stopped (struct driver_data*,struct request*) ; 
 int /*<<< orphan*/  mtip_check_unal_depth (struct blk_mq_hw_ctx*,struct request*) ; 
 int /*<<< orphan*/  mtip_hw_submit_io (struct driver_data*,struct request*,struct mtip_cmd*,struct blk_mq_hw_ctx*) ; 
 int /*<<< orphan*/  mtip_issue_reserved_cmd (struct blk_mq_hw_ctx*,struct request*) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static blk_status_t mtip_queue_rq(struct blk_mq_hw_ctx *hctx,
			 const struct blk_mq_queue_data *bd)
{
	struct driver_data *dd = hctx->queue->queuedata;
	struct request *rq = bd->rq;
	struct mtip_cmd *cmd = blk_mq_rq_to_pdu(rq);

	if (blk_rq_is_passthrough(rq))
		return mtip_issue_reserved_cmd(hctx, rq);

	if (unlikely(mtip_check_unal_depth(hctx, rq)))
		return BLK_STS_DEV_RESOURCE;

	if (is_se_active(dd) || is_stopped(dd, rq))
		return BLK_STS_IOERR;

	blk_mq_start_request(rq);

	mtip_hw_submit_io(dd, rq, cmd, hctx);
	return BLK_STS_OK;
}