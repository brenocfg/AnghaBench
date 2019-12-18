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
struct rsa_edesc {scalar_t__ sec4_sg_bytes; int /*<<< orphan*/  sec4_sg_dma; int /*<<< orphan*/  src_nents; int /*<<< orphan*/  dst_nents; } ;
struct device {int dummy; } ;
struct caam_rsa_req_ctx {int /*<<< orphan*/  fixup_src; } ;
struct akcipher_request {int /*<<< orphan*/  dst; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 struct caam_rsa_req_ctx* akcipher_request_ctx (struct akcipher_request*) ; 
 int /*<<< orphan*/  dma_unmap_sg (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_single (struct device*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rsa_io_unmap(struct device *dev, struct rsa_edesc *edesc,
			 struct akcipher_request *req)
{
	struct caam_rsa_req_ctx *req_ctx = akcipher_request_ctx(req);

	dma_unmap_sg(dev, req->dst, edesc->dst_nents, DMA_FROM_DEVICE);
	dma_unmap_sg(dev, req_ctx->fixup_src, edesc->src_nents, DMA_TO_DEVICE);

	if (edesc->sec4_sg_bytes)
		dma_unmap_single(dev, edesc->sec4_sg_dma, edesc->sec4_sg_bytes,
				 DMA_TO_DEVICE);
}