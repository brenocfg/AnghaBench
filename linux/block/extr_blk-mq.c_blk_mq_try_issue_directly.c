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
struct request {int dummy; } ;
struct blk_mq_hw_ctx {int flags; } ;
typedef  scalar_t__ blk_status_t ;
typedef  int /*<<< orphan*/  blk_qc_t ;

/* Variables and functions */
 int BLK_MQ_F_BLOCKING ; 
 scalar_t__ BLK_STS_DEV_RESOURCE ; 
 scalar_t__ BLK_STS_OK ; 
 scalar_t__ BLK_STS_RESOURCE ; 
 scalar_t__ __blk_mq_try_issue_directly (struct blk_mq_hw_ctx*,struct request*,int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  blk_mq_end_request (struct request*,scalar_t__) ; 
 int /*<<< orphan*/  blk_mq_request_bypass_insert (struct request*,int) ; 
 int /*<<< orphan*/  hctx_lock (struct blk_mq_hw_ctx*,int*) ; 
 int /*<<< orphan*/  hctx_unlock (struct blk_mq_hw_ctx*,int) ; 
 int /*<<< orphan*/  might_sleep_if (int) ; 

__attribute__((used)) static void blk_mq_try_issue_directly(struct blk_mq_hw_ctx *hctx,
		struct request *rq, blk_qc_t *cookie)
{
	blk_status_t ret;
	int srcu_idx;

	might_sleep_if(hctx->flags & BLK_MQ_F_BLOCKING);

	hctx_lock(hctx, &srcu_idx);

	ret = __blk_mq_try_issue_directly(hctx, rq, cookie, false, true);
	if (ret == BLK_STS_RESOURCE || ret == BLK_STS_DEV_RESOURCE)
		blk_mq_request_bypass_insert(rq, true);
	else if (ret != BLK_STS_OK)
		blk_mq_end_request(rq, ret);

	hctx_unlock(hctx, srcu_idx);
}