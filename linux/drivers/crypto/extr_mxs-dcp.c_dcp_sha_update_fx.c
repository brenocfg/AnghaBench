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
struct dcp_sha_req_ctx {int fini; int init; } ;
struct dcp_async_ctx {int hot; size_t chan; int /*<<< orphan*/  mutex; } ;
struct dcp {int /*<<< orphan*/ * thread; int /*<<< orphan*/ * lock; int /*<<< orphan*/ * queue; } ;
struct crypto_ahash {int dummy; } ;
struct ahash_request {int /*<<< orphan*/  base; int /*<<< orphan*/  nbytes; } ;

/* Variables and functions */
 struct dcp_sha_req_ctx* ahash_request_ctx (struct ahash_request*) ; 
 struct dcp_async_ctx* crypto_ahash_ctx (struct crypto_ahash*) ; 
 struct crypto_ahash* crypto_ahash_reqtfm (struct ahash_request*) ; 
 int crypto_enqueue_request (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct dcp* global_sdcp ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up_process (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dcp_sha_update_fx(struct ahash_request *req, int fini)
{
	struct dcp *sdcp = global_sdcp;

	struct dcp_sha_req_ctx *rctx = ahash_request_ctx(req);
	struct crypto_ahash *tfm = crypto_ahash_reqtfm(req);
	struct dcp_async_ctx *actx = crypto_ahash_ctx(tfm);

	int ret;

	/*
	 * Ignore requests that have no data in them and are not
	 * the trailing requests in the stream of requests.
	 */
	if (!req->nbytes && !fini)
		return 0;

	mutex_lock(&actx->mutex);

	rctx->fini = fini;

	if (!actx->hot) {
		actx->hot = 1;
		rctx->init = 1;
	}

	spin_lock(&sdcp->lock[actx->chan]);
	ret = crypto_enqueue_request(&sdcp->queue[actx->chan], &req->base);
	spin_unlock(&sdcp->lock[actx->chan]);

	wake_up_process(sdcp->thread[actx->chan]);
	mutex_unlock(&actx->mutex);

	return ret;
}