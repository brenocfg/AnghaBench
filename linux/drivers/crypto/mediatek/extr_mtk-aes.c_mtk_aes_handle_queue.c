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
typedef  size_t u8 ;
struct mtk_cryp {struct mtk_aes_rec** aes; } ;
struct mtk_aes_rec {int flags; struct mtk_aes_base_ctx* ctx; struct crypto_async_request* areq; int /*<<< orphan*/  lock; int /*<<< orphan*/  queue; } ;
struct TYPE_2__ {int /*<<< orphan*/  state; } ;
struct mtk_aes_base_ctx {int (* start ) (struct mtk_cryp*,struct mtk_aes_rec*) ;int /*<<< orphan*/  key; TYPE_1__ info; } ;
struct crypto_async_request {int /*<<< orphan*/  tfm; int /*<<< orphan*/  (* complete ) (struct crypto_async_request*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int AES_FLAGS_BUSY ; 
 int /*<<< orphan*/  EINPROGRESS ; 
 struct crypto_async_request* crypto_dequeue_request (int /*<<< orphan*/ *) ; 
 int crypto_enqueue_request (int /*<<< orphan*/ *,struct crypto_async_request*) ; 
 struct crypto_async_request* crypto_get_backlog (int /*<<< orphan*/ *) ; 
 struct mtk_aes_base_ctx* crypto_tfm_ctx (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stub1 (struct crypto_async_request*,int /*<<< orphan*/ ) ; 
 int stub2 (struct mtk_cryp*,struct mtk_aes_rec*) ; 

__attribute__((used)) static int mtk_aes_handle_queue(struct mtk_cryp *cryp, u8 id,
				struct crypto_async_request *new_areq)
{
	struct mtk_aes_rec *aes = cryp->aes[id];
	struct crypto_async_request *areq, *backlog;
	struct mtk_aes_base_ctx *ctx;
	unsigned long flags;
	int ret = 0;

	spin_lock_irqsave(&aes->lock, flags);
	if (new_areq)
		ret = crypto_enqueue_request(&aes->queue, new_areq);
	if (aes->flags & AES_FLAGS_BUSY) {
		spin_unlock_irqrestore(&aes->lock, flags);
		return ret;
	}
	backlog = crypto_get_backlog(&aes->queue);
	areq = crypto_dequeue_request(&aes->queue);
	if (areq)
		aes->flags |= AES_FLAGS_BUSY;
	spin_unlock_irqrestore(&aes->lock, flags);

	if (!areq)
		return ret;

	if (backlog)
		backlog->complete(backlog, -EINPROGRESS);

	ctx = crypto_tfm_ctx(areq->tfm);
	/* Write key into state buffer */
	memcpy(ctx->info.state, ctx->key, sizeof(ctx->key));

	aes->areq = areq;
	aes->ctx = ctx;

	return ctx->start(cryp, aes);
}