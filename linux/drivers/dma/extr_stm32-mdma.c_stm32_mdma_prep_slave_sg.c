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
typedef  int /*<<< orphan*/  u32 ;
struct stm32_mdma_desc {int cyclic; int count; TYPE_2__* node; int /*<<< orphan*/  vdesc; } ;
struct stm32_mdma_chan {int /*<<< orphan*/  desc_pool; int /*<<< orphan*/  vchan; TYPE_1__* desc; } ;
struct scatterlist {int dummy; } ;
struct dma_chan {int dummy; } ;
struct dma_async_tx_descriptor {int dummy; } ;
typedef  enum dma_transfer_direction { ____Placeholder_dma_transfer_direction } dma_transfer_direction ;
struct TYPE_4__ {int /*<<< orphan*/  hwdesc_phys; int /*<<< orphan*/  hwdesc; } ;
struct TYPE_3__ {scalar_t__ cyclic; } ;

/* Variables and functions */
 int /*<<< orphan*/  chan2dev (struct stm32_mdma_chan*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dma_pool_free (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct stm32_mdma_desc*) ; 
 struct stm32_mdma_desc* stm32_mdma_alloc_desc (struct stm32_mdma_chan*,int /*<<< orphan*/ ) ; 
 int stm32_mdma_setup_xfer (struct stm32_mdma_chan*,struct stm32_mdma_desc*,struct scatterlist*,int /*<<< orphan*/ ,int) ; 
 struct stm32_mdma_chan* to_stm32_mdma_chan (struct dma_chan*) ; 
 struct dma_async_tx_descriptor* vchan_tx_prep (int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static struct dma_async_tx_descriptor *
stm32_mdma_prep_slave_sg(struct dma_chan *c, struct scatterlist *sgl,
			 u32 sg_len, enum dma_transfer_direction direction,
			 unsigned long flags, void *context)
{
	struct stm32_mdma_chan *chan = to_stm32_mdma_chan(c);
	struct stm32_mdma_desc *desc;
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

	desc = stm32_mdma_alloc_desc(chan, sg_len);
	if (!desc)
		return NULL;

	ret = stm32_mdma_setup_xfer(chan, desc, sgl, sg_len, direction);
	if (ret < 0)
		goto xfer_setup_err;

	desc->cyclic = false;

	return vchan_tx_prep(&chan->vchan, &desc->vdesc, flags);

xfer_setup_err:
	for (i = 0; i < desc->count; i++)
		dma_pool_free(chan->desc_pool, desc->node[i].hwdesc,
			      desc->node[i].hwdesc_phys);
	kfree(desc);
	return NULL;
}