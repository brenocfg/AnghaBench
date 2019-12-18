#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct s5p_aes_reqctx {int /*<<< orphan*/  mode; } ;
struct s5p_aes_dev {int busy; TYPE_2__* req; int /*<<< orphan*/  ctx; int /*<<< orphan*/  lock; int /*<<< orphan*/  queue; } ;
struct crypto_async_request {int /*<<< orphan*/  (* complete ) (struct crypto_async_request*,int /*<<< orphan*/ ) ;} ;
struct TYPE_4__ {int /*<<< orphan*/  tfm; } ;
struct TYPE_5__ {TYPE_1__ base; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINPROGRESS ; 
 TYPE_2__* ablkcipher_request_cast (struct crypto_async_request*) ; 
 struct s5p_aes_reqctx* ablkcipher_request_ctx (TYPE_2__*) ; 
 struct crypto_async_request* crypto_dequeue_request (int /*<<< orphan*/ *) ; 
 struct crypto_async_request* crypto_get_backlog (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  crypto_tfm_ctx (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  s5p_aes_crypt_start (struct s5p_aes_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stub1 (struct crypto_async_request*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void s5p_tasklet_cb(unsigned long data)
{
	struct s5p_aes_dev *dev = (struct s5p_aes_dev *)data;
	struct crypto_async_request *async_req, *backlog;
	struct s5p_aes_reqctx *reqctx;
	unsigned long flags;

	spin_lock_irqsave(&dev->lock, flags);
	backlog   = crypto_get_backlog(&dev->queue);
	async_req = crypto_dequeue_request(&dev->queue);

	if (!async_req) {
		dev->busy = false;
		spin_unlock_irqrestore(&dev->lock, flags);
		return;
	}
	spin_unlock_irqrestore(&dev->lock, flags);

	if (backlog)
		backlog->complete(backlog, -EINPROGRESS);

	dev->req = ablkcipher_request_cast(async_req);
	dev->ctx = crypto_tfm_ctx(dev->req->base.tfm);
	reqctx   = ablkcipher_request_ctx(dev->req);

	s5p_aes_crypt_start(dev, reqctx->mode);
}