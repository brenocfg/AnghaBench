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
typedef  size_t u32 ;
typedef  size_t u16 ;
struct fsl_edma_desc {int iscyclic; int dirn; int /*<<< orphan*/  vdesc; TYPE_2__* tcd; } ;
struct TYPE_3__ {size_t dst_addr_width; size_t dst_maxburst; size_t src_addr_width; size_t src_maxburst; } ;
struct fsl_edma_chan {size_t dma_dev_addr; int /*<<< orphan*/  vchan; void* attr; TYPE_1__ cfg; } ;
struct dma_chan {int dummy; } ;
struct dma_async_tx_descriptor {int dummy; } ;
typedef  enum dma_transfer_direction { ____Placeholder_dma_transfer_direction } dma_transfer_direction ;
typedef  scalar_t__ dma_addr_t ;
struct TYPE_4__ {size_t ptcd; int /*<<< orphan*/  vtcd; } ;

/* Variables and functions */
 int DMA_MEM_TO_DEV ; 
 struct fsl_edma_desc* fsl_edma_alloc_desc (struct fsl_edma_chan*,int) ; 
 int /*<<< orphan*/  fsl_edma_fill_tcd (int /*<<< orphan*/ ,size_t,size_t,void*,size_t,size_t,int /*<<< orphan*/ ,size_t,size_t,size_t,size_t,int,int,int) ; 
 void* fsl_edma_get_tcd_attr (size_t) ; 
 int /*<<< orphan*/  fsl_edma_prep_slave_dma (struct fsl_edma_chan*,int) ; 
 int /*<<< orphan*/  is_slave_direction (int) ; 
 struct fsl_edma_chan* to_fsl_edma_chan (struct dma_chan*) ; 
 struct dma_async_tx_descriptor* vchan_tx_prep (int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned long) ; 

struct dma_async_tx_descriptor *fsl_edma_prep_dma_cyclic(
		struct dma_chan *chan, dma_addr_t dma_addr, size_t buf_len,
		size_t period_len, enum dma_transfer_direction direction,
		unsigned long flags)
{
	struct fsl_edma_chan *fsl_chan = to_fsl_edma_chan(chan);
	struct fsl_edma_desc *fsl_desc;
	dma_addr_t dma_buf_next;
	int sg_len, i;
	u32 src_addr, dst_addr, last_sg, nbytes;
	u16 soff, doff, iter;

	if (!is_slave_direction(direction))
		return NULL;

	if (!fsl_edma_prep_slave_dma(fsl_chan, direction))
		return NULL;

	sg_len = buf_len / period_len;
	fsl_desc = fsl_edma_alloc_desc(fsl_chan, sg_len);
	if (!fsl_desc)
		return NULL;
	fsl_desc->iscyclic = true;
	fsl_desc->dirn = direction;

	dma_buf_next = dma_addr;
	if (direction == DMA_MEM_TO_DEV) {
		fsl_chan->attr =
			fsl_edma_get_tcd_attr(fsl_chan->cfg.dst_addr_width);
		nbytes = fsl_chan->cfg.dst_addr_width *
			fsl_chan->cfg.dst_maxburst;
	} else {
		fsl_chan->attr =
			fsl_edma_get_tcd_attr(fsl_chan->cfg.src_addr_width);
		nbytes = fsl_chan->cfg.src_addr_width *
			fsl_chan->cfg.src_maxburst;
	}

	iter = period_len / nbytes;

	for (i = 0; i < sg_len; i++) {
		if (dma_buf_next >= dma_addr + buf_len)
			dma_buf_next = dma_addr;

		/* get next sg's physical address */
		last_sg = fsl_desc->tcd[(i + 1) % sg_len].ptcd;

		if (direction == DMA_MEM_TO_DEV) {
			src_addr = dma_buf_next;
			dst_addr = fsl_chan->dma_dev_addr;
			soff = fsl_chan->cfg.dst_addr_width;
			doff = 0;
		} else {
			src_addr = fsl_chan->dma_dev_addr;
			dst_addr = dma_buf_next;
			soff = 0;
			doff = fsl_chan->cfg.src_addr_width;
		}

		fsl_edma_fill_tcd(fsl_desc->tcd[i].vtcd, src_addr, dst_addr,
				  fsl_chan->attr, soff, nbytes, 0, iter,
				  iter, doff, last_sg, true, false, true);
		dma_buf_next += period_len;
	}

	return vchan_tx_prep(&fsl_chan->vchan, &fsl_desc->vdesc, flags);
}