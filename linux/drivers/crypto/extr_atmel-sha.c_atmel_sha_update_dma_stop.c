#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct atmel_sha_reqctx {int flags; scalar_t__ offset; scalar_t__ block_size; scalar_t__ buflen; int /*<<< orphan*/  dma_addr; TYPE_1__* sg; } ;
struct atmel_sha_dev {int /*<<< orphan*/  dev; int /*<<< orphan*/  req; } ;
struct TYPE_4__ {scalar_t__ length; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int SHA_FLAGS_PAD ; 
 int SHA_FLAGS_SG ; 
 struct atmel_sha_reqctx* ahash_request_ctx (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_sg (int /*<<< orphan*/ ,TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 TYPE_1__* sg_next (TYPE_1__*) ; 

__attribute__((used)) static int atmel_sha_update_dma_stop(struct atmel_sha_dev *dd)
{
	struct atmel_sha_reqctx *ctx = ahash_request_ctx(dd->req);

	if (ctx->flags & SHA_FLAGS_SG) {
		dma_unmap_sg(dd->dev, ctx->sg, 1, DMA_TO_DEVICE);
		if (ctx->sg->length == ctx->offset) {
			ctx->sg = sg_next(ctx->sg);
			if (ctx->sg)
				ctx->offset = 0;
		}
		if (ctx->flags & SHA_FLAGS_PAD) {
			dma_unmap_single(dd->dev, ctx->dma_addr,
				ctx->buflen + ctx->block_size, DMA_TO_DEVICE);
		}
	} else {
		dma_unmap_single(dd->dev, ctx->dma_addr, ctx->buflen +
						ctx->block_size, DMA_TO_DEVICE);
	}

	return 0;
}