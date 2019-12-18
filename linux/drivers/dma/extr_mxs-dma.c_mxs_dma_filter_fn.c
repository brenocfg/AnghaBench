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
struct mxs_dma_filter_param {scalar_t__ chan_id; } ;
struct mxs_dma_engine {int /*<<< orphan*/  pdev; } ;
struct mxs_dma_chan {int chan_irq; struct mxs_dma_engine* mxs_dma; } ;
struct dma_chan {scalar_t__ chan_id; } ;

/* Variables and functions */
 int platform_get_irq (int /*<<< orphan*/ ,scalar_t__) ; 
 struct mxs_dma_chan* to_mxs_dma_chan (struct dma_chan*) ; 

__attribute__((used)) static bool mxs_dma_filter_fn(struct dma_chan *chan, void *fn_param)
{
	struct mxs_dma_filter_param *param = fn_param;
	struct mxs_dma_chan *mxs_chan = to_mxs_dma_chan(chan);
	struct mxs_dma_engine *mxs_dma = mxs_chan->mxs_dma;
	int chan_irq;

	if (chan->chan_id != param->chan_id)
		return false;

	chan_irq = platform_get_irq(mxs_dma->pdev, param->chan_id);
	if (chan_irq < 0)
		return false;

	mxs_chan->chan_irq = chan_irq;

	return true;
}