#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct stm32_dma_desc {int num_sgs; int cyclic; int /*<<< orphan*/  vdesc; TYPE_2__* sg_req; } ;
struct TYPE_4__ {int /*<<< orphan*/  dma_spar; int /*<<< orphan*/  dma_sfcr; int /*<<< orphan*/  dma_scr; } ;
struct stm32_dma_chan {int /*<<< orphan*/  vchan; TYPE_1__ chan_reg; scalar_t__ busy; int /*<<< orphan*/  config_init; } ;
struct dma_chan {int dummy; } ;
struct dma_async_tx_descriptor {int dummy; } ;
typedef  enum dma_transfer_direction { ____Placeholder_dma_transfer_direction } dma_transfer_direction ;
typedef  enum dma_slave_buswidth { ____Placeholder_dma_slave_buswidth } dma_slave_buswidth ;
typedef  size_t dma_addr_t ;
struct TYPE_6__ {size_t dma_sm0ar; size_t dma_sm1ar; int dma_sndtr; int /*<<< orphan*/  dma_spar; int /*<<< orphan*/  dma_sfcr; int /*<<< orphan*/  dma_scr; } ;
struct TYPE_5__ {size_t len; TYPE_3__ chan_reg; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_NOWAIT ; 
 int STM32_DMA_ALIGNED_MAX_DATA_ITEMS ; 
 int /*<<< orphan*/  STM32_DMA_SCR_CIRC ; 
 int /*<<< orphan*/  STM32_DMA_SCR_DBM ; 
 int /*<<< orphan*/  STM32_DMA_SCR_PFCTRL ; 
 int /*<<< orphan*/  chan2dev (struct stm32_dma_chan*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 struct stm32_dma_desc* kzalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sg_req ; 
 int /*<<< orphan*/  stm32_dma_clear_reg (TYPE_3__*) ; 
 int stm32_dma_set_xfer_param (struct stm32_dma_chan*,int,int*,size_t) ; 
 int /*<<< orphan*/  struct_size (struct stm32_dma_desc*,int /*<<< orphan*/ ,int) ; 
 struct stm32_dma_chan* to_stm32_dma_chan (struct dma_chan*) ; 
 struct dma_async_tx_descriptor* vchan_tx_prep (int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static struct dma_async_tx_descriptor *stm32_dma_prep_dma_cyclic(
	struct dma_chan *c, dma_addr_t buf_addr, size_t buf_len,
	size_t period_len, enum dma_transfer_direction direction,
	unsigned long flags)
{
	struct stm32_dma_chan *chan = to_stm32_dma_chan(c);
	struct stm32_dma_desc *desc;
	enum dma_slave_buswidth buswidth;
	u32 num_periods, nb_data_items;
	int i, ret;

	if (!buf_len || !period_len) {
		dev_err(chan2dev(chan), "Invalid buffer/period len\n");
		return NULL;
	}

	if (!chan->config_init) {
		dev_err(chan2dev(chan), "dma channel is not configured\n");
		return NULL;
	}

	if (buf_len % period_len) {
		dev_err(chan2dev(chan), "buf_len not multiple of period_len\n");
		return NULL;
	}

	/*
	 * We allow to take more number of requests till DMA is
	 * not started. The driver will loop over all requests.
	 * Once DMA is started then new requests can be queued only after
	 * terminating the DMA.
	 */
	if (chan->busy) {
		dev_err(chan2dev(chan), "Request not allowed when dma busy\n");
		return NULL;
	}

	ret = stm32_dma_set_xfer_param(chan, direction, &buswidth, period_len);
	if (ret < 0)
		return NULL;

	nb_data_items = period_len / buswidth;
	if (nb_data_items > STM32_DMA_ALIGNED_MAX_DATA_ITEMS) {
		dev_err(chan2dev(chan), "number of items not supported\n");
		return NULL;
	}

	/*  Enable Circular mode or double buffer mode */
	if (buf_len == period_len)
		chan->chan_reg.dma_scr |= STM32_DMA_SCR_CIRC;
	else
		chan->chan_reg.dma_scr |= STM32_DMA_SCR_DBM;

	/* Clear periph ctrl if client set it */
	chan->chan_reg.dma_scr &= ~STM32_DMA_SCR_PFCTRL;

	num_periods = buf_len / period_len;

	desc = kzalloc(struct_size(desc, sg_req, num_periods), GFP_NOWAIT);
	if (!desc)
		return NULL;

	for (i = 0; i < num_periods; i++) {
		desc->sg_req[i].len = period_len;

		stm32_dma_clear_reg(&desc->sg_req[i].chan_reg);
		desc->sg_req[i].chan_reg.dma_scr = chan->chan_reg.dma_scr;
		desc->sg_req[i].chan_reg.dma_sfcr = chan->chan_reg.dma_sfcr;
		desc->sg_req[i].chan_reg.dma_spar = chan->chan_reg.dma_spar;
		desc->sg_req[i].chan_reg.dma_sm0ar = buf_addr;
		desc->sg_req[i].chan_reg.dma_sm1ar = buf_addr;
		desc->sg_req[i].chan_reg.dma_sndtr = nb_data_items;
		buf_addr += period_len;
	}

	desc->num_sgs = num_periods;
	desc->cyclic = true;

	return vchan_tx_prep(&chan->vchan, &desc->vdesc, flags);
}