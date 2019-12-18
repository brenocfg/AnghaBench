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
typedef  int u32 ;
struct scatterlist {int /*<<< orphan*/  length; int /*<<< orphan*/  offset; } ;
struct mtk_sha_reqctx {size_t bufcnt; int offset; int bs; int flags; struct scatterlist* sg; int /*<<< orphan*/  dma_addr; int /*<<< orphan*/  buffer; scalar_t__ total; } ;
struct mtk_sha_rec {int /*<<< orphan*/  flags; int /*<<< orphan*/  req; } ;
struct mtk_cryp {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int EINVAL ; 
 int /*<<< orphan*/  IS_ALIGNED (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  SHA_BUF_SIZE ; 
 int /*<<< orphan*/  SHA_FLAGS_FINAL ; 
 int SHA_FLAGS_FINUP ; 
 int SHA_FLAGS_SG ; 
 struct mtk_sha_reqctx* ahash_request_ctx (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dma_map_sg (int /*<<< orphan*/ ,struct scatterlist*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_map_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_mapping_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int min (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtk_sha_append_sg (struct mtk_sha_reqctx*) ; 
 int /*<<< orphan*/  mtk_sha_fill_padding (struct mtk_sha_reqctx*,int) ; 
 int mtk_sha_update_slow (struct mtk_cryp*,struct mtk_sha_rec*) ; 
 int mtk_sha_xmit (struct mtk_cryp*,struct mtk_sha_rec*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  sg_dma_address (struct scatterlist*) ; 
 scalar_t__ sg_is_last (struct scatterlist*) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mtk_sha_update_start(struct mtk_cryp *cryp,
				struct mtk_sha_rec *sha)
{
	struct mtk_sha_reqctx *ctx = ahash_request_ctx(sha->req);
	u32 len, final, tail;
	struct scatterlist *sg;

	if (!ctx->total)
		return 0;

	if (ctx->bufcnt || ctx->offset)
		return mtk_sha_update_slow(cryp, sha);

	sg = ctx->sg;

	if (!IS_ALIGNED(sg->offset, sizeof(u32)))
		return mtk_sha_update_slow(cryp, sha);

	if (!sg_is_last(sg) && !IS_ALIGNED(sg->length, ctx->bs))
		/* size is not ctx->bs aligned */
		return mtk_sha_update_slow(cryp, sha);

	len = min(ctx->total, sg->length);

	if (sg_is_last(sg)) {
		if (!(ctx->flags & SHA_FLAGS_FINUP)) {
			/* not last sg must be ctx->bs aligned */
			tail = len & (ctx->bs - 1);
			len -= tail;
		}
	}

	ctx->total -= len;
	ctx->offset = len; /* offset where to start slow */

	final = (ctx->flags & SHA_FLAGS_FINUP) && !ctx->total;

	/* Add padding */
	if (final) {
		size_t count;

		tail = len & (ctx->bs - 1);
		len -= tail;
		ctx->total += tail;
		ctx->offset = len; /* offset where to start slow */

		sg = ctx->sg;
		mtk_sha_append_sg(ctx);
		mtk_sha_fill_padding(ctx, len);

		ctx->dma_addr = dma_map_single(cryp->dev, ctx->buffer,
					       SHA_BUF_SIZE, DMA_TO_DEVICE);
		if (unlikely(dma_mapping_error(cryp->dev, ctx->dma_addr))) {
			dev_err(cryp->dev, "dma map bytes error\n");
			return -EINVAL;
		}

		sha->flags |= SHA_FLAGS_FINAL;
		count = ctx->bufcnt;
		ctx->bufcnt = 0;

		if (len == 0) {
			ctx->flags &= ~SHA_FLAGS_SG;
			return mtk_sha_xmit(cryp, sha, ctx->dma_addr,
					    count, 0, 0);

		} else {
			ctx->sg = sg;
			if (!dma_map_sg(cryp->dev, ctx->sg, 1, DMA_TO_DEVICE)) {
				dev_err(cryp->dev, "dma_map_sg error\n");
				return -EINVAL;
			}

			ctx->flags |= SHA_FLAGS_SG;
			return mtk_sha_xmit(cryp, sha, sg_dma_address(ctx->sg),
					    len, ctx->dma_addr, count);
		}
	}

	if (!dma_map_sg(cryp->dev, ctx->sg, 1, DMA_TO_DEVICE)) {
		dev_err(cryp->dev, "dma_map_sg  error\n");
		return -EINVAL;
	}

	ctx->flags |= SHA_FLAGS_SG;

	return mtk_sha_xmit(cryp, sha, sg_dma_address(ctx->sg),
			    len, 0, 0);
}