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
struct atmel_aes_reqctx {int dummy; } ;
struct atmel_aes_dev {TYPE_1__* ctx; int /*<<< orphan*/  areq; } ;
struct ablkcipher_request {scalar_t__ nbytes; int /*<<< orphan*/  dst; int /*<<< orphan*/  src; int /*<<< orphan*/  info; } ;
struct TYPE_2__ {scalar_t__ block_size; } ;

/* Variables and functions */
 scalar_t__ AES_BLOCK_SIZE ; 
 scalar_t__ ATMEL_AES_DMA_THRESHOLD ; 
 struct ablkcipher_request* ablkcipher_request_cast (int /*<<< orphan*/ ) ; 
 struct atmel_aes_reqctx* ablkcipher_request_ctx (struct ablkcipher_request*) ; 
 int atmel_aes_complete (struct atmel_aes_dev*,int) ; 
 int atmel_aes_cpu_start (struct atmel_aes_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int atmel_aes_dma_start (struct atmel_aes_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int atmel_aes_hw_init (struct atmel_aes_dev*) ; 
 int /*<<< orphan*/  atmel_aes_set_mode (struct atmel_aes_dev*,struct atmel_aes_reqctx*) ; 
 int /*<<< orphan*/  atmel_aes_transfer_complete ; 
 int /*<<< orphan*/  atmel_aes_write_ctrl (struct atmel_aes_dev*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int atmel_aes_start(struct atmel_aes_dev *dd)
{
	struct ablkcipher_request *req = ablkcipher_request_cast(dd->areq);
	struct atmel_aes_reqctx *rctx = ablkcipher_request_ctx(req);
	bool use_dma = (req->nbytes >= ATMEL_AES_DMA_THRESHOLD ||
			dd->ctx->block_size != AES_BLOCK_SIZE);
	int err;

	atmel_aes_set_mode(dd, rctx);

	err = atmel_aes_hw_init(dd);
	if (err)
		return atmel_aes_complete(dd, err);

	atmel_aes_write_ctrl(dd, use_dma, req->info);
	if (use_dma)
		return atmel_aes_dma_start(dd, req->src, req->dst, req->nbytes,
					   atmel_aes_transfer_complete);

	return atmel_aes_cpu_start(dd, req->src, req->dst, req->nbytes,
				   atmel_aes_transfer_complete);
}