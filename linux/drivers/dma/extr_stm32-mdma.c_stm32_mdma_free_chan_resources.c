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
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;
struct stm32_mdma_device {TYPE_2__ ddev; } ;
struct TYPE_3__ {int /*<<< orphan*/  lock; } ;
struct stm32_mdma_chan {int /*<<< orphan*/ * desc_pool; TYPE_1__ vchan; int /*<<< orphan*/ * desc; scalar_t__ busy; int /*<<< orphan*/  id; } ;
struct dma_chan {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  chan2dev (struct stm32_mdma_chan*) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dmam_pool_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct stm32_mdma_device* stm32_mdma_get_dev (struct stm32_mdma_chan*) ; 
 int /*<<< orphan*/  stm32_mdma_stop (struct stm32_mdma_chan*) ; 
 struct stm32_mdma_chan* to_stm32_mdma_chan (struct dma_chan*) ; 
 int /*<<< orphan*/  to_virt_chan (struct dma_chan*) ; 
 int /*<<< orphan*/  vchan_free_chan_resources (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void stm32_mdma_free_chan_resources(struct dma_chan *c)
{
	struct stm32_mdma_chan *chan = to_stm32_mdma_chan(c);
	struct stm32_mdma_device *dmadev = stm32_mdma_get_dev(chan);
	unsigned long flags;

	dev_dbg(chan2dev(chan), "Freeing channel %d\n", chan->id);

	if (chan->busy) {
		spin_lock_irqsave(&chan->vchan.lock, flags);
		stm32_mdma_stop(chan);
		chan->desc = NULL;
		spin_unlock_irqrestore(&chan->vchan.lock, flags);
	}

	pm_runtime_put(dmadev->ddev.dev);
	vchan_free_chan_resources(to_virt_chan(c));
	dmam_pool_destroy(chan->desc_pool);
	chan->desc_pool = NULL;
}