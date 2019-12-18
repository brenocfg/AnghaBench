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
struct sec4_sg_entry {int dummy; } ;
struct device {int dummy; } ;
struct crypto_aead {int dummy; } ;
struct caam_ctx {unsigned int authsize; struct device* jrdev; } ;
struct TYPE_2__ {int flags; } ;
struct aead_request {int assoclen; int cryptlen; int /*<<< orphan*/  dst; int /*<<< orphan*/  src; TYPE_1__ base; } ;
struct aead_edesc {int src_nents; int dst_nents; int mapped_src_nents; int mapped_dst_nents; int sec4_sg_bytes; int /*<<< orphan*/  sec4_sg_dma; void* sec4_sg; } ;
typedef  int gfp_t ;

/* Variables and functions */
 int CRYPTO_TFM_REQ_MAY_SLEEP ; 
 int /*<<< orphan*/  DMA_BIDIRECTIONAL ; 
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int ENOMEM ; 
 struct aead_edesc* ERR_PTR (int) ; 
 int GFP_ATOMIC ; 
 int GFP_DMA ; 
 int GFP_KERNEL ; 
 int /*<<< orphan*/  aead_unmap (struct device*,struct aead_edesc*,struct aead_request*) ; 
 int /*<<< orphan*/  caam_unmap (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct caam_ctx* crypto_aead_ctx (struct crypto_aead*) ; 
 struct crypto_aead* crypto_aead_reqtfm (struct aead_request*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 int dma_map_sg (struct device*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_map_single (struct device*,void*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ dma_mapping_error (struct device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_sg (struct device*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct aead_edesc*) ; 
 struct aead_edesc* kzalloc (int,int) ; 
 scalar_t__ likely (int) ; 
 int pad_sg_nents (int) ; 
 int sg_nents_for_len (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sg_to_sec4_sg_last (int /*<<< orphan*/ ,int,void*,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static struct aead_edesc *aead_edesc_alloc(struct aead_request *req,
					   int desc_bytes, bool *all_contig_ptr,
					   bool encrypt)
{
	struct crypto_aead *aead = crypto_aead_reqtfm(req);
	struct caam_ctx *ctx = crypto_aead_ctx(aead);
	struct device *jrdev = ctx->jrdev;
	gfp_t flags = (req->base.flags & CRYPTO_TFM_REQ_MAY_SLEEP) ?
		       GFP_KERNEL : GFP_ATOMIC;
	int src_nents, mapped_src_nents, dst_nents = 0, mapped_dst_nents = 0;
	int src_len, dst_len = 0;
	struct aead_edesc *edesc;
	int sec4_sg_index, sec4_sg_len, sec4_sg_bytes;
	unsigned int authsize = ctx->authsize;

	if (unlikely(req->dst != req->src)) {
		src_len = req->assoclen + req->cryptlen;
		dst_len = src_len + (encrypt ? authsize : (-authsize));

		src_nents = sg_nents_for_len(req->src, src_len);
		if (unlikely(src_nents < 0)) {
			dev_err(jrdev, "Insufficient bytes (%d) in src S/G\n",
				src_len);
			return ERR_PTR(src_nents);
		}

		dst_nents = sg_nents_for_len(req->dst, dst_len);
		if (unlikely(dst_nents < 0)) {
			dev_err(jrdev, "Insufficient bytes (%d) in dst S/G\n",
				dst_len);
			return ERR_PTR(dst_nents);
		}
	} else {
		src_len = req->assoclen + req->cryptlen +
			  (encrypt ? authsize : 0);

		src_nents = sg_nents_for_len(req->src, src_len);
		if (unlikely(src_nents < 0)) {
			dev_err(jrdev, "Insufficient bytes (%d) in src S/G\n",
				src_len);
			return ERR_PTR(src_nents);
		}
	}

	if (likely(req->src == req->dst)) {
		mapped_src_nents = dma_map_sg(jrdev, req->src, src_nents,
					      DMA_BIDIRECTIONAL);
		if (unlikely(!mapped_src_nents)) {
			dev_err(jrdev, "unable to map source\n");
			return ERR_PTR(-ENOMEM);
		}
	} else {
		/* Cover also the case of null (zero length) input data */
		if (src_nents) {
			mapped_src_nents = dma_map_sg(jrdev, req->src,
						      src_nents, DMA_TO_DEVICE);
			if (unlikely(!mapped_src_nents)) {
				dev_err(jrdev, "unable to map source\n");
				return ERR_PTR(-ENOMEM);
			}
		} else {
			mapped_src_nents = 0;
		}

		/* Cover also the case of null (zero length) output data */
		if (dst_nents) {
			mapped_dst_nents = dma_map_sg(jrdev, req->dst,
						      dst_nents,
						      DMA_FROM_DEVICE);
			if (unlikely(!mapped_dst_nents)) {
				dev_err(jrdev, "unable to map destination\n");
				dma_unmap_sg(jrdev, req->src, src_nents,
					     DMA_TO_DEVICE);
				return ERR_PTR(-ENOMEM);
			}
		} else {
			mapped_dst_nents = 0;
		}
	}

	/*
	 * HW reads 4 S/G entries at a time; make sure the reads don't go beyond
	 * the end of the table by allocating more S/G entries.
	 */
	sec4_sg_len = mapped_src_nents > 1 ? mapped_src_nents : 0;
	if (mapped_dst_nents > 1)
		sec4_sg_len += pad_sg_nents(mapped_dst_nents);
	else
		sec4_sg_len = pad_sg_nents(sec4_sg_len);

	sec4_sg_bytes = sec4_sg_len * sizeof(struct sec4_sg_entry);

	/* allocate space for base edesc and hw desc commands, link tables */
	edesc = kzalloc(sizeof(*edesc) + desc_bytes + sec4_sg_bytes,
			GFP_DMA | flags);
	if (!edesc) {
		caam_unmap(jrdev, req->src, req->dst, src_nents, dst_nents, 0,
			   0, 0, 0);
		return ERR_PTR(-ENOMEM);
	}

	edesc->src_nents = src_nents;
	edesc->dst_nents = dst_nents;
	edesc->mapped_src_nents = mapped_src_nents;
	edesc->mapped_dst_nents = mapped_dst_nents;
	edesc->sec4_sg = (void *)edesc + sizeof(struct aead_edesc) +
			 desc_bytes;
	*all_contig_ptr = !(mapped_src_nents > 1);

	sec4_sg_index = 0;
	if (mapped_src_nents > 1) {
		sg_to_sec4_sg_last(req->src, src_len,
				   edesc->sec4_sg + sec4_sg_index, 0);
		sec4_sg_index += mapped_src_nents;
	}
	if (mapped_dst_nents > 1) {
		sg_to_sec4_sg_last(req->dst, dst_len,
				   edesc->sec4_sg + sec4_sg_index, 0);
	}

	if (!sec4_sg_bytes)
		return edesc;

	edesc->sec4_sg_dma = dma_map_single(jrdev, edesc->sec4_sg,
					    sec4_sg_bytes, DMA_TO_DEVICE);
	if (dma_mapping_error(jrdev, edesc->sec4_sg_dma)) {
		dev_err(jrdev, "unable to map S/G table\n");
		aead_unmap(jrdev, edesc, req);
		kfree(edesc);
		return ERR_PTR(-ENOMEM);
	}

	edesc->sec4_sg_bytes = sec4_sg_bytes;

	return edesc;
}