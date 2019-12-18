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
struct talitos_private {int dummy; } ;
struct talitos_desc {int /*<<< orphan*/ * ptr; } ;
struct talitos_edesc {int /*<<< orphan*/  dma_len; int /*<<< orphan*/  dma_link_tbl; scalar_t__ src_nents; scalar_t__ dst_nents; int /*<<< orphan*/  buf; int /*<<< orphan*/  iv_dma; struct talitos_desc desc; } ;
struct talitos_ctx {unsigned int keylen; int /*<<< orphan*/  ch; int /*<<< orphan*/  iv; int /*<<< orphan*/  dma_key; struct device* dev; } ;
struct device {int dummy; } ;
struct crypto_ablkcipher {int dummy; } ;
struct ablkcipher_request {unsigned int nbytes; scalar_t__ src; scalar_t__ dst; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_BIDIRECTIONAL ; 
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int EINPROGRESS ; 
 int /*<<< orphan*/  common_nonsnoop_unmap (struct device*,struct talitos_edesc*,struct ablkcipher_request*) ; 
 struct talitos_ctx* crypto_ablkcipher_ctx (struct crypto_ablkcipher*) ; 
 unsigned int crypto_ablkcipher_ivsize (struct crypto_ablkcipher*) ; 
 struct crypto_ablkcipher* crypto_ablkcipher_reqtfm (struct ablkcipher_request*) ; 
 struct talitos_private* dev_get_drvdata (struct device*) ; 
 int dma_map_sg (struct device*,scalar_t__,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_sync_single_for_device (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int has_ftr_sec1 (struct talitos_private*) ; 
 int /*<<< orphan*/  kfree (struct talitos_edesc*) ; 
 int /*<<< orphan*/  map_single_talitos_ptr (struct device*,int /*<<< orphan*/ *,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sg_copy_to_buffer (scalar_t__,int,int /*<<< orphan*/ ,unsigned int) ; 
 int talitos_sg_map (struct device*,scalar_t__,unsigned int,struct talitos_edesc*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,scalar_t__) ; 
 int talitos_submit (struct device*,int /*<<< orphan*/ ,struct talitos_desc*,void (*) (struct device*,struct talitos_desc*,void*,int),struct ablkcipher_request*) ; 
 int /*<<< orphan*/  to_talitos_ptr (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned int,int) ; 

__attribute__((used)) static int common_nonsnoop(struct talitos_edesc *edesc,
			   struct ablkcipher_request *areq,
			   void (*callback) (struct device *dev,
					     struct talitos_desc *desc,
					     void *context, int error))
{
	struct crypto_ablkcipher *cipher = crypto_ablkcipher_reqtfm(areq);
	struct talitos_ctx *ctx = crypto_ablkcipher_ctx(cipher);
	struct device *dev = ctx->dev;
	struct talitos_desc *desc = &edesc->desc;
	unsigned int cryptlen = areq->nbytes;
	unsigned int ivsize = crypto_ablkcipher_ivsize(cipher);
	int sg_count, ret;
	bool sync_needed = false;
	struct talitos_private *priv = dev_get_drvdata(dev);
	bool is_sec1 = has_ftr_sec1(priv);

	/* first DWORD empty */

	/* cipher iv */
	to_talitos_ptr(&desc->ptr[1], edesc->iv_dma, ivsize, is_sec1);

	/* cipher key */
	to_talitos_ptr(&desc->ptr[2], ctx->dma_key, ctx->keylen, is_sec1);

	sg_count = edesc->src_nents ?: 1;
	if (is_sec1 && sg_count > 1)
		sg_copy_to_buffer(areq->src, sg_count, edesc->buf,
				  cryptlen);
	else
		sg_count = dma_map_sg(dev, areq->src, sg_count,
				      (areq->src == areq->dst) ?
				      DMA_BIDIRECTIONAL : DMA_TO_DEVICE);
	/*
	 * cipher in
	 */
	sg_count = talitos_sg_map(dev, areq->src, cryptlen, edesc,
				  &desc->ptr[3], sg_count, 0, 0);
	if (sg_count > 1)
		sync_needed = true;

	/* cipher out */
	if (areq->src != areq->dst) {
		sg_count = edesc->dst_nents ? : 1;
		if (!is_sec1 || sg_count == 1)
			dma_map_sg(dev, areq->dst, sg_count, DMA_FROM_DEVICE);
	}

	ret = talitos_sg_map(dev, areq->dst, cryptlen, edesc, &desc->ptr[4],
			     sg_count, 0, (edesc->src_nents + 1));
	if (ret > 1)
		sync_needed = true;

	/* iv out */
	map_single_talitos_ptr(dev, &desc->ptr[5], ivsize, ctx->iv,
			       DMA_FROM_DEVICE);

	/* last DWORD empty */

	if (sync_needed)
		dma_sync_single_for_device(dev, edesc->dma_link_tbl,
					   edesc->dma_len, DMA_BIDIRECTIONAL);

	ret = talitos_submit(dev, ctx->ch, desc, callback, areq);
	if (ret != -EINPROGRESS) {
		common_nonsnoop_unmap(dev, edesc, areq);
		kfree(edesc);
	}
	return ret;
}