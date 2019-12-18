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
struct atmel_aes_reqctx {int dummy; } ;
struct atmel_aes_dev {scalar_t__ total; int /*<<< orphan*/  areq; int /*<<< orphan*/  ctx; } ;
struct atmel_aes_ctr_ctx {scalar_t__ offset; int /*<<< orphan*/  iv; } ;
struct ablkcipher_request {int /*<<< orphan*/  info; } ;

/* Variables and functions */
 int /*<<< orphan*/  AES_BLOCK_SIZE ; 
 struct ablkcipher_request* ablkcipher_request_cast (int /*<<< orphan*/ ) ; 
 struct atmel_aes_reqctx* ablkcipher_request_ctx (struct ablkcipher_request*) ; 
 int atmel_aes_complete (struct atmel_aes_dev*,int) ; 
 struct atmel_aes_ctr_ctx* atmel_aes_ctr_ctx_cast (int /*<<< orphan*/ ) ; 
 int atmel_aes_ctr_transfer (struct atmel_aes_dev*) ; 
 int atmel_aes_hw_init (struct atmel_aes_dev*) ; 
 int /*<<< orphan*/  atmel_aes_set_mode (struct atmel_aes_dev*,struct atmel_aes_reqctx*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int atmel_aes_ctr_start(struct atmel_aes_dev *dd)
{
	struct atmel_aes_ctr_ctx *ctx = atmel_aes_ctr_ctx_cast(dd->ctx);
	struct ablkcipher_request *req = ablkcipher_request_cast(dd->areq);
	struct atmel_aes_reqctx *rctx = ablkcipher_request_ctx(req);
	int err;

	atmel_aes_set_mode(dd, rctx);

	err = atmel_aes_hw_init(dd);
	if (err)
		return atmel_aes_complete(dd, err);

	memcpy(ctx->iv, req->info, AES_BLOCK_SIZE);
	ctx->offset = 0;
	dd->total = 0;
	return atmel_aes_ctr_transfer(dd);
}