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
struct cc_hw_desc {int dummy; } ;
struct cc_aead_ctx {int /*<<< orphan*/  auth_mode; int /*<<< orphan*/  drvdata; } ;
struct aead_request {int /*<<< orphan*/  src; } ;
struct TYPE_2__ {int /*<<< orphan*/  mlli_nents; int /*<<< orphan*/  sram_addr; } ;
struct aead_req_ctx {int assoc_buff_type; int /*<<< orphan*/  cryptlen; TYPE_1__ assoc; int /*<<< orphan*/  assoclen; } ;
typedef  enum cc_req_dma_buf_type { ____Placeholder_cc_req_dma_buf_type } cc_req_dma_buf_type ;

/* Variables and functions */
#define  CC_DMA_BUF_DLLI 130 
#define  CC_DMA_BUF_MLLI 129 
#define  CC_DMA_BUF_NULL 128 
 int /*<<< orphan*/  DMA_DLLI ; 
 int /*<<< orphan*/  DMA_MLLI ; 
 int /*<<< orphan*/  DRV_HASH_XCBC_MAC ; 
 int /*<<< orphan*/  NS_BIT ; 
 struct aead_req_ctx* aead_request_ctx (struct aead_request*) ; 
 struct cc_aead_ctx* crypto_aead_ctx (struct crypto_aead*) ; 
 struct crypto_aead* crypto_aead_reqtfm (struct aead_request*) ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 struct device* drvdata_to_dev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hw_desc_init (struct cc_hw_desc*) ; 
 int /*<<< orphan*/  set_din_not_last_indication (struct cc_hw_desc*) ; 
 int /*<<< orphan*/  set_din_type (struct cc_hw_desc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_flow_mode (struct cc_hw_desc*,unsigned int) ; 
 int /*<<< orphan*/  sg_dma_address (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cc_set_assoc_desc(struct aead_request *areq, unsigned int flow_mode,
			      struct cc_hw_desc desc[], unsigned int *seq_size)
{
	struct crypto_aead *tfm = crypto_aead_reqtfm(areq);
	struct cc_aead_ctx *ctx = crypto_aead_ctx(tfm);
	struct aead_req_ctx *areq_ctx = aead_request_ctx(areq);
	enum cc_req_dma_buf_type assoc_dma_type = areq_ctx->assoc_buff_type;
	unsigned int idx = *seq_size;
	struct device *dev = drvdata_to_dev(ctx->drvdata);

	switch (assoc_dma_type) {
	case CC_DMA_BUF_DLLI:
		dev_dbg(dev, "ASSOC buffer type DLLI\n");
		hw_desc_init(&desc[idx]);
		set_din_type(&desc[idx], DMA_DLLI, sg_dma_address(areq->src),
			     areq_ctx->assoclen, NS_BIT);
		set_flow_mode(&desc[idx], flow_mode);
		if (ctx->auth_mode == DRV_HASH_XCBC_MAC &&
		    areq_ctx->cryptlen > 0)
			set_din_not_last_indication(&desc[idx]);
		break;
	case CC_DMA_BUF_MLLI:
		dev_dbg(dev, "ASSOC buffer type MLLI\n");
		hw_desc_init(&desc[idx]);
		set_din_type(&desc[idx], DMA_MLLI, areq_ctx->assoc.sram_addr,
			     areq_ctx->assoc.mlli_nents, NS_BIT);
		set_flow_mode(&desc[idx], flow_mode);
		if (ctx->auth_mode == DRV_HASH_XCBC_MAC &&
		    areq_ctx->cryptlen > 0)
			set_din_not_last_indication(&desc[idx]);
		break;
	case CC_DMA_BUF_NULL:
	default:
		dev_err(dev, "Invalid ASSOC buffer type\n");
	}

	*seq_size = (++idx);
}