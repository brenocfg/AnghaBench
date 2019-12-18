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
struct zynqmp_dma_chan {int /*<<< orphan*/  dev; int /*<<< orphan*/  sw_desc_pool; int /*<<< orphan*/  desc_pool_p; int /*<<< orphan*/  desc_pool_v; int /*<<< orphan*/  lock; } ;
struct dma_chan {int dummy; } ;

/* Variables and functions */
 int ZYNQMP_DMA_DESC_SIZE (struct zynqmp_dma_chan*) ; 
 int ZYNQMP_DMA_NUM_DESCS ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_mark_last_busy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_put_autosuspend (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct zynqmp_dma_chan* to_chan (struct dma_chan*) ; 
 int /*<<< orphan*/  zynqmp_dma_free_descriptors (struct zynqmp_dma_chan*) ; 

__attribute__((used)) static void zynqmp_dma_free_chan_resources(struct dma_chan *dchan)
{
	struct zynqmp_dma_chan *chan = to_chan(dchan);
	unsigned long irqflags;

	spin_lock_irqsave(&chan->lock, irqflags);
	zynqmp_dma_free_descriptors(chan);
	spin_unlock_irqrestore(&chan->lock, irqflags);
	dma_free_coherent(chan->dev,
		(2 * ZYNQMP_DMA_DESC_SIZE(chan) * ZYNQMP_DMA_NUM_DESCS),
		chan->desc_pool_v, chan->desc_pool_p);
	kfree(chan->sw_desc_pool);
	pm_runtime_mark_last_busy(chan->dev);
	pm_runtime_put_autosuspend(chan->dev);
}