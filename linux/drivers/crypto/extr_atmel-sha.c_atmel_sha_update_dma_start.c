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
typedef  int /*<<< orphan*/  u32 ;
struct scatterlist {int /*<<< orphan*/  length; int /*<<< orphan*/  offset; } ;
struct atmel_sha_reqctx {unsigned int bufcnt; unsigned int offset; int block_size; int flags; struct scatterlist* sg; int /*<<< orphan*/  dma_addr; scalar_t__ buflen; int /*<<< orphan*/  buffer; scalar_t__ total; int /*<<< orphan*/ * digcnt; } ;
struct atmel_sha_dev {int /*<<< orphan*/  dev; int /*<<< orphan*/  req; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  IS_ALIGNED (int /*<<< orphan*/ ,int) ; 
 int SHA_FLAGS_FINUP ; 
 int SHA_FLAGS_SG ; 
 struct atmel_sha_reqctx* ahash_request_ctx (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atmel_sha_append_sg (struct atmel_sha_reqctx*) ; 
 int atmel_sha_complete (struct atmel_sha_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atmel_sha_fill_padding (struct atmel_sha_reqctx*,unsigned int) ; 
 int atmel_sha_update_dma_slow (struct atmel_sha_dev*) ; 
 int atmel_sha_xmit_start (struct atmel_sha_dev*,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,scalar_t__) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  dma_map_sg (int /*<<< orphan*/ ,struct scatterlist*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_map_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ dma_mapping_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned int min (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sg_dma_address (struct scatterlist*) ; 
 scalar_t__ sg_is_last (struct scatterlist*) ; 

__attribute__((used)) static int atmel_sha_update_dma_start(struct atmel_sha_dev *dd)
{
	struct atmel_sha_reqctx *ctx = ahash_request_ctx(dd->req);
	unsigned int length, final, tail;
	struct scatterlist *sg;
	unsigned int count;

	if (!ctx->total)
		return 0;

	if (ctx->bufcnt || ctx->offset)
		return atmel_sha_update_dma_slow(dd);

	dev_dbg(dd->dev, "fast: digcnt: 0x%llx 0x%llx, bufcnt: %zd, total: %u\n",
		ctx->digcnt[1], ctx->digcnt[0], ctx->bufcnt, ctx->total);

	sg = ctx->sg;

	if (!IS_ALIGNED(sg->offset, sizeof(u32)))
		return atmel_sha_update_dma_slow(dd);

	if (!sg_is_last(sg) && !IS_ALIGNED(sg->length, ctx->block_size))
		/* size is not ctx->block_size aligned */
		return atmel_sha_update_dma_slow(dd);

	length = min(ctx->total, sg->length);

	if (sg_is_last(sg)) {
		if (!(ctx->flags & SHA_FLAGS_FINUP)) {
			/* not last sg must be ctx->block_size aligned */
			tail = length & (ctx->block_size - 1);
			length -= tail;
		}
	}

	ctx->total -= length;
	ctx->offset = length; /* offset where to start slow */

	final = (ctx->flags & SHA_FLAGS_FINUP) && !ctx->total;

	/* Add padding */
	if (final) {
		tail = length & (ctx->block_size - 1);
		length -= tail;
		ctx->total += tail;
		ctx->offset = length; /* offset where to start slow */

		sg = ctx->sg;
		atmel_sha_append_sg(ctx);

		atmel_sha_fill_padding(ctx, length);

		ctx->dma_addr = dma_map_single(dd->dev, ctx->buffer,
			ctx->buflen + ctx->block_size, DMA_TO_DEVICE);
		if (dma_mapping_error(dd->dev, ctx->dma_addr)) {
			dev_err(dd->dev, "dma %zu bytes error\n",
				ctx->buflen + ctx->block_size);
			return atmel_sha_complete(dd, -EINVAL);
		}

		if (length == 0) {
			ctx->flags &= ~SHA_FLAGS_SG;
			count = ctx->bufcnt;
			ctx->bufcnt = 0;
			return atmel_sha_xmit_start(dd, ctx->dma_addr, count, 0,
					0, final);
		} else {
			ctx->sg = sg;
			if (!dma_map_sg(dd->dev, ctx->sg, 1,
				DMA_TO_DEVICE)) {
					dev_err(dd->dev, "dma_map_sg  error\n");
					return atmel_sha_complete(dd, -EINVAL);
			}

			ctx->flags |= SHA_FLAGS_SG;

			count = ctx->bufcnt;
			ctx->bufcnt = 0;
			return atmel_sha_xmit_start(dd, sg_dma_address(ctx->sg),
					length, ctx->dma_addr, count, final);
		}
	}

	if (!dma_map_sg(dd->dev, ctx->sg, 1, DMA_TO_DEVICE)) {
		dev_err(dd->dev, "dma_map_sg  error\n");
		return atmel_sha_complete(dd, -EINVAL);
	}

	ctx->flags |= SHA_FLAGS_SG;

	/* next call does not fail... so no unmap in the case of error */
	return atmel_sha_xmit_start(dd, sg_dma_address(ctx->sg), length, 0,
								0, final);
}