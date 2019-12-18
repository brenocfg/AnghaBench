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
struct scatterlist {int dummy; } ;
struct device {int dummy; } ;
struct crypto_tfm {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  mlli_len; int /*<<< orphan*/  mlli_dma_addr; } ;
struct cipher_req_ctx {scalar_t__ dma_buf_type; TYPE_1__ mlli_params; } ;
struct cc_hw_desc {int dummy; } ;
struct cc_cipher_ctx {TYPE_2__* drvdata; } ;
struct TYPE_4__ {scalar_t__ mlli_sram_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  BYPASS ; 
 scalar_t__ CC_DMA_BUF_MLLI ; 
 int /*<<< orphan*/  DMA_DLLI ; 
 int /*<<< orphan*/  NS_BIT ; 
 struct cc_cipher_ctx* crypto_tfm_ctx (struct crypto_tfm*) ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned int) ; 
 struct device* drvdata_to_dev (TYPE_2__*) ; 
 int /*<<< orphan*/  hw_desc_init (struct cc_hw_desc*) ; 
 int /*<<< orphan*/  set_din_type (struct cc_hw_desc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_dout_sram (struct cc_hw_desc*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_flow_mode (struct cc_hw_desc*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cc_setup_mlli_desc(struct crypto_tfm *tfm,
			       struct cipher_req_ctx *req_ctx,
			       struct scatterlist *dst, struct scatterlist *src,
			       unsigned int nbytes, void *areq,
			       struct cc_hw_desc desc[], unsigned int *seq_size)
{
	struct cc_cipher_ctx *ctx_p = crypto_tfm_ctx(tfm);
	struct device *dev = drvdata_to_dev(ctx_p->drvdata);

	if (req_ctx->dma_buf_type == CC_DMA_BUF_MLLI) {
		/* bypass */
		dev_dbg(dev, " bypass params addr %pad length 0x%X addr 0x%08X\n",
			&req_ctx->mlli_params.mlli_dma_addr,
			req_ctx->mlli_params.mlli_len,
			(unsigned int)ctx_p->drvdata->mlli_sram_addr);
		hw_desc_init(&desc[*seq_size]);
		set_din_type(&desc[*seq_size], DMA_DLLI,
			     req_ctx->mlli_params.mlli_dma_addr,
			     req_ctx->mlli_params.mlli_len, NS_BIT);
		set_dout_sram(&desc[*seq_size],
			      ctx_p->drvdata->mlli_sram_addr,
			      req_ctx->mlli_params.mlli_len);
		set_flow_mode(&desc[*seq_size], BYPASS);
		(*seq_size)++;
	}
}