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
struct crypto_async_request {int /*<<< orphan*/  tfm; int /*<<< orphan*/  (* complete ) (struct crypto_async_request*,int /*<<< orphan*/ ) ;} ;
struct atmel_aes_dev {int flags; int is_async; struct atmel_aes_base_ctx* ctx; struct crypto_async_request* areq; int /*<<< orphan*/  lock; int /*<<< orphan*/  queue; } ;
struct atmel_aes_base_ctx {int (* start ) (struct atmel_aes_dev*) ;} ;

/* Variables and functions */
 int AES_FLAGS_BUSY ; 
 int /*<<< orphan*/  EINPROGRESS ; 
 struct crypto_async_request* crypto_dequeue_request (int /*<<< orphan*/ *) ; 
 int crypto_enqueue_request (int /*<<< orphan*/ *,struct crypto_async_request*) ; 
 struct crypto_async_request* crypto_get_backlog (int /*<<< orphan*/ *) ; 
 struct atmel_aes_base_ctx* crypto_tfm_ctx (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stub1 (struct crypto_async_request*,int /*<<< orphan*/ ) ; 
 int stub2 (struct atmel_aes_dev*) ; 

__attribute__((used)) static int atmel_aes_handle_queue(struct atmel_aes_dev *dd,
				  struct crypto_async_request *new_areq)
{
	struct crypto_async_request *areq, *backlog;
	struct atmel_aes_base_ctx *ctx;
	unsigned long flags;
	bool start_async;
	int err, ret = 0;

	spin_lock_irqsave(&dd->lock, flags);
	if (new_areq)
		ret = crypto_enqueue_request(&dd->queue, new_areq);
	if (dd->flags & AES_FLAGS_BUSY) {
		spin_unlock_irqrestore(&dd->lock, flags);
		return ret;
	}
	backlog = crypto_get_backlog(&dd->queue);
	areq = crypto_dequeue_request(&dd->queue);
	if (areq)
		dd->flags |= AES_FLAGS_BUSY;
	spin_unlock_irqrestore(&dd->lock, flags);

	if (!areq)
		return ret;

	if (backlog)
		backlog->complete(backlog, -EINPROGRESS);

	ctx = crypto_tfm_ctx(areq->tfm);

	dd->areq = areq;
	dd->ctx = ctx;
	start_async = (areq != new_areq);
	dd->is_async = start_async;

	/* WARNING: ctx->start() MAY change dd->is_async. */
	err = ctx->start(dd);
	return (start_async) ? ret : err;
}