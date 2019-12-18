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
typedef  int u32 ;
struct stm32_mdma_device {int dummy; } ;
struct stm32_mdma_desc {int ccr; int cyclic; int count; TYPE_2__* node; int /*<<< orphan*/  vdesc; } ;
struct dma_slave_config {scalar_t__ src_addr; scalar_t__ dst_addr; } ;
struct stm32_mdma_chan {int /*<<< orphan*/  desc_pool; int /*<<< orphan*/  vchan; TYPE_1__* desc; struct dma_slave_config dma_config; } ;
struct dma_chan {int dummy; } ;
struct dma_async_tx_descriptor {int dummy; } ;
typedef  enum dma_transfer_direction { ____Placeholder_dma_transfer_direction } dma_transfer_direction ;
typedef  scalar_t__ dma_addr_t ;
struct TYPE_4__ {int /*<<< orphan*/  hwdesc_phys; int /*<<< orphan*/  hwdesc; } ;
struct TYPE_3__ {scalar_t__ cyclic; } ;

/* Variables and functions */
 int DMA_MEM_TO_DEV ; 
 int STM32_MDMA_CCR_BTIE ; 
 int STM32_MDMA_CCR_CTCIE ; 
 int STM32_MDMA_CCR_IRQ_MASK ; 
 int STM32_MDMA_CCR_TEIE ; 
 int /*<<< orphan*/  STM32_MDMA_CTBR_DBUS ; 
 int /*<<< orphan*/  STM32_MDMA_CTBR_SBUS ; 
 size_t STM32_MDMA_MAX_BLOCK_LEN ; 
 int /*<<< orphan*/  chan2dev (struct stm32_mdma_chan*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dma_pool_free (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct stm32_mdma_desc*) ; 
 struct stm32_mdma_desc* stm32_mdma_alloc_desc (struct stm32_mdma_chan*,int) ; 
 struct stm32_mdma_device* stm32_mdma_get_dev (struct stm32_mdma_chan*) ; 
 int /*<<< orphan*/  stm32_mdma_set_bus (struct stm32_mdma_device*,int*,int /*<<< orphan*/ ,scalar_t__) ; 
 int stm32_mdma_set_xfer_param (struct stm32_mdma_chan*,int,int*,int*,int*,scalar_t__,size_t) ; 
 int /*<<< orphan*/  stm32_mdma_setup_hwdesc (struct stm32_mdma_chan*,struct stm32_mdma_desc*,int,int,scalar_t__,scalar_t__,size_t,int,int,int,int,int) ; 
 struct stm32_mdma_chan* to_stm32_mdma_chan (struct dma_chan*) ; 
 struct dma_async_tx_descriptor* vchan_tx_prep (int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static struct dma_async_tx_descriptor *
stm32_mdma_prep_dma_cyclic(struct dma_chan *c, dma_addr_t buf_addr,
			   size_t buf_len, size_t period_len,
			   enum dma_transfer_direction direction,
			   unsigned long flags)
{
	struct stm32_mdma_chan *chan = to_stm32_mdma_chan(c);
	struct stm32_mdma_device *dmadev = stm32_mdma_get_dev(chan);
	struct dma_slave_config *dma_config = &chan->dma_config;
	struct stm32_mdma_desc *desc;
	dma_addr_t src_addr, dst_addr;
	u32 ccr, ctcr, ctbr, count;
	int i, ret;

	/*
	 * Once DMA is in setup cyclic mode the channel we cannot assign this
	 * channel anymore. The DMA channel needs to be aborted or terminated
	 * for allowing another request.
	 */
	if (chan->desc && chan->desc->cyclic) {
		dev_err(chan2dev(chan),
			"Request not allowed when dma in cyclic mode\n");
		return NULL;
	}

	if (!buf_len || !period_len || period_len > STM32_MDMA_MAX_BLOCK_LEN) {
		dev_err(chan2dev(chan), "Invalid buffer/period len\n");
		return NULL;
	}

	if (buf_len % period_len) {
		dev_err(chan2dev(chan), "buf_len not multiple of period_len\n");
		return NULL;
	}

	count = buf_len / period_len;

	desc = stm32_mdma_alloc_desc(chan, count);
	if (!desc)
		return NULL;

	/* Select bus */
	if (direction == DMA_MEM_TO_DEV) {
		src_addr = buf_addr;
		ret = stm32_mdma_set_xfer_param(chan, direction, &ccr, &ctcr,
						&ctbr, src_addr, period_len);
		stm32_mdma_set_bus(dmadev, &ctbr, STM32_MDMA_CTBR_SBUS,
				   src_addr);
	} else {
		dst_addr = buf_addr;
		ret = stm32_mdma_set_xfer_param(chan, direction, &ccr, &ctcr,
						&ctbr, dst_addr, period_len);
		stm32_mdma_set_bus(dmadev, &ctbr, STM32_MDMA_CTBR_DBUS,
				   dst_addr);
	}

	if (ret < 0)
		goto xfer_setup_err;

	/* Enable interrupts */
	ccr &= ~STM32_MDMA_CCR_IRQ_MASK;
	ccr |= STM32_MDMA_CCR_TEIE | STM32_MDMA_CCR_CTCIE | STM32_MDMA_CCR_BTIE;
	desc->ccr = ccr;

	/* Configure hwdesc list */
	for (i = 0; i < count; i++) {
		if (direction == DMA_MEM_TO_DEV) {
			src_addr = buf_addr + i * period_len;
			dst_addr = dma_config->dst_addr;
		} else {
			src_addr = dma_config->src_addr;
			dst_addr = buf_addr + i * period_len;
		}

		stm32_mdma_setup_hwdesc(chan, desc, direction, i, src_addr,
					dst_addr, period_len, ctcr, ctbr,
					i == count - 1, i == 0, true);
	}

	desc->cyclic = true;

	return vchan_tx_prep(&chan->vchan, &desc->vdesc, flags);

xfer_setup_err:
	for (i = 0; i < desc->count; i++)
		dma_pool_free(chan->desc_pool, desc->node[i].hwdesc,
			      desc->node[i].hwdesc_phys);
	kfree(desc);
	return NULL;
}