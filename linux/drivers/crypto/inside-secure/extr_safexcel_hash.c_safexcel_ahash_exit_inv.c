#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct safexcel_inv_result {int error; int /*<<< orphan*/  completion; } ;
struct safexcel_crypto_priv {int /*<<< orphan*/  dev; TYPE_3__* ring; } ;
struct safexcel_ahash_req {int needs_inv; } ;
struct TYPE_11__ {int ring; int exit_inv; } ;
struct safexcel_ahash_ctx {TYPE_1__ base; struct safexcel_crypto_priv* priv; } ;
struct crypto_tfm {int dummy; } ;
struct TYPE_15__ {struct crypto_tfm* tfm; } ;
struct TYPE_14__ {TYPE_6__ base; } ;
struct TYPE_12__ {int /*<<< orphan*/  work; } ;
struct TYPE_13__ {TYPE_2__ work_data; int /*<<< orphan*/  workqueue; int /*<<< orphan*/  queue_lock; int /*<<< orphan*/  queue; } ;

/* Variables and functions */
 int /*<<< orphan*/  CRYPTO_TFM_REQ_MAY_BACKLOG ; 
 int /*<<< orphan*/  EIP197_AHASH_REQ_SIZE ; 
 int /*<<< orphan*/  EIP197_REQUEST_ON_STACK (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __crypto_ahash_cast (struct crypto_tfm*) ; 
 int /*<<< orphan*/  ahash ; 
 struct safexcel_ahash_req* ahash_request_ctx (TYPE_4__*) ; 
 int /*<<< orphan*/  ahash_request_set_callback (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct safexcel_inv_result*) ; 
 int /*<<< orphan*/  ahash_request_set_tfm (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  crypto_enqueue_request (int /*<<< orphan*/ *,TYPE_6__*) ; 
 struct safexcel_ahash_ctx* crypto_tfm_ctx (struct crypto_tfm*) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_4__* req ; 
 int /*<<< orphan*/  safexcel_inv_complete ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wait_for_completion (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int safexcel_ahash_exit_inv(struct crypto_tfm *tfm)
{
	struct safexcel_ahash_ctx *ctx = crypto_tfm_ctx(tfm);
	struct safexcel_crypto_priv *priv = ctx->priv;
	EIP197_REQUEST_ON_STACK(req, ahash, EIP197_AHASH_REQ_SIZE);
	struct safexcel_ahash_req *rctx = ahash_request_ctx(req);
	struct safexcel_inv_result result = {};
	int ring = ctx->base.ring;

	memset(req, 0, EIP197_AHASH_REQ_SIZE);

	/* create invalidation request */
	init_completion(&result.completion);
	ahash_request_set_callback(req, CRYPTO_TFM_REQ_MAY_BACKLOG,
				   safexcel_inv_complete, &result);

	ahash_request_set_tfm(req, __crypto_ahash_cast(tfm));
	ctx = crypto_tfm_ctx(req->base.tfm);
	ctx->base.exit_inv = true;
	rctx->needs_inv = true;

	spin_lock_bh(&priv->ring[ring].queue_lock);
	crypto_enqueue_request(&priv->ring[ring].queue, &req->base);
	spin_unlock_bh(&priv->ring[ring].queue_lock);

	queue_work(priv->ring[ring].workqueue,
		   &priv->ring[ring].work_data.work);

	wait_for_completion(&result.completion);

	if (result.error) {
		dev_warn(priv->dev, "hash: completion error (%d)\n",
			 result.error);
		return result.error;
	}

	return 0;
}