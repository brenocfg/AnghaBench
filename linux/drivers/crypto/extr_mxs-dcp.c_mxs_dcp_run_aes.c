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
struct dcp_dma_desc {int control0; int size; scalar_t__ status; void* payload; void* destination; void* source; scalar_t__ next_cmd_addr; int /*<<< orphan*/  control1; } ;
struct dcp_async_ctx {size_t chan; int fill; } ;
struct dcp_aes_req_ctx {scalar_t__ ecb; scalar_t__ enc; } ;
struct dcp {int /*<<< orphan*/  dev; TYPE_1__* coh; } ;
struct ablkcipher_request {int dummy; } ;
typedef  void* dma_addr_t ;
struct TYPE_2__ {int /*<<< orphan*/  aes_out_buf; int /*<<< orphan*/  aes_in_buf; int /*<<< orphan*/  aes_key; struct dcp_dma_desc* desc; } ;

/* Variables and functions */
 int AES_BLOCK_SIZE ; 
 int AES_KEYSIZE_128 ; 
 int DCP_BUF_SZ ; 
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int EINVAL ; 
 int MXS_DCP_CONTROL0_CIPHER_ENCRYPT ; 
 int MXS_DCP_CONTROL0_CIPHER_INIT ; 
 int MXS_DCP_CONTROL0_DECR_SEMAPHORE ; 
 int MXS_DCP_CONTROL0_ENABLE_CIPHER ; 
 int MXS_DCP_CONTROL0_INTERRUPT ; 
 int MXS_DCP_CONTROL0_PAYLOAD_KEY ; 
 int /*<<< orphan*/  MXS_DCP_CONTROL1_CIPHER_MODE_CBC ; 
 int /*<<< orphan*/  MXS_DCP_CONTROL1_CIPHER_MODE_ECB ; 
 int /*<<< orphan*/  MXS_DCP_CONTROL1_CIPHER_SELECT_AES128 ; 
 struct dcp_aes_req_ctx* ablkcipher_request_ctx (struct ablkcipher_request*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 void* dma_map_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_single (int /*<<< orphan*/ ,void*,int,int /*<<< orphan*/ ) ; 
 struct dcp* global_sdcp ; 
 int mxs_dcp_start_dma (struct dcp_async_ctx*) ; 

__attribute__((used)) static int mxs_dcp_run_aes(struct dcp_async_ctx *actx,
			   struct ablkcipher_request *req, int init)
{
	struct dcp *sdcp = global_sdcp;
	struct dcp_dma_desc *desc = &sdcp->coh->desc[actx->chan];
	struct dcp_aes_req_ctx *rctx = ablkcipher_request_ctx(req);
	int ret;

	dma_addr_t key_phys = dma_map_single(sdcp->dev, sdcp->coh->aes_key,
					     2 * AES_KEYSIZE_128,
					     DMA_TO_DEVICE);
	dma_addr_t src_phys = dma_map_single(sdcp->dev, sdcp->coh->aes_in_buf,
					     DCP_BUF_SZ, DMA_TO_DEVICE);
	dma_addr_t dst_phys = dma_map_single(sdcp->dev, sdcp->coh->aes_out_buf,
					     DCP_BUF_SZ, DMA_FROM_DEVICE);

	if (actx->fill % AES_BLOCK_SIZE) {
		dev_err(sdcp->dev, "Invalid block size!\n");
		ret = -EINVAL;
		goto aes_done_run;
	}

	/* Fill in the DMA descriptor. */
	desc->control0 = MXS_DCP_CONTROL0_DECR_SEMAPHORE |
		    MXS_DCP_CONTROL0_INTERRUPT |
		    MXS_DCP_CONTROL0_ENABLE_CIPHER;

	/* Payload contains the key. */
	desc->control0 |= MXS_DCP_CONTROL0_PAYLOAD_KEY;

	if (rctx->enc)
		desc->control0 |= MXS_DCP_CONTROL0_CIPHER_ENCRYPT;
	if (init)
		desc->control0 |= MXS_DCP_CONTROL0_CIPHER_INIT;

	desc->control1 = MXS_DCP_CONTROL1_CIPHER_SELECT_AES128;

	if (rctx->ecb)
		desc->control1 |= MXS_DCP_CONTROL1_CIPHER_MODE_ECB;
	else
		desc->control1 |= MXS_DCP_CONTROL1_CIPHER_MODE_CBC;

	desc->next_cmd_addr = 0;
	desc->source = src_phys;
	desc->destination = dst_phys;
	desc->size = actx->fill;
	desc->payload = key_phys;
	desc->status = 0;

	ret = mxs_dcp_start_dma(actx);

aes_done_run:
	dma_unmap_single(sdcp->dev, key_phys, 2 * AES_KEYSIZE_128,
			 DMA_TO_DEVICE);
	dma_unmap_single(sdcp->dev, src_phys, DCP_BUF_SZ, DMA_TO_DEVICE);
	dma_unmap_single(sdcp->dev, dst_phys, DCP_BUF_SZ, DMA_FROM_DEVICE);

	return ret;
}