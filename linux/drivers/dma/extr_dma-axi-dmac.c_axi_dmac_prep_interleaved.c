#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct dma_interleaved_template {int frame_size; scalar_t__ dir; int numf; TYPE_2__* sgl; int /*<<< orphan*/  dst_start; int /*<<< orphan*/  src_start; int /*<<< orphan*/  dst_inc; int /*<<< orphan*/  src_inc; } ;
struct dma_chan {int dummy; } ;
struct dma_async_tx_descriptor {int dummy; } ;
struct axi_dmac_desc {int cyclic; int /*<<< orphan*/  vdesc; TYPE_1__* sg; } ;
struct axi_dmac_chan {scalar_t__ direction; size_t max_length; int /*<<< orphan*/  vchan; scalar_t__ hw_2d; } ;
struct TYPE_5__ {int size; } ;
struct TYPE_4__ {size_t src_stride; size_t dest_stride; size_t x_len; int y_len; int /*<<< orphan*/  dest_addr; int /*<<< orphan*/  src_addr; } ;

/* Variables and functions */
 unsigned long DMA_CYCLIC ; 
 struct axi_dmac_desc* axi_dmac_alloc_desc (int) ; 
 int /*<<< orphan*/  axi_dmac_check_addr (struct axi_dmac_chan*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  axi_dmac_check_len (struct axi_dmac_chan*,int) ; 
 scalar_t__ axi_dmac_dest_is_mem (struct axi_dmac_chan*) ; 
 scalar_t__ axi_dmac_src_is_mem (struct axi_dmac_chan*) ; 
 size_t dmaengine_get_dst_icg (struct dma_interleaved_template*,TYPE_2__*) ; 
 size_t dmaengine_get_src_icg (struct dma_interleaved_template*,TYPE_2__*) ; 
 struct axi_dmac_chan* to_axi_dmac_chan (struct dma_chan*) ; 
 struct dma_async_tx_descriptor* vchan_tx_prep (int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static struct dma_async_tx_descriptor *axi_dmac_prep_interleaved(
	struct dma_chan *c, struct dma_interleaved_template *xt,
	unsigned long flags)
{
	struct axi_dmac_chan *chan = to_axi_dmac_chan(c);
	struct axi_dmac_desc *desc;
	size_t dst_icg, src_icg;

	if (xt->frame_size != 1)
		return NULL;

	if (xt->dir != chan->direction)
		return NULL;

	if (axi_dmac_src_is_mem(chan)) {
		if (!xt->src_inc || !axi_dmac_check_addr(chan, xt->src_start))
			return NULL;
	}

	if (axi_dmac_dest_is_mem(chan)) {
		if (!xt->dst_inc || !axi_dmac_check_addr(chan, xt->dst_start))
			return NULL;
	}

	dst_icg = dmaengine_get_dst_icg(xt, &xt->sgl[0]);
	src_icg = dmaengine_get_src_icg(xt, &xt->sgl[0]);

	if (chan->hw_2d) {
		if (!axi_dmac_check_len(chan, xt->sgl[0].size) ||
		    xt->numf == 0)
			return NULL;
		if (xt->sgl[0].size + dst_icg > chan->max_length ||
		    xt->sgl[0].size + src_icg > chan->max_length)
			return NULL;
	} else {
		if (dst_icg != 0 || src_icg != 0)
			return NULL;
		if (chan->max_length / xt->sgl[0].size < xt->numf)
			return NULL;
		if (!axi_dmac_check_len(chan, xt->sgl[0].size * xt->numf))
			return NULL;
	}

	desc = axi_dmac_alloc_desc(1);
	if (!desc)
		return NULL;

	if (axi_dmac_src_is_mem(chan)) {
		desc->sg[0].src_addr = xt->src_start;
		desc->sg[0].src_stride = xt->sgl[0].size + src_icg;
	}

	if (axi_dmac_dest_is_mem(chan)) {
		desc->sg[0].dest_addr = xt->dst_start;
		desc->sg[0].dest_stride = xt->sgl[0].size + dst_icg;
	}

	if (chan->hw_2d) {
		desc->sg[0].x_len = xt->sgl[0].size;
		desc->sg[0].y_len = xt->numf;
	} else {
		desc->sg[0].x_len = xt->sgl[0].size * xt->numf;
		desc->sg[0].y_len = 1;
	}

	if (flags & DMA_CYCLIC)
		desc->cyclic = true;

	return vchan_tx_prep(&chan->vchan, &desc->vdesc, flags);
}