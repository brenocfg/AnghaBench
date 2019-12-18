#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct talitos_private {int dummy; } ;
struct talitos_desc {int /*<<< orphan*/  next_desc; int /*<<< orphan*/  hdr1; TYPE_1__* ptr; int /*<<< orphan*/  hdr; } ;
struct talitos_edesc {scalar_t__ dma_len; int /*<<< orphan*/  dma_link_tbl; scalar_t__ buf; scalar_t__ src_nents; struct talitos_desc desc; } ;
struct talitos_ctx {int /*<<< orphan*/  ch; scalar_t__ keylen; int /*<<< orphan*/  dma_key; struct device* dev; } ;
struct talitos_ahash_req_ctx {size_t buf_idx; int /*<<< orphan*/  hw_context; int /*<<< orphan*/  hw_context_size; scalar_t__ last; int /*<<< orphan*/  psrc; scalar_t__ nbuf; int /*<<< orphan*/ * buf; scalar_t__ first; scalar_t__ swinit; } ;
struct device {int dummy; } ;
struct crypto_ahash {int dummy; } ;
struct ahash_request {int /*<<< orphan*/  result; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;
struct TYPE_9__ {scalar_t__ ptr; } ;

/* Variables and functions */
 int /*<<< orphan*/  DESC_HDR_DONE_NOTIFY ; 
 int /*<<< orphan*/  DESC_HDR_MODE0_MDEU_CONT ; 
 int /*<<< orphan*/  DESC_HDR_MODE0_MDEU_INIT ; 
 int /*<<< orphan*/  DESC_HDR_MODE0_MDEU_PAD ; 
 int /*<<< orphan*/  DMA_BIDIRECTIONAL ; 
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int EINPROGRESS ; 
 int /*<<< orphan*/  TALITOS_DESC_SIZE ; 
 struct talitos_ahash_req_ctx* ahash_request_ctx (struct ahash_request*) ; 
 int /*<<< orphan*/  common_nonsnoop_hash_unmap (struct device*,struct talitos_edesc*,struct ahash_request*) ; 
 int /*<<< orphan*/  copy_talitos_ptr (TYPE_1__*,TYPE_1__*,int) ; 
 int /*<<< orphan*/  cpu_to_be32 (int /*<<< orphan*/ ) ; 
 struct talitos_ctx* crypto_ahash_ctx (struct crypto_ahash*) ; 
 scalar_t__ crypto_ahash_digestsize (struct crypto_ahash*) ; 
 struct crypto_ahash* crypto_ahash_reqtfm (struct ahash_request*) ; 
 struct talitos_private* dev_get_drvdata (struct device*) ; 
 int dma_map_sg (struct device*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_map_single (struct device*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_sync_single_for_device (struct device*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ from_talitos_ptr_len (TYPE_1__*,int) ; 
 int has_ftr_sec1 (struct talitos_private*) ; 
 int /*<<< orphan*/  kfree (struct talitos_edesc*) ; 
 int /*<<< orphan*/  map_single_talitos_ptr (struct device*,TYPE_1__*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  map_single_talitos_ptr_nosync (struct device*,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct talitos_desc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sg_copy_to_buffer (int /*<<< orphan*/ ,int,scalar_t__,unsigned int) ; 
 int /*<<< orphan*/  talitos_handle_buggy_hash (struct talitos_ctx*,struct talitos_edesc*,TYPE_1__*) ; 
 int talitos_sg_map (struct device*,int /*<<< orphan*/ ,unsigned int,struct talitos_edesc*,TYPE_1__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int talitos_submit (struct device*,int /*<<< orphan*/ ,struct talitos_desc*,void (*) (struct device*,struct talitos_desc*,void*,int),struct ahash_request*) ; 
 int /*<<< orphan*/  to_talitos_ptr (TYPE_1__*,int /*<<< orphan*/ ,scalar_t__,int) ; 

__attribute__((used)) static int common_nonsnoop_hash(struct talitos_edesc *edesc,
				struct ahash_request *areq, unsigned int length,
				void (*callback) (struct device *dev,
						  struct talitos_desc *desc,
						  void *context, int error))
{
	struct crypto_ahash *tfm = crypto_ahash_reqtfm(areq);
	struct talitos_ctx *ctx = crypto_ahash_ctx(tfm);
	struct talitos_ahash_req_ctx *req_ctx = ahash_request_ctx(areq);
	struct device *dev = ctx->dev;
	struct talitos_desc *desc = &edesc->desc;
	int ret;
	bool sync_needed = false;
	struct talitos_private *priv = dev_get_drvdata(dev);
	bool is_sec1 = has_ftr_sec1(priv);
	int sg_count;

	/* first DWORD empty */

	/* hash context in */
	if (!req_ctx->first || req_ctx->swinit) {
		map_single_talitos_ptr_nosync(dev, &desc->ptr[1],
					      req_ctx->hw_context_size,
					      req_ctx->hw_context,
					      DMA_TO_DEVICE);
		req_ctx->swinit = 0;
	}
	/* Indicate next op is not the first. */
	req_ctx->first = 0;

	/* HMAC key */
	if (ctx->keylen)
		to_talitos_ptr(&desc->ptr[2], ctx->dma_key, ctx->keylen,
			       is_sec1);

	if (is_sec1 && req_ctx->nbuf)
		length -= req_ctx->nbuf;

	sg_count = edesc->src_nents ?: 1;
	if (is_sec1 && sg_count > 1)
		sg_copy_to_buffer(req_ctx->psrc, sg_count, edesc->buf, length);
	else if (length)
		sg_count = dma_map_sg(dev, req_ctx->psrc, sg_count,
				      DMA_TO_DEVICE);
	/*
	 * data in
	 */
	if (is_sec1 && req_ctx->nbuf) {
		map_single_talitos_ptr(dev, &desc->ptr[3], req_ctx->nbuf,
				       req_ctx->buf[req_ctx->buf_idx],
				       DMA_TO_DEVICE);
	} else {
		sg_count = talitos_sg_map(dev, req_ctx->psrc, length, edesc,
					  &desc->ptr[3], sg_count, 0, 0);
		if (sg_count > 1)
			sync_needed = true;
	}

	/* fifth DWORD empty */

	/* hash/HMAC out -or- hash context out */
	if (req_ctx->last)
		map_single_talitos_ptr(dev, &desc->ptr[5],
				       crypto_ahash_digestsize(tfm),
				       areq->result, DMA_FROM_DEVICE);
	else
		map_single_talitos_ptr_nosync(dev, &desc->ptr[5],
					      req_ctx->hw_context_size,
					      req_ctx->hw_context,
					      DMA_FROM_DEVICE);

	/* last DWORD empty */

	if (is_sec1 && from_talitos_ptr_len(&desc->ptr[3], true) == 0)
		talitos_handle_buggy_hash(ctx, edesc, &desc->ptr[3]);

	if (is_sec1 && req_ctx->nbuf && length) {
		struct talitos_desc *desc2 = (struct talitos_desc *)
					     (edesc->buf + edesc->dma_len);
		dma_addr_t next_desc;

		memset(desc2, 0, sizeof(*desc2));
		desc2->hdr = desc->hdr;
		desc2->hdr &= ~DESC_HDR_MODE0_MDEU_INIT;
		desc2->hdr1 = desc2->hdr;
		desc->hdr &= ~DESC_HDR_MODE0_MDEU_PAD;
		desc->hdr |= DESC_HDR_MODE0_MDEU_CONT;
		desc->hdr &= ~DESC_HDR_DONE_NOTIFY;

		if (desc->ptr[1].ptr)
			copy_talitos_ptr(&desc2->ptr[1], &desc->ptr[1],
					 is_sec1);
		else
			map_single_talitos_ptr_nosync(dev, &desc2->ptr[1],
						      req_ctx->hw_context_size,
						      req_ctx->hw_context,
						      DMA_TO_DEVICE);
		copy_talitos_ptr(&desc2->ptr[2], &desc->ptr[2], is_sec1);
		sg_count = talitos_sg_map(dev, req_ctx->psrc, length, edesc,
					  &desc2->ptr[3], sg_count, 0, 0);
		if (sg_count > 1)
			sync_needed = true;
		copy_talitos_ptr(&desc2->ptr[5], &desc->ptr[5], is_sec1);
		if (req_ctx->last)
			map_single_talitos_ptr_nosync(dev, &desc->ptr[5],
						      req_ctx->hw_context_size,
						      req_ctx->hw_context,
						      DMA_FROM_DEVICE);

		next_desc = dma_map_single(dev, &desc2->hdr1, TALITOS_DESC_SIZE,
					   DMA_BIDIRECTIONAL);
		desc->next_desc = cpu_to_be32(next_desc);
	}

	if (sync_needed)
		dma_sync_single_for_device(dev, edesc->dma_link_tbl,
					   edesc->dma_len, DMA_BIDIRECTIONAL);

	ret = talitos_submit(dev, ctx->ch, desc, callback, areq);
	if (ret != -EINPROGRESS) {
		common_nonsnoop_hash_unmap(dev, edesc, areq);
		kfree(edesc);
	}
	return ret;
}