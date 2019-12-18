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
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;
struct mxs_dma_engine {TYPE_1__ dma_device; int /*<<< orphan*/  clk; } ;
struct TYPE_5__ {int /*<<< orphan*/  tx_submit; } ;
struct mxs_dma_chan {int /*<<< orphan*/  ccw_phys; int /*<<< orphan*/  ccw; int /*<<< orphan*/  chan_irq; TYPE_2__ desc; struct mxs_dma_engine* mxs_dma; } ;
struct dma_chan {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CCW_BLOCK_SIZE ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  async_tx_ack (TYPE_2__*) ; 
 int clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_alloc_coherent (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_async_tx_descriptor_init (TYPE_2__*,struct dma_chan*) ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct mxs_dma_engine*) ; 
 int /*<<< orphan*/  mxs_dma_int_handler ; 
 int /*<<< orphan*/  mxs_dma_reset_chan (struct dma_chan*) ; 
 int /*<<< orphan*/  mxs_dma_tx_submit ; 
 int request_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,struct mxs_dma_engine*) ; 
 struct mxs_dma_chan* to_mxs_dma_chan (struct dma_chan*) ; 

__attribute__((used)) static int mxs_dma_alloc_chan_resources(struct dma_chan *chan)
{
	struct mxs_dma_chan *mxs_chan = to_mxs_dma_chan(chan);
	struct mxs_dma_engine *mxs_dma = mxs_chan->mxs_dma;
	int ret;

	mxs_chan->ccw = dma_alloc_coherent(mxs_dma->dma_device.dev,
					   CCW_BLOCK_SIZE,
					   &mxs_chan->ccw_phys, GFP_KERNEL);
	if (!mxs_chan->ccw) {
		ret = -ENOMEM;
		goto err_alloc;
	}

	ret = request_irq(mxs_chan->chan_irq, mxs_dma_int_handler,
			  0, "mxs-dma", mxs_dma);
	if (ret)
		goto err_irq;

	ret = clk_prepare_enable(mxs_dma->clk);
	if (ret)
		goto err_clk;

	mxs_dma_reset_chan(chan);

	dma_async_tx_descriptor_init(&mxs_chan->desc, chan);
	mxs_chan->desc.tx_submit = mxs_dma_tx_submit;

	/* the descriptor is ready */
	async_tx_ack(&mxs_chan->desc);

	return 0;

err_clk:
	free_irq(mxs_chan->chan_irq, mxs_dma);
err_irq:
	dma_free_coherent(mxs_dma->dma_device.dev, CCW_BLOCK_SIZE,
			mxs_chan->ccw, mxs_chan->ccw_phys);
err_alloc:
	return ret;
}