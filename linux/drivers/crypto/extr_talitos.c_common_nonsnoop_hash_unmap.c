#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct talitos_private {int dummy; } ;
struct talitos_desc {scalar_t__ next_desc; TYPE_1__* ptr; } ;
struct talitos_edesc {struct talitos_desc desc; scalar_t__ dma_len; int /*<<< orphan*/  dma_link_tbl; scalar_t__ buf; } ;
struct talitos_ahash_req_ctx {scalar_t__ nbuf; scalar_t__ psrc; } ;
struct device {int dummy; } ;
struct ahash_request {int dummy; } ;
struct TYPE_3__ {scalar_t__ ptr; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_BIDIRECTIONAL ; 
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 scalar_t__ TALITOS_DESC_SIZE ; 
 struct talitos_ahash_req_ctx* ahash_request_ctx (struct ahash_request*) ; 
 int /*<<< orphan*/  be32_to_cpu (scalar_t__) ; 
 struct talitos_private* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  dma_unmap_single (struct device*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ from_talitos_ptr_len (TYPE_1__*,int) ; 
 int has_ftr_sec1 (struct talitos_private*) ; 
 int /*<<< orphan*/  talitos_sg_unmap (struct device*,struct talitos_edesc*,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unmap_single_talitos_ptr (struct device*,TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void common_nonsnoop_hash_unmap(struct device *dev,
				       struct talitos_edesc *edesc,
				       struct ahash_request *areq)
{
	struct talitos_ahash_req_ctx *req_ctx = ahash_request_ctx(areq);
	struct talitos_private *priv = dev_get_drvdata(dev);
	bool is_sec1 = has_ftr_sec1(priv);
	struct talitos_desc *desc = &edesc->desc;
	struct talitos_desc *desc2 = (struct talitos_desc *)
				     (edesc->buf + edesc->dma_len);

	unmap_single_talitos_ptr(dev, &edesc->desc.ptr[5], DMA_FROM_DEVICE);
	if (desc->next_desc &&
	    desc->ptr[5].ptr != desc2->ptr[5].ptr)
		unmap_single_talitos_ptr(dev, &desc2->ptr[5], DMA_FROM_DEVICE);

	if (req_ctx->psrc)
		talitos_sg_unmap(dev, edesc, req_ctx->psrc, NULL, 0, 0);

	/* When using hashctx-in, must unmap it. */
	if (from_talitos_ptr_len(&edesc->desc.ptr[1], is_sec1))
		unmap_single_talitos_ptr(dev, &edesc->desc.ptr[1],
					 DMA_TO_DEVICE);
	else if (desc->next_desc)
		unmap_single_talitos_ptr(dev, &desc2->ptr[1],
					 DMA_TO_DEVICE);

	if (is_sec1 && req_ctx->nbuf)
		unmap_single_talitos_ptr(dev, &desc->ptr[3],
					 DMA_TO_DEVICE);

	if (edesc->dma_len)
		dma_unmap_single(dev, edesc->dma_link_tbl, edesc->dma_len,
				 DMA_BIDIRECTIONAL);

	if (edesc->desc.next_desc)
		dma_unmap_single(dev, be32_to_cpu(edesc->desc.next_desc),
				 TALITOS_DESC_SIZE, DMA_BIDIRECTIONAL);
}