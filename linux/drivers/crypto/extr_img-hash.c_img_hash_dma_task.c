#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct scatterlist {int dummy; } ;
struct img_hash_request_ctx {size_t offset; int bufcnt; TYPE_1__* sg; scalar_t__ sent; scalar_t__ buffer; int /*<<< orphan*/  nents; int /*<<< orphan*/  sgfirst; int /*<<< orphan*/  flags; } ;
struct img_hash_dev {scalar_t__ err; int /*<<< orphan*/  dev; int /*<<< orphan*/  req; } ;
struct TYPE_3__ {size_t length; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRIVER_FLAGS_CPU ; 
 struct img_hash_request_ctx* ahash_request_ctx (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  img_hash_dma_callback (struct img_hash_dev*) ; 
 int /*<<< orphan*/  img_hash_xmit_cpu (struct img_hash_dev*,int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ ) ; 
 scalar_t__ img_hash_xmit_dma (struct img_hash_dev*,struct scatterlist*) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  sg_init_one (struct scatterlist*,int /*<<< orphan*/ *,size_t) ; 
 void* sg_next (TYPE_1__*) ; 
 void* sg_pcopy_to_buffer (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,size_t,scalar_t__) ; 
 int /*<<< orphan*/ * sg_virt (TYPE_1__*) ; 

__attribute__((used)) static void img_hash_dma_task(unsigned long d)
{
	struct img_hash_dev *hdev = (struct img_hash_dev *)d;
	struct img_hash_request_ctx *ctx = ahash_request_ctx(hdev->req);
	u8 *addr;
	size_t nbytes, bleft, wsend, len, tbc;
	struct scatterlist tsg;

	if (!hdev->req || !ctx->sg)
		return;

	addr = sg_virt(ctx->sg);
	nbytes = ctx->sg->length - ctx->offset;

	/*
	 * The hash accelerator does not support a data valid mask. This means
	 * that if each dma (i.e. per page) is not a multiple of 4 bytes, the
	 * padding bytes in the last word written by that dma would erroneously
	 * be included in the hash. To avoid this we round down the transfer,
	 * and add the excess to the start of the next dma. It does not matter
	 * that the final dma may not be a multiple of 4 bytes as the hashing
	 * block is programmed to accept the correct number of bytes.
	 */

	bleft = nbytes % 4;
	wsend = (nbytes / 4);

	if (wsend) {
		sg_init_one(&tsg, addr + ctx->offset, wsend * 4);
		if (img_hash_xmit_dma(hdev, &tsg)) {
			dev_err(hdev->dev, "DMA failed, falling back to CPU");
			ctx->flags |= DRIVER_FLAGS_CPU;
			hdev->err = 0;
			img_hash_xmit_cpu(hdev, addr + ctx->offset,
					  wsend * 4, 0);
			ctx->sent += wsend * 4;
			wsend = 0;
		} else {
			ctx->sent += wsend * 4;
		}
	}

	if (bleft) {
		ctx->bufcnt = sg_pcopy_to_buffer(ctx->sgfirst, ctx->nents,
						 ctx->buffer, bleft, ctx->sent);
		tbc = 0;
		ctx->sg = sg_next(ctx->sg);
		while (ctx->sg && (ctx->bufcnt < 4)) {
			len = ctx->sg->length;
			if (likely(len > (4 - ctx->bufcnt)))
				len = 4 - ctx->bufcnt;
			tbc = sg_pcopy_to_buffer(ctx->sgfirst, ctx->nents,
						 ctx->buffer + ctx->bufcnt, len,
					ctx->sent + ctx->bufcnt);
			ctx->bufcnt += tbc;
			if (tbc >= ctx->sg->length) {
				ctx->sg = sg_next(ctx->sg);
				tbc = 0;
			}
		}

		ctx->sent += ctx->bufcnt;
		ctx->offset = tbc;

		if (!wsend)
			img_hash_dma_callback(hdev);
	} else {
		ctx->offset = 0;
		ctx->sg = sg_next(ctx->sg);
	}
}