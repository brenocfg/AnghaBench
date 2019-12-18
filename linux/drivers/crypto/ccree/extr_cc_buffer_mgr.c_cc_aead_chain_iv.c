#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct device {int dummy; } ;
struct crypto_aead {int dummy; } ;
struct cc_drvdata {int dummy; } ;
struct buffer_array {int dummy; } ;
struct aead_request {int /*<<< orphan*/  iv; int /*<<< orphan*/  base; } ;
struct TYPE_4__ {int /*<<< orphan*/  mlli_nents; } ;
struct TYPE_3__ {scalar_t__ iv_dma_addr; int /*<<< orphan*/ * iv; } ;
struct aead_req_ctx {unsigned int hw_iv_size; int /*<<< orphan*/  assoc_buff_type; TYPE_2__ assoc; TYPE_1__ gen_ctx; scalar_t__ plaintext_authenticate_only; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int /*<<< orphan*/  CC_DMA_BUF_MLLI ; 
 int /*<<< orphan*/  DMA_BIDIRECTIONAL ; 
 int ENOMEM ; 
 unsigned int GCM_BLOCK_RFC4_IV_OFFSET ; 
 struct aead_req_ctx* aead_request_ctx (struct aead_request*) ; 
 int /*<<< orphan*/  cc_add_buffer_entry (struct device*,struct buffer_array*,scalar_t__,unsigned int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cc_gfp_flags (int /*<<< orphan*/ *) ; 
 unsigned int crypto_aead_ivsize (struct crypto_aead*) ; 
 struct crypto_aead* crypto_aead_reqtfm (struct aead_request*) ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,unsigned int,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,unsigned int,int /*<<< orphan*/ ) ; 
 scalar_t__ dma_map_single (struct device*,int /*<<< orphan*/ *,unsigned int,int /*<<< orphan*/ ) ; 
 scalar_t__ dma_mapping_error (struct device*,scalar_t__) ; 
 struct device* drvdata_to_dev (struct cc_drvdata*) ; 
 int /*<<< orphan*/ * kmemdup (int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kzfree (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int cc_aead_chain_iv(struct cc_drvdata *drvdata,
			    struct aead_request *req,
			    struct buffer_array *sg_data,
			    bool is_last, bool do_chain)
{
	struct aead_req_ctx *areq_ctx = aead_request_ctx(req);
	unsigned int hw_iv_size = areq_ctx->hw_iv_size;
	struct device *dev = drvdata_to_dev(drvdata);
	gfp_t flags = cc_gfp_flags(&req->base);
	int rc = 0;

	if (!req->iv) {
		areq_ctx->gen_ctx.iv_dma_addr = 0;
		areq_ctx->gen_ctx.iv = NULL;
		goto chain_iv_exit;
	}

	areq_ctx->gen_ctx.iv = kmemdup(req->iv, hw_iv_size, flags);
	if (!areq_ctx->gen_ctx.iv)
		return -ENOMEM;

	areq_ctx->gen_ctx.iv_dma_addr =
		dma_map_single(dev, areq_ctx->gen_ctx.iv, hw_iv_size,
			       DMA_BIDIRECTIONAL);
	if (dma_mapping_error(dev, areq_ctx->gen_ctx.iv_dma_addr)) {
		dev_err(dev, "Mapping iv %u B at va=%pK for DMA failed\n",
			hw_iv_size, req->iv);
		kzfree(areq_ctx->gen_ctx.iv);
		areq_ctx->gen_ctx.iv = NULL;
		rc = -ENOMEM;
		goto chain_iv_exit;
	}

	dev_dbg(dev, "Mapped iv %u B at va=%pK to dma=%pad\n",
		hw_iv_size, req->iv, &areq_ctx->gen_ctx.iv_dma_addr);
	// TODO: what about CTR?? ask Ron
	if (do_chain && areq_ctx->plaintext_authenticate_only) {
		struct crypto_aead *tfm = crypto_aead_reqtfm(req);
		unsigned int iv_size_to_authenc = crypto_aead_ivsize(tfm);
		unsigned int iv_ofs = GCM_BLOCK_RFC4_IV_OFFSET;
		/* Chain to given list */
		cc_add_buffer_entry(dev, sg_data,
				    (areq_ctx->gen_ctx.iv_dma_addr + iv_ofs),
				    iv_size_to_authenc, is_last,
				    &areq_ctx->assoc.mlli_nents);
		areq_ctx->assoc_buff_type = CC_DMA_BUF_MLLI;
	}

chain_iv_exit:
	return rc;
}