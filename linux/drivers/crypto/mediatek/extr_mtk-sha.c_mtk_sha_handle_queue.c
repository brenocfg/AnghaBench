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
typedef  size_t u8 ;
struct mtk_sha_reqctx {scalar_t__ op; int flags; } ;
struct mtk_sha_rec {int flags; struct ahash_request* req; int /*<<< orphan*/  lock; int /*<<< orphan*/  queue; } ;
struct mtk_cryp {struct mtk_sha_rec** sha; } ;
struct crypto_async_request {int /*<<< orphan*/  (* complete ) (struct crypto_async_request*,int) ;} ;
struct ahash_request {int dummy; } ;

/* Variables and functions */
 int EINPROGRESS ; 
 int SHA_FLAGS_BUSY ; 
 int SHA_FLAGS_FINUP ; 
 scalar_t__ SHA_OP_FINAL ; 
 scalar_t__ SHA_OP_UPDATE ; 
 int ahash_enqueue_request (int /*<<< orphan*/ *,struct ahash_request*) ; 
 struct ahash_request* ahash_request_cast (struct crypto_async_request*) ; 
 struct mtk_sha_reqctx* ahash_request_ctx (struct ahash_request*) ; 
 struct crypto_async_request* crypto_dequeue_request (int /*<<< orphan*/ *) ; 
 struct crypto_async_request* crypto_get_backlog (int /*<<< orphan*/ *) ; 
 int mtk_sha_final_req (struct mtk_cryp*,struct mtk_sha_rec*) ; 
 int /*<<< orphan*/  mtk_sha_finish_req (struct mtk_cryp*,struct mtk_sha_rec*,int) ; 
 int /*<<< orphan*/  mtk_sha_info_init (struct mtk_sha_reqctx*) ; 
 int mtk_sha_update_start (struct mtk_cryp*,struct mtk_sha_rec*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stub1 (struct crypto_async_request*,int) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int mtk_sha_handle_queue(struct mtk_cryp *cryp, u8 id,
				struct ahash_request *req)
{
	struct mtk_sha_rec *sha = cryp->sha[id];
	struct crypto_async_request *async_req, *backlog;
	struct mtk_sha_reqctx *ctx;
	unsigned long flags;
	int err = 0, ret = 0;

	spin_lock_irqsave(&sha->lock, flags);
	if (req)
		ret = ahash_enqueue_request(&sha->queue, req);

	if (SHA_FLAGS_BUSY & sha->flags) {
		spin_unlock_irqrestore(&sha->lock, flags);
		return ret;
	}

	backlog = crypto_get_backlog(&sha->queue);
	async_req = crypto_dequeue_request(&sha->queue);
	if (async_req)
		sha->flags |= SHA_FLAGS_BUSY;
	spin_unlock_irqrestore(&sha->lock, flags);

	if (!async_req)
		return ret;

	if (backlog)
		backlog->complete(backlog, -EINPROGRESS);

	req = ahash_request_cast(async_req);
	ctx = ahash_request_ctx(req);

	sha->req = req;

	mtk_sha_info_init(ctx);

	if (ctx->op == SHA_OP_UPDATE) {
		err = mtk_sha_update_start(cryp, sha);
		if (err != -EINPROGRESS && (ctx->flags & SHA_FLAGS_FINUP))
			/* No final() after finup() */
			err = mtk_sha_final_req(cryp, sha);
	} else if (ctx->op == SHA_OP_FINAL) {
		err = mtk_sha_final_req(cryp, sha);
	}

	if (unlikely(err != -EINPROGRESS))
		/* Task will not finish it, so do it here */
		mtk_sha_finish_req(cryp, sha, err);

	return ret;
}