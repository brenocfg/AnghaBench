#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct device {int dummy; } ;
struct cc_drvdata {scalar_t__ coherent; } ;
struct aead_request {scalar_t__ src; scalar_t__ dst; int /*<<< orphan*/  cryptlen; } ;
struct TYPE_8__ {scalar_t__ op_type; int /*<<< orphan*/  iv; scalar_t__ iv_dma_addr; } ;
struct TYPE_7__ {int /*<<< orphan*/  nents; } ;
struct TYPE_6__ {int /*<<< orphan*/  nents; } ;
struct TYPE_5__ {int /*<<< orphan*/  mlli_dma_addr; scalar_t__ mlli_virt_addr; int /*<<< orphan*/  curr_pool; } ;
struct aead_req_ctx {unsigned int hw_iv_size; scalar_t__ cipher_mode; scalar_t__ ccm_hdr_size; scalar_t__ assoc_buff_type; scalar_t__ data_buff_type; TYPE_4__ gen_ctx; int /*<<< orphan*/  assoclen; TYPE_3__ assoc; TYPE_2__ src; TYPE_1__ mlli_params; int /*<<< orphan*/  ccm_adata_sg; scalar_t__ ccm_iv0_dma_addr; scalar_t__ gcm_iv_inc2_dma_addr; scalar_t__ gcm_iv_inc1_dma_addr; scalar_t__ gcm_block_len_dma_addr; scalar_t__ hkey_dma_addr; scalar_t__ mac_buf_dma_addr; } ;

/* Variables and functions */
 unsigned int AES_BLOCK_SIZE ; 
 scalar_t__ CC_DMA_BUF_MLLI ; 
 int /*<<< orphan*/  CC_SG_FROM_BUF ; 
 int /*<<< orphan*/  DMA_BIDIRECTIONAL ; 
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 scalar_t__ DRV_CIPHER_GCTR ; 
 scalar_t__ DRV_CRYPTO_DIRECTION_DECRYPT ; 
 unsigned int MAX_MAC_SIZE ; 
 struct aead_req_ctx* aead_request_ctx (struct aead_request*) ; 
 int /*<<< orphan*/  cc_copy_mac (struct device*,struct aead_request*,int /*<<< orphan*/ ) ; 
 scalar_t__ ccm_header_size_null ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,int /*<<< orphan*/ ,...) ; 
 struct cc_drvdata* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  dma_pool_free (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_sg (struct device*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_single (struct device*,scalar_t__,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kzfree (int /*<<< orphan*/ ) ; 
 int sg_nents (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sg_virt (scalar_t__) ; 

void cc_unmap_aead_request(struct device *dev, struct aead_request *req)
{
	struct aead_req_ctx *areq_ctx = aead_request_ctx(req);
	unsigned int hw_iv_size = areq_ctx->hw_iv_size;
	struct cc_drvdata *drvdata = dev_get_drvdata(dev);

	if (areq_ctx->mac_buf_dma_addr) {
		dma_unmap_single(dev, areq_ctx->mac_buf_dma_addr,
				 MAX_MAC_SIZE, DMA_BIDIRECTIONAL);
	}

	if (areq_ctx->cipher_mode == DRV_CIPHER_GCTR) {
		if (areq_ctx->hkey_dma_addr) {
			dma_unmap_single(dev, areq_ctx->hkey_dma_addr,
					 AES_BLOCK_SIZE, DMA_BIDIRECTIONAL);
		}

		if (areq_ctx->gcm_block_len_dma_addr) {
			dma_unmap_single(dev, areq_ctx->gcm_block_len_dma_addr,
					 AES_BLOCK_SIZE, DMA_TO_DEVICE);
		}

		if (areq_ctx->gcm_iv_inc1_dma_addr) {
			dma_unmap_single(dev, areq_ctx->gcm_iv_inc1_dma_addr,
					 AES_BLOCK_SIZE, DMA_TO_DEVICE);
		}

		if (areq_ctx->gcm_iv_inc2_dma_addr) {
			dma_unmap_single(dev, areq_ctx->gcm_iv_inc2_dma_addr,
					 AES_BLOCK_SIZE, DMA_TO_DEVICE);
		}
	}

	if (areq_ctx->ccm_hdr_size != ccm_header_size_null) {
		if (areq_ctx->ccm_iv0_dma_addr) {
			dma_unmap_single(dev, areq_ctx->ccm_iv0_dma_addr,
					 AES_BLOCK_SIZE, DMA_TO_DEVICE);
		}

		dma_unmap_sg(dev, &areq_ctx->ccm_adata_sg, 1, DMA_TO_DEVICE);
	}
	if (areq_ctx->gen_ctx.iv_dma_addr) {
		dma_unmap_single(dev, areq_ctx->gen_ctx.iv_dma_addr,
				 hw_iv_size, DMA_BIDIRECTIONAL);
		kzfree(areq_ctx->gen_ctx.iv);
	}

	/* Release pool */
	if ((areq_ctx->assoc_buff_type == CC_DMA_BUF_MLLI ||
	     areq_ctx->data_buff_type == CC_DMA_BUF_MLLI) &&
	    (areq_ctx->mlli_params.mlli_virt_addr)) {
		dev_dbg(dev, "free MLLI buffer: dma=%pad virt=%pK\n",
			&areq_ctx->mlli_params.mlli_dma_addr,
			areq_ctx->mlli_params.mlli_virt_addr);
		dma_pool_free(areq_ctx->mlli_params.curr_pool,
			      areq_ctx->mlli_params.mlli_virt_addr,
			      areq_ctx->mlli_params.mlli_dma_addr);
	}

	dev_dbg(dev, "Unmapping src sgl: req->src=%pK areq_ctx->src.nents=%u areq_ctx->assoc.nents=%u assoclen:%u cryptlen=%u\n",
		sg_virt(req->src), areq_ctx->src.nents, areq_ctx->assoc.nents,
		areq_ctx->assoclen, req->cryptlen);

	dma_unmap_sg(dev, req->src, sg_nents(req->src), DMA_BIDIRECTIONAL);
	if (req->src != req->dst) {
		dev_dbg(dev, "Unmapping dst sgl: req->dst=%pK\n",
			sg_virt(req->dst));
		dma_unmap_sg(dev, req->dst, sg_nents(req->dst),
			     DMA_BIDIRECTIONAL);
	}
	if (drvdata->coherent &&
	    areq_ctx->gen_ctx.op_type == DRV_CRYPTO_DIRECTION_DECRYPT &&
	    req->src == req->dst) {
		/* copy back mac from temporary location to deal with possible
		 * data memory overriding that caused by cache coherence
		 * problem.
		 */
		cc_copy_mac(dev, req, CC_SG_FROM_BUF);
	}
}