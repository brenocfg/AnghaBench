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
struct mmp_tdma_desc {size_t src_addr; size_t dst_addr; size_t byte_cnt; scalar_t__ nxt_desc; } ;
struct dma_async_tx_descriptor {int dummy; } ;
struct mmp_tdma_chan {scalar_t__ status; int desc_num; size_t dev_addr; size_t buf_len; size_t period_len; struct dma_async_tx_descriptor desc; scalar_t__ pos; scalar_t__ desc_arr_phys; struct mmp_tdma_desc* desc_arr; int /*<<< orphan*/  slave_config; int /*<<< orphan*/  dev; } ;
struct dma_chan {int dummy; } ;
typedef  enum dma_transfer_direction { ____Placeholder_dma_transfer_direction } dma_transfer_direction ;
typedef  size_t dma_addr_t ;

/* Variables and functions */
 scalar_t__ DMA_COMPLETE ; 
 scalar_t__ DMA_ERROR ; 
 scalar_t__ DMA_IN_PROGRESS ; 
 int DMA_MEM_TO_DEV ; 
 unsigned long DMA_PREP_INTERRUPT ; 
 size_t TDMA_MAX_XFER_BYTES ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,size_t,size_t) ; 
 struct mmp_tdma_desc* mmp_tdma_alloc_descriptor (struct mmp_tdma_chan*) ; 
 int /*<<< orphan*/  mmp_tdma_config_write (struct dma_chan*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mmp_tdma_enable_irq (struct mmp_tdma_chan*,int) ; 
 struct mmp_tdma_chan* to_mmp_tdma_chan (struct dma_chan*) ; 

__attribute__((used)) static struct dma_async_tx_descriptor *mmp_tdma_prep_dma_cyclic(
		struct dma_chan *chan, dma_addr_t dma_addr, size_t buf_len,
		size_t period_len, enum dma_transfer_direction direction,
		unsigned long flags)
{
	struct mmp_tdma_chan *tdmac = to_mmp_tdma_chan(chan);
	struct mmp_tdma_desc *desc;
	int num_periods = buf_len / period_len;
	int i = 0, buf = 0;

	if (tdmac->status != DMA_COMPLETE)
		return NULL;

	if (period_len > TDMA_MAX_XFER_BYTES) {
		dev_err(tdmac->dev,
				"maximum period size exceeded: %zu > %d\n",
				period_len, TDMA_MAX_XFER_BYTES);
		goto err_out;
	}

	tdmac->status = DMA_IN_PROGRESS;
	tdmac->desc_num = num_periods;
	desc = mmp_tdma_alloc_descriptor(tdmac);
	if (!desc)
		goto err_out;

	mmp_tdma_config_write(chan, direction, &tdmac->slave_config);

	while (buf < buf_len) {
		desc = &tdmac->desc_arr[i];

		if (i + 1 == num_periods)
			desc->nxt_desc = tdmac->desc_arr_phys;
		else
			desc->nxt_desc = tdmac->desc_arr_phys +
				sizeof(*desc) * (i + 1);

		if (direction == DMA_MEM_TO_DEV) {
			desc->src_addr = dma_addr;
			desc->dst_addr = tdmac->dev_addr;
		} else {
			desc->src_addr = tdmac->dev_addr;
			desc->dst_addr = dma_addr;
		}
		desc->byte_cnt = period_len;
		dma_addr += period_len;
		buf += period_len;
		i++;
	}

	/* enable interrupt */
	if (flags & DMA_PREP_INTERRUPT)
		mmp_tdma_enable_irq(tdmac, true);

	tdmac->buf_len = buf_len;
	tdmac->period_len = period_len;
	tdmac->pos = 0;

	return &tdmac->desc;

err_out:
	tdmac->status = DMA_ERROR;
	return NULL;
}