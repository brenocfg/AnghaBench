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
struct mv_cesa_req {struct mv_cesa_engine* engine; } ;
struct mv_cesa_engine {int /*<<< orphan*/  lock; int /*<<< orphan*/  queue; } ;
struct crypto_async_request {int dummy; } ;

/* Variables and functions */
 scalar_t__ CESA_DMA_REQ ; 
 int EBUSY ; 
 int EINPROGRESS ; 
 int crypto_enqueue_request (int /*<<< orphan*/ *,struct crypto_async_request*) ; 
 int /*<<< orphan*/  mv_cesa_rearm_engine (struct mv_cesa_engine*) ; 
 scalar_t__ mv_cesa_req_get_type (struct mv_cesa_req*) ; 
 int /*<<< orphan*/  mv_cesa_tdma_chain (struct mv_cesa_engine*,struct mv_cesa_req*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

int mv_cesa_queue_req(struct crypto_async_request *req,
		      struct mv_cesa_req *creq)
{
	int ret;
	struct mv_cesa_engine *engine = creq->engine;

	spin_lock_bh(&engine->lock);
	ret = crypto_enqueue_request(&engine->queue, req);
	if ((mv_cesa_req_get_type(creq) == CESA_DMA_REQ) &&
	    (ret == -EINPROGRESS || ret == -EBUSY))
		mv_cesa_tdma_chain(engine, creq);
	spin_unlock_bh(&engine->lock);

	if (ret != -EINPROGRESS)
		return ret;

	mv_cesa_rearm_engine(engine);

	return -EINPROGRESS;
}