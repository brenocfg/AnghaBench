#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct safexcel_crypto_priv {int flags; TYPE_3__* ring; int /*<<< orphan*/  context_pool; } ;
struct safexcel_ahash_req {int needs_inv; scalar_t__ processed; scalar_t__ digest; int state_sz; scalar_t__ block_sz; scalar_t__ finish; int /*<<< orphan*/  state; } ;
struct TYPE_5__ {int needs_inv; int ring; TYPE_4__* ctxr; int /*<<< orphan*/  ctxr_dma; } ;
struct safexcel_ahash_ctx {TYPE_1__ base; int /*<<< orphan*/  opad; struct safexcel_crypto_priv* priv; } ;
struct ahash_request {int /*<<< orphan*/  base; } ;
struct TYPE_8__ {scalar_t__ data; } ;
struct TYPE_6__ {int /*<<< orphan*/  work; } ;
struct TYPE_7__ {TYPE_2__ work_data; int /*<<< orphan*/  workqueue; int /*<<< orphan*/  queue_lock; int /*<<< orphan*/  queue; } ;

/* Variables and functions */
 scalar_t__ CONTEXT_CONTROL_DIGEST_PRECOMPUTED ; 
 int /*<<< orphan*/  EIP197_GFP_FLAGS (int /*<<< orphan*/ ) ; 
 int EIP197_TRC_CACHE ; 
 int ENOMEM ; 
 struct safexcel_ahash_req* ahash_request_ctx (struct ahash_request*) ; 
 struct safexcel_ahash_ctx* crypto_ahash_ctx (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  crypto_ahash_reqtfm (struct ahash_request*) ; 
 int crypto_enqueue_request (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_4__* dma_pool_zalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ memcmp (scalar_t__,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int safexcel_select_ring (struct safexcel_crypto_priv*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int safexcel_ahash_enqueue(struct ahash_request *areq)
{
	struct safexcel_ahash_ctx *ctx = crypto_ahash_ctx(crypto_ahash_reqtfm(areq));
	struct safexcel_ahash_req *req = ahash_request_ctx(areq);
	struct safexcel_crypto_priv *priv = ctx->priv;
	int ret, ring;

	req->needs_inv = false;

	if (ctx->base.ctxr) {
		if (priv->flags & EIP197_TRC_CACHE && !ctx->base.needs_inv &&
		    req->processed &&
		    (/* invalidate for basic hash continuation finish */
		     (req->finish &&
		      (req->digest == CONTEXT_CONTROL_DIGEST_PRECOMPUTED)) ||
		     /* invalidate if (i)digest changed */
		     memcmp(ctx->base.ctxr->data, req->state, req->state_sz) ||
		     /* invalidate for HMAC continuation finish */
		     (req->finish && (req->processed != req->block_sz)) ||
		     /* invalidate for HMAC finish with odigest changed */
		     (req->finish &&
		      memcmp(ctx->base.ctxr->data + (req->state_sz>>2),
			     ctx->opad, req->state_sz))))
			/*
			 * We're still setting needs_inv here, even though it is
			 * cleared right away, because the needs_inv flag can be
			 * set in other functions and we want to keep the same
			 * logic.
			 */
			ctx->base.needs_inv = true;

		if (ctx->base.needs_inv) {
			ctx->base.needs_inv = false;
			req->needs_inv = true;
		}
	} else {
		ctx->base.ring = safexcel_select_ring(priv);
		ctx->base.ctxr = dma_pool_zalloc(priv->context_pool,
						 EIP197_GFP_FLAGS(areq->base),
						 &ctx->base.ctxr_dma);
		if (!ctx->base.ctxr)
			return -ENOMEM;
	}

	ring = ctx->base.ring;

	spin_lock_bh(&priv->ring[ring].queue_lock);
	ret = crypto_enqueue_request(&priv->ring[ring].queue, &areq->base);
	spin_unlock_bh(&priv->ring[ring].queue_lock);

	queue_work(priv->ring[ring].workqueue,
		   &priv->ring[ring].work_data.work);

	return ret;
}