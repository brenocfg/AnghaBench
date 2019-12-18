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
struct device {int dummy; } ;
struct crypto_aead {int dummy; } ;
struct cc_drvdata {int dummy; } ;
struct buffer_array {int dummy; } ;
struct aead_request {int /*<<< orphan*/  src; } ;
struct TYPE_2__ {int nents; scalar_t__ mlli_nents; } ;
struct aead_req_ctx {unsigned int assoclen; scalar_t__ assoc_buff_type; scalar_t__ ccm_hdr_size; TYPE_1__ assoc; scalar_t__ is_gcm4543; } ;

/* Variables and functions */
 scalar_t__ CC_DMA_BUF_DLLI ; 
 scalar_t__ CC_DMA_BUF_MLLI ; 
 scalar_t__ CC_DMA_BUF_NULL ; 
 int EINVAL ; 
 int ENOMEM ; 
 int LLI_MAX_NUM_OF_ASSOC_DATA_ENTRIES ; 
 struct aead_req_ctx* aead_request_ctx (struct aead_request*) ; 
 int /*<<< orphan*/  cc_add_sg_entry (struct device*,struct buffer_array*,int,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ,int,scalar_t__*) ; 
 int /*<<< orphan*/  cc_dma_buf_type (scalar_t__) ; 
 scalar_t__ ccm_header_size_null ; 
 scalar_t__ crypto_aead_ivsize (struct crypto_aead*) ; 
 struct crypto_aead* crypto_aead_reqtfm (struct aead_request*) ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int,int) ; 
 struct device* drvdata_to_dev (struct cc_drvdata*) ; 
 int sg_nents_for_len (int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static int cc_aead_chain_assoc(struct cc_drvdata *drvdata,
			       struct aead_request *req,
			       struct buffer_array *sg_data,
			       bool is_last, bool do_chain)
{
	struct aead_req_ctx *areq_ctx = aead_request_ctx(req);
	int rc = 0;
	int mapped_nents = 0;
	struct crypto_aead *tfm = crypto_aead_reqtfm(req);
	unsigned int size_of_assoc = areq_ctx->assoclen;
	struct device *dev = drvdata_to_dev(drvdata);

	if (areq_ctx->is_gcm4543)
		size_of_assoc += crypto_aead_ivsize(tfm);

	if (!sg_data) {
		rc = -EINVAL;
		goto chain_assoc_exit;
	}

	if (areq_ctx->assoclen == 0) {
		areq_ctx->assoc_buff_type = CC_DMA_BUF_NULL;
		areq_ctx->assoc.nents = 0;
		areq_ctx->assoc.mlli_nents = 0;
		dev_dbg(dev, "Chain assoc of length 0: buff_type=%s nents=%u\n",
			cc_dma_buf_type(areq_ctx->assoc_buff_type),
			areq_ctx->assoc.nents);
		goto chain_assoc_exit;
	}

	mapped_nents = sg_nents_for_len(req->src, size_of_assoc);
	if (mapped_nents < 0)
		return mapped_nents;

	if (mapped_nents > LLI_MAX_NUM_OF_ASSOC_DATA_ENTRIES) {
		dev_err(dev, "Too many fragments. current %d max %d\n",
			mapped_nents, LLI_MAX_NUM_OF_ASSOC_DATA_ENTRIES);
		return -ENOMEM;
	}
	areq_ctx->assoc.nents = mapped_nents;

	/* in CCM case we have additional entry for
	 * ccm header configurations
	 */
	if (areq_ctx->ccm_hdr_size != ccm_header_size_null) {
		if ((mapped_nents + 1) > LLI_MAX_NUM_OF_ASSOC_DATA_ENTRIES) {
			dev_err(dev, "CCM case.Too many fragments. Current %d max %d\n",
				(areq_ctx->assoc.nents + 1),
				LLI_MAX_NUM_OF_ASSOC_DATA_ENTRIES);
			rc = -ENOMEM;
			goto chain_assoc_exit;
		}
	}

	if (mapped_nents == 1 && areq_ctx->ccm_hdr_size == ccm_header_size_null)
		areq_ctx->assoc_buff_type = CC_DMA_BUF_DLLI;
	else
		areq_ctx->assoc_buff_type = CC_DMA_BUF_MLLI;

	if (do_chain || areq_ctx->assoc_buff_type == CC_DMA_BUF_MLLI) {
		dev_dbg(dev, "Chain assoc: buff_type=%s nents=%u\n",
			cc_dma_buf_type(areq_ctx->assoc_buff_type),
			areq_ctx->assoc.nents);
		cc_add_sg_entry(dev, sg_data, areq_ctx->assoc.nents, req->src,
				areq_ctx->assoclen, 0, is_last,
				&areq_ctx->assoc.mlli_nents);
		areq_ctx->assoc_buff_type = CC_DMA_BUF_MLLI;
	}

chain_assoc_exit:
	return rc;
}