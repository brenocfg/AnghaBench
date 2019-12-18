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
struct sahara_dev {int flags; int /*<<< orphan*/  nb_in_sg; int /*<<< orphan*/  in_sg; int /*<<< orphan*/  device; int /*<<< orphan*/  nb_out_sg; int /*<<< orphan*/  out_sg; int /*<<< orphan*/  dma_completion; struct sahara_ctx* ctx; int /*<<< orphan*/  iv_base; int /*<<< orphan*/  total; } ;
struct sahara_ctx {int dummy; } ;
struct sahara_aes_reqctx {int mode; } ;
struct ablkcipher_request {int /*<<< orphan*/  info; int /*<<< orphan*/  dst; int /*<<< orphan*/  src; int /*<<< orphan*/  nbytes; } ;

/* Variables and functions */
 int /*<<< orphan*/  AES_KEYSIZE_128 ; 
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int EINVAL ; 
 int ETIMEDOUT ; 
 int FLAGS_CBC ; 
 int FLAGS_MODE_MASK ; 
 int /*<<< orphan*/  SAHARA_TIMEOUT_MS ; 
 struct sahara_aes_reqctx* ablkcipher_request_ctx (struct ablkcipher_request*) ; 
 struct sahara_ctx* crypto_ablkcipher_ctx (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  crypto_ablkcipher_reqtfm (struct ablkcipher_request*) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 struct sahara_dev* dev_ptr ; 
 int /*<<< orphan*/  dma_unmap_sg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reinit_completion (int /*<<< orphan*/ *) ; 
 int sahara_hw_descriptor_create (struct sahara_dev*) ; 
 unsigned long wait_for_completion_timeout (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sahara_aes_process(struct ablkcipher_request *req)
{
	struct sahara_dev *dev = dev_ptr;
	struct sahara_ctx *ctx;
	struct sahara_aes_reqctx *rctx;
	int ret;
	unsigned long timeout;

	/* Request is ready to be dispatched by the device */
	dev_dbg(dev->device,
		"dispatch request (nbytes=%d, src=%p, dst=%p)\n",
		req->nbytes, req->src, req->dst);

	/* assign new request to device */
	dev->total = req->nbytes;
	dev->in_sg = req->src;
	dev->out_sg = req->dst;

	rctx = ablkcipher_request_ctx(req);
	ctx = crypto_ablkcipher_ctx(crypto_ablkcipher_reqtfm(req));
	rctx->mode &= FLAGS_MODE_MASK;
	dev->flags = (dev->flags & ~FLAGS_MODE_MASK) | rctx->mode;

	if ((dev->flags & FLAGS_CBC) && req->info)
		memcpy(dev->iv_base, req->info, AES_KEYSIZE_128);

	/* assign new context to device */
	dev->ctx = ctx;

	reinit_completion(&dev->dma_completion);

	ret = sahara_hw_descriptor_create(dev);
	if (ret)
		return -EINVAL;

	timeout = wait_for_completion_timeout(&dev->dma_completion,
				msecs_to_jiffies(SAHARA_TIMEOUT_MS));
	if (!timeout) {
		dev_err(dev->device, "AES timeout\n");
		return -ETIMEDOUT;
	}

	dma_unmap_sg(dev->device, dev->out_sg, dev->nb_out_sg,
		DMA_FROM_DEVICE);
	dma_unmap_sg(dev->device, dev->in_sg, dev->nb_in_sg,
		DMA_TO_DEVICE);

	return 0;
}