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
struct xgene_dma_chan {int /*<<< orphan*/ * desc_pool; int /*<<< orphan*/  lock; int /*<<< orphan*/  ld_completed; int /*<<< orphan*/  ld_running; int /*<<< orphan*/  ld_pending; } ;
struct dma_chan {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  chan_dbg (struct xgene_dma_chan*,char*) ; 
 int /*<<< orphan*/  dma_pool_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 struct xgene_dma_chan* to_dma_chan (struct dma_chan*) ; 
 int /*<<< orphan*/  xgene_dma_cleanup_descriptors (struct xgene_dma_chan*) ; 
 int /*<<< orphan*/  xgene_dma_free_desc_list (struct xgene_dma_chan*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void xgene_dma_free_chan_resources(struct dma_chan *dchan)
{
	struct xgene_dma_chan *chan = to_dma_chan(dchan);

	chan_dbg(chan, "Free all resources\n");

	if (!chan->desc_pool)
		return;

	/* Process all running descriptor */
	xgene_dma_cleanup_descriptors(chan);

	spin_lock_bh(&chan->lock);

	/* Clean all link descriptor queues */
	xgene_dma_free_desc_list(chan, &chan->ld_pending);
	xgene_dma_free_desc_list(chan, &chan->ld_running);
	xgene_dma_free_desc_list(chan, &chan->ld_completed);

	spin_unlock_bh(&chan->lock);

	/* Delete this channel DMA pool */
	dma_pool_destroy(chan->desc_pool);
	chan->desc_pool = NULL;
}