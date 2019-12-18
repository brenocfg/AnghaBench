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
struct TYPE_3__ {int /*<<< orphan*/  device_node; struct dma_device* device; } ;
struct xgene_dma_chan {TYPE_1__ dma_chan; int /*<<< orphan*/  tasklet; int /*<<< orphan*/ * desc_pool; scalar_t__ pending; int /*<<< orphan*/  ld_completed; int /*<<< orphan*/  ld_running; int /*<<< orphan*/  ld_pending; int /*<<< orphan*/  lock; } ;
struct xgene_dma {int /*<<< orphan*/  dev; struct dma_device* dma_dev; struct xgene_dma_chan* chan; } ;
struct dma_device {int /*<<< orphan*/  cap_mask; int /*<<< orphan*/  channels; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_PQ ; 
 int /*<<< orphan*/  DMA_XOR ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  chan_err (struct xgene_dma_chan*,char*,int) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,char*,char*) ; 
 int dma_async_device_register (struct dma_device*) ; 
 int /*<<< orphan*/  dma_chan_name (TYPE_1__*) ; 
 int /*<<< orphan*/  dma_cookie_init (TYPE_1__*) ; 
 scalar_t__ dma_has_cap (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tasklet_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  tasklet_kill (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xgene_dma_set_caps (struct xgene_dma_chan*,struct dma_device*) ; 
 int /*<<< orphan*/  xgene_dma_tasklet_cb ; 

__attribute__((used)) static int xgene_dma_async_register(struct xgene_dma *pdma, int id)
{
	struct xgene_dma_chan *chan = &pdma->chan[id];
	struct dma_device *dma_dev = &pdma->dma_dev[id];
	int ret;

	chan->dma_chan.device = dma_dev;

	spin_lock_init(&chan->lock);
	INIT_LIST_HEAD(&chan->ld_pending);
	INIT_LIST_HEAD(&chan->ld_running);
	INIT_LIST_HEAD(&chan->ld_completed);
	tasklet_init(&chan->tasklet, xgene_dma_tasklet_cb,
		     (unsigned long)chan);

	chan->pending = 0;
	chan->desc_pool = NULL;
	dma_cookie_init(&chan->dma_chan);

	/* Setup dma device capabilities and prep routines */
	xgene_dma_set_caps(chan, dma_dev);

	/* Initialize DMA device list head */
	INIT_LIST_HEAD(&dma_dev->channels);
	list_add_tail(&chan->dma_chan.device_node, &dma_dev->channels);

	/* Register with Linux async DMA framework*/
	ret = dma_async_device_register(dma_dev);
	if (ret) {
		chan_err(chan, "Failed to register async device %d", ret);
		tasklet_kill(&chan->tasklet);

		return ret;
	}

	/* DMA capability info */
	dev_info(pdma->dev,
		 "%s: CAPABILITY ( %s%s)\n", dma_chan_name(&chan->dma_chan),
		 dma_has_cap(DMA_XOR, dma_dev->cap_mask) ? "XOR " : "",
		 dma_has_cap(DMA_PQ, dma_dev->cap_mask) ? "PQ " : "");

	return 0;
}