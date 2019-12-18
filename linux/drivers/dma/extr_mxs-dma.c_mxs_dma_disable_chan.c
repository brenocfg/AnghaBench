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
struct mxs_dma_chan {int /*<<< orphan*/  status; } ;
struct dma_chan {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_COMPLETE ; 
 struct mxs_dma_chan* to_mxs_dma_chan (struct dma_chan*) ; 

__attribute__((used)) static void mxs_dma_disable_chan(struct dma_chan *chan)
{
	struct mxs_dma_chan *mxs_chan = to_mxs_dma_chan(chan);

	mxs_chan->status = DMA_COMPLETE;
}