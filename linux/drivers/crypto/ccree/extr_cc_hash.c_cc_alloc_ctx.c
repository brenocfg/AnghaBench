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
struct TYPE_2__ {scalar_t__ keylen; } ;
struct cc_hash_ctx {int is_hmac; void* opad_tmp_keys_dma_addr; scalar_t__ opad_tmp_keys_buff; void* digest_buff_dma_addr; scalar_t__ digest_buff; TYPE_1__ key_params; int /*<<< orphan*/  drvdata; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_BIDIRECTIONAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  cc_free_ctx (struct cc_hash_ctx*) ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,int,scalar_t__,void**) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int,scalar_t__) ; 
 void* dma_map_single (struct device*,void*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ dma_mapping_error (struct device*,void*) ; 
 struct device* drvdata_to_dev (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cc_alloc_ctx(struct cc_hash_ctx *ctx)
{
	struct device *dev = drvdata_to_dev(ctx->drvdata);

	ctx->key_params.keylen = 0;

	ctx->digest_buff_dma_addr =
		dma_map_single(dev, (void *)ctx->digest_buff,
			       sizeof(ctx->digest_buff), DMA_BIDIRECTIONAL);
	if (dma_mapping_error(dev, ctx->digest_buff_dma_addr)) {
		dev_err(dev, "Mapping digest len %zu B at va=%pK for DMA failed\n",
			sizeof(ctx->digest_buff), ctx->digest_buff);
		goto fail;
	}
	dev_dbg(dev, "Mapped digest %zu B at va=%pK to dma=%pad\n",
		sizeof(ctx->digest_buff), ctx->digest_buff,
		&ctx->digest_buff_dma_addr);

	ctx->opad_tmp_keys_dma_addr =
		dma_map_single(dev, (void *)ctx->opad_tmp_keys_buff,
			       sizeof(ctx->opad_tmp_keys_buff),
			       DMA_BIDIRECTIONAL);
	if (dma_mapping_error(dev, ctx->opad_tmp_keys_dma_addr)) {
		dev_err(dev, "Mapping opad digest %zu B at va=%pK for DMA failed\n",
			sizeof(ctx->opad_tmp_keys_buff),
			ctx->opad_tmp_keys_buff);
		goto fail;
	}
	dev_dbg(dev, "Mapped opad_tmp_keys %zu B at va=%pK to dma=%pad\n",
		sizeof(ctx->opad_tmp_keys_buff), ctx->opad_tmp_keys_buff,
		&ctx->opad_tmp_keys_dma_addr);

	ctx->is_hmac = false;
	return 0;

fail:
	cc_free_ctx(ctx);
	return -ENOMEM;
}