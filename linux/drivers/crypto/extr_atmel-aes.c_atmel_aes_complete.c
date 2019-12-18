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
struct crypto_ablkcipher {int dummy; } ;
struct atmel_aes_reqctx {int mode; int /*<<< orphan*/  lastc; } ;
struct atmel_aes_dev {int /*<<< orphan*/  queue_task; TYPE_2__* areq; scalar_t__ is_async; TYPE_1__* ctx; int /*<<< orphan*/  flags; int /*<<< orphan*/  iclk; } ;
struct ablkcipher_request {scalar_t__ dst; scalar_t__ src; scalar_t__ nbytes; int /*<<< orphan*/  info; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* complete ) (TYPE_2__*,int) ;} ;
struct TYPE_4__ {scalar_t__ is_aead; } ;

/* Variables and functions */
 int /*<<< orphan*/  AES_FLAGS_BUSY ; 
 int AES_FLAGS_ENCRYPT ; 
 struct ablkcipher_request* ablkcipher_request_cast (TYPE_2__*) ; 
 struct atmel_aes_reqctx* ablkcipher_request_ctx (struct ablkcipher_request*) ; 
 int /*<<< orphan*/  atmel_aes_authenc_complete (struct atmel_aes_dev*,int) ; 
 int /*<<< orphan*/  clk_disable (int /*<<< orphan*/ ) ; 
 int crypto_ablkcipher_ivsize (struct crypto_ablkcipher*) ; 
 struct crypto_ablkcipher* crypto_ablkcipher_reqtfm (struct ablkcipher_request*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  scatterwalk_map_and_copy (int /*<<< orphan*/ ,scalar_t__,scalar_t__,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*,int) ; 
 int /*<<< orphan*/  tasklet_schedule (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline int atmel_aes_complete(struct atmel_aes_dev *dd, int err)
{
#ifdef CONFIG_CRYPTO_DEV_ATMEL_AUTHENC
	if (dd->ctx->is_aead)
		atmel_aes_authenc_complete(dd, err);
#endif

	clk_disable(dd->iclk);
	dd->flags &= ~AES_FLAGS_BUSY;

	if (!dd->ctx->is_aead) {
		struct ablkcipher_request *req =
			ablkcipher_request_cast(dd->areq);
		struct atmel_aes_reqctx *rctx = ablkcipher_request_ctx(req);
		struct crypto_ablkcipher *ablkcipher =
			crypto_ablkcipher_reqtfm(req);
		int ivsize = crypto_ablkcipher_ivsize(ablkcipher);

		if (rctx->mode & AES_FLAGS_ENCRYPT) {
			scatterwalk_map_and_copy(req->info, req->dst,
				req->nbytes - ivsize, ivsize, 0);
		} else {
			if (req->src == req->dst) {
				memcpy(req->info, rctx->lastc, ivsize);
			} else {
				scatterwalk_map_and_copy(req->info, req->src,
					req->nbytes - ivsize, ivsize, 0);
			}
		}
	}

	if (dd->is_async)
		dd->areq->complete(dd->areq, err);

	tasklet_schedule(&dd->queue_task);

	return err;
}