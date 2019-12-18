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
struct s5p_hash_reqctx {int finup; int /*<<< orphan*/  total; int /*<<< orphan*/  error; scalar_t__ op_update; scalar_t__ digcnt; } ;
struct s5p_aes_dev {int /*<<< orphan*/  dev; struct ahash_request* hash_req; int /*<<< orphan*/  hash_lock; int /*<<< orphan*/  hash_flags; int /*<<< orphan*/  hash_queue; } ;
struct crypto_async_request {int /*<<< orphan*/  (* complete ) (struct crypto_async_request*,int) ;} ;
struct ahash_request {int /*<<< orphan*/  nbytes; } ;

/* Variables and functions */
 int EINPROGRESS ; 
 int /*<<< orphan*/  HASH_FLAGS_BUSY ; 
 int /*<<< orphan*/  SSS_HASHIN_INDEPENDENT ; 
 int ahash_enqueue_request (int /*<<< orphan*/ *,struct ahash_request*) ; 
 struct ahash_request* ahash_request_cast (struct crypto_async_request*) ; 
 struct s5p_hash_reqctx* ahash_request_ctx (struct ahash_request*) ; 
 struct crypto_async_request* crypto_dequeue_request (int /*<<< orphan*/ *) ; 
 struct crypto_async_request* crypto_get_backlog (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  s5p_ahash_dma_init (struct s5p_aes_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  s5p_hash_finish_req (struct ahash_request*,int) ; 
 int s5p_hash_prepare_request (struct ahash_request*,scalar_t__) ; 
 int /*<<< orphan*/  s5p_hash_write_iv (struct ahash_request*) ; 
 int s5p_hash_xmit_dma (struct s5p_aes_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stub1 (struct crypto_async_request*,int) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int s5p_hash_handle_queue(struct s5p_aes_dev *dd,
				 struct ahash_request *req)
{
	struct crypto_async_request *async_req, *backlog;
	struct s5p_hash_reqctx *ctx;
	unsigned long flags;
	int err = 0, ret = 0;

retry:
	spin_lock_irqsave(&dd->hash_lock, flags);
	if (req)
		ret = ahash_enqueue_request(&dd->hash_queue, req);

	if (test_bit(HASH_FLAGS_BUSY, &dd->hash_flags)) {
		spin_unlock_irqrestore(&dd->hash_lock, flags);
		return ret;
	}

	backlog = crypto_get_backlog(&dd->hash_queue);
	async_req = crypto_dequeue_request(&dd->hash_queue);
	if (async_req)
		set_bit(HASH_FLAGS_BUSY, &dd->hash_flags);

	spin_unlock_irqrestore(&dd->hash_lock, flags);

	if (!async_req)
		return ret;

	if (backlog)
		backlog->complete(backlog, -EINPROGRESS);

	req = ahash_request_cast(async_req);
	dd->hash_req = req;
	ctx = ahash_request_ctx(req);

	err = s5p_hash_prepare_request(req, ctx->op_update);
	if (err || !ctx->total)
		goto out;

	dev_dbg(dd->dev, "handling new req, op_update: %u, nbytes: %d\n",
		ctx->op_update, req->nbytes);

	s5p_ahash_dma_init(dd, SSS_HASHIN_INDEPENDENT);
	if (ctx->digcnt)
		s5p_hash_write_iv(req); /* restore hash IV */

	if (ctx->op_update) { /* HASH_OP_UPDATE */
		err = s5p_hash_xmit_dma(dd, ctx->total, ctx->finup);
		if (err != -EINPROGRESS && ctx->finup && !ctx->error)
			/* no final() after finup() */
			err = s5p_hash_xmit_dma(dd, ctx->total, true);
	} else { /* HASH_OP_FINAL */
		err = s5p_hash_xmit_dma(dd, ctx->total, true);
	}
out:
	if (err != -EINPROGRESS) {
		/* hash_tasklet_cb will not finish it, so do it here */
		s5p_hash_finish_req(req, err);
		req = NULL;

		/*
		 * Execute next request immediately if there is anything
		 * in queue.
		 */
		goto retry;
	}

	return ret;
}