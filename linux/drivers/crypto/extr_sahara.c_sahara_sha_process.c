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
struct sahara_sha_reqctx {int /*<<< orphan*/  digest_size; scalar_t__ context; int /*<<< orphan*/  context_size; scalar_t__ sg_in_idx; scalar_t__ first; } ;
struct sahara_dev {scalar_t__ context_base; int /*<<< orphan*/  nb_in_sg; int /*<<< orphan*/  in_sg; int /*<<< orphan*/  device; int /*<<< orphan*/  dma_completion; scalar_t__* hw_phys_desc; TYPE_1__** hw_desc; } ;
struct ahash_request {scalar_t__ result; } ;
struct TYPE_2__ {scalar_t__ next; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int ETIMEDOUT ; 
 int /*<<< orphan*/  SAHARA_REG_DAR ; 
 int /*<<< orphan*/  SAHARA_TIMEOUT_MS ; 
 struct sahara_sha_reqctx* ahash_request_ctx (struct ahash_request*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 struct sahara_dev* dev_ptr ; 
 int /*<<< orphan*/  dma_unmap_sg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reinit_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sahara_dump_descriptors (struct sahara_dev*) ; 
 int /*<<< orphan*/  sahara_dump_links (struct sahara_dev*) ; 
 int /*<<< orphan*/  sahara_sha_hw_context_descriptor_create (struct sahara_dev*,struct sahara_sha_reqctx*,struct ahash_request*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sahara_sha_hw_data_descriptor_create (struct sahara_dev*,struct sahara_sha_reqctx*,struct ahash_request*,int) ; 
 int sahara_sha_prepare_request (struct ahash_request*) ; 
 int /*<<< orphan*/  sahara_write (struct sahara_dev*,scalar_t__,int /*<<< orphan*/ ) ; 
 unsigned long wait_for_completion_timeout (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sahara_sha_process(struct ahash_request *req)
{
	struct sahara_dev *dev = dev_ptr;
	struct sahara_sha_reqctx *rctx = ahash_request_ctx(req);
	int ret;
	unsigned long timeout;

	ret = sahara_sha_prepare_request(req);
	if (!ret)
		return ret;

	if (rctx->first) {
		sahara_sha_hw_data_descriptor_create(dev, rctx, req, 0);
		dev->hw_desc[0]->next = 0;
		rctx->first = 0;
	} else {
		memcpy(dev->context_base, rctx->context, rctx->context_size);

		sahara_sha_hw_context_descriptor_create(dev, rctx, req, 0);
		dev->hw_desc[0]->next = dev->hw_phys_desc[1];
		sahara_sha_hw_data_descriptor_create(dev, rctx, req, 1);
		dev->hw_desc[1]->next = 0;
	}

	sahara_dump_descriptors(dev);
	sahara_dump_links(dev);

	reinit_completion(&dev->dma_completion);

	sahara_write(dev, dev->hw_phys_desc[0], SAHARA_REG_DAR);

	timeout = wait_for_completion_timeout(&dev->dma_completion,
				msecs_to_jiffies(SAHARA_TIMEOUT_MS));
	if (!timeout) {
		dev_err(dev->device, "SHA timeout\n");
		return -ETIMEDOUT;
	}

	if (rctx->sg_in_idx)
		dma_unmap_sg(dev->device, dev->in_sg, dev->nb_in_sg,
			     DMA_TO_DEVICE);

	memcpy(rctx->context, dev->context_base, rctx->context_size);

	if (req->result)
		memcpy(req->result, rctx->context, rctx->digest_size);

	return 0;
}