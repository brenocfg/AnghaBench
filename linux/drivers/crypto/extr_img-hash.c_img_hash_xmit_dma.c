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
struct scatterlist {int dummy; } ;
struct img_hash_request_ctx {scalar_t__ dma_ct; } ;
struct img_hash_dev {int err; int /*<<< orphan*/  dma_lch; int /*<<< orphan*/  dev; int /*<<< orphan*/  req; } ;
struct dma_async_tx_descriptor {struct img_hash_dev* callback_param; int /*<<< orphan*/  callback; } ;

/* Variables and functions */
 int DMA_CTRL_ACK ; 
 int /*<<< orphan*/  DMA_MEM_TO_DEV ; 
 int DMA_PREP_INTERRUPT ; 
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int EINVAL ; 
 struct img_hash_request_ctx* ahash_request_ctx (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dma_async_issue_pending (int /*<<< orphan*/ ) ; 
 scalar_t__ dma_map_sg (int /*<<< orphan*/ ,struct scatterlist*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_sg (int /*<<< orphan*/ ,struct scatterlist*,int,int /*<<< orphan*/ ) ; 
 struct dma_async_tx_descriptor* dmaengine_prep_slave_sg (int /*<<< orphan*/ ,struct scatterlist*,scalar_t__,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dmaengine_submit (struct dma_async_tx_descriptor*) ; 
 int /*<<< orphan*/  img_hash_dma_callback ; 

__attribute__((used)) static int img_hash_xmit_dma(struct img_hash_dev *hdev, struct scatterlist *sg)
{
	struct dma_async_tx_descriptor *desc;
	struct img_hash_request_ctx *ctx = ahash_request_ctx(hdev->req);

	ctx->dma_ct = dma_map_sg(hdev->dev, sg, 1, DMA_TO_DEVICE);
	if (ctx->dma_ct == 0) {
		dev_err(hdev->dev, "Invalid DMA sg\n");
		hdev->err = -EINVAL;
		return -EINVAL;
	}

	desc = dmaengine_prep_slave_sg(hdev->dma_lch,
				       sg,
				       ctx->dma_ct,
				       DMA_MEM_TO_DEV,
				       DMA_PREP_INTERRUPT | DMA_CTRL_ACK);
	if (!desc) {
		dev_err(hdev->dev, "Null DMA descriptor\n");
		hdev->err = -EINVAL;
		dma_unmap_sg(hdev->dev, sg, 1, DMA_TO_DEVICE);
		return -EINVAL;
	}
	desc->callback = img_hash_dma_callback;
	desc->callback_param = hdev;
	dmaengine_submit(desc);
	dma_async_issue_pending(hdev->dma_lch);

	return 0;
}