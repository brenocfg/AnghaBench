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
struct atmel_sha_reqctx {int /*<<< orphan*/  dma_addr; int /*<<< orphan*/  flags; scalar_t__ block_size; scalar_t__ buflen; int /*<<< orphan*/  buffer; } ;
struct atmel_sha_dev {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  SHA_FLAGS_SG ; 
 int atmel_sha_complete (struct atmel_sha_dev*,int /*<<< orphan*/ ) ; 
 int atmel_sha_xmit_start (struct atmel_sha_dev*,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int /*<<< orphan*/  dma_map_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ dma_mapping_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int atmel_sha_xmit_dma_map(struct atmel_sha_dev *dd,
					struct atmel_sha_reqctx *ctx,
					size_t length, int final)
{
	ctx->dma_addr = dma_map_single(dd->dev, ctx->buffer,
				ctx->buflen + ctx->block_size, DMA_TO_DEVICE);
	if (dma_mapping_error(dd->dev, ctx->dma_addr)) {
		dev_err(dd->dev, "dma %zu bytes error\n", ctx->buflen +
				ctx->block_size);
		return atmel_sha_complete(dd, -EINVAL);
	}

	ctx->flags &= ~SHA_FLAGS_SG;

	/* next call does not fail... so no unmap in the case of error */
	return atmel_sha_xmit_start(dd, ctx->dma_addr, length, 0, 0, final);
}