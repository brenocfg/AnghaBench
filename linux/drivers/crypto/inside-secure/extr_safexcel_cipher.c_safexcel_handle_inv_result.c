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
struct safexcel_result_desc {int dummy; } ;
struct safexcel_crypto_priv {TYPE_3__* ring; int /*<<< orphan*/  context_pool; int /*<<< orphan*/  dev; } ;
struct safexcel_cipher_req {int /*<<< orphan*/  rdescs; } ;
struct TYPE_4__ {int ring; int /*<<< orphan*/  ctxr_dma; int /*<<< orphan*/  ctxr; scalar_t__ exit_inv; } ;
struct safexcel_cipher_ctx {TYPE_1__ base; } ;
struct crypto_async_request {int /*<<< orphan*/  tfm; } ;
struct TYPE_5__ {int /*<<< orphan*/  work; } ;
struct TYPE_6__ {TYPE_2__ work_data; int /*<<< orphan*/  workqueue; int /*<<< orphan*/  queue_lock; int /*<<< orphan*/  queue; int /*<<< orphan*/  rdr; } ;

/* Variables and functions */
 int EINPROGRESS ; 
 scalar_t__ IS_ERR (struct safexcel_result_desc*) ; 
 int PTR_ERR (struct safexcel_result_desc*) ; 
 int crypto_enqueue_request (int /*<<< orphan*/ *,struct crypto_async_request*) ; 
 struct safexcel_cipher_ctx* crypto_tfm_ctx (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dma_pool_free (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  safexcel_complete (struct safexcel_crypto_priv*,int) ; 
 int safexcel_rdesc_check_errors (struct safexcel_crypto_priv*,struct safexcel_result_desc*) ; 
 struct safexcel_result_desc* safexcel_ring_next_rptr (struct safexcel_crypto_priv*,int /*<<< orphan*/ *) ; 
 int safexcel_select_ring (struct safexcel_crypto_priv*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int safexcel_handle_inv_result(struct safexcel_crypto_priv *priv,
				      int ring,
				      struct crypto_async_request *base,
				      struct safexcel_cipher_req *sreq,
				      bool *should_complete, int *ret)
{
	struct safexcel_cipher_ctx *ctx = crypto_tfm_ctx(base->tfm);
	struct safexcel_result_desc *rdesc;
	int ndesc = 0, enq_ret;

	*ret = 0;

	if (unlikely(!sreq->rdescs))
		return 0;

	while (sreq->rdescs--) {
		rdesc = safexcel_ring_next_rptr(priv, &priv->ring[ring].rdr);
		if (IS_ERR(rdesc)) {
			dev_err(priv->dev,
				"cipher: invalidate: could not retrieve the result descriptor\n");
			*ret = PTR_ERR(rdesc);
			break;
		}

		if (likely(!*ret))
			*ret = safexcel_rdesc_check_errors(priv, rdesc);

		ndesc++;
	}

	safexcel_complete(priv, ring);

	if (ctx->base.exit_inv) {
		dma_pool_free(priv->context_pool, ctx->base.ctxr,
			      ctx->base.ctxr_dma);

		*should_complete = true;

		return ndesc;
	}

	ring = safexcel_select_ring(priv);
	ctx->base.ring = ring;

	spin_lock_bh(&priv->ring[ring].queue_lock);
	enq_ret = crypto_enqueue_request(&priv->ring[ring].queue, base);
	spin_unlock_bh(&priv->ring[ring].queue_lock);

	if (enq_ret != -EINPROGRESS)
		*ret = enq_ret;

	queue_work(priv->ring[ring].workqueue,
		   &priv->ring[ring].work_data.work);

	*should_complete = false;

	return ndesc;
}