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
struct stm32_dmamux_data {int /*<<< orphan*/  lock; int /*<<< orphan*/  dma_inuse; int /*<<< orphan*/  iomem; } ;
struct stm32_dmamux {int /*<<< orphan*/  chan_id; int /*<<< orphan*/  master; int /*<<< orphan*/  request; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  STM32_DMAMUX_CCR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct stm32_dmamux_data* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  kfree (struct stm32_dmamux*) ; 
 int /*<<< orphan*/  pm_runtime_put_sync (struct device*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stm32_dmamux_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void stm32_dmamux_free(struct device *dev, void *route_data)
{
	struct stm32_dmamux_data *dmamux = dev_get_drvdata(dev);
	struct stm32_dmamux *mux = route_data;
	unsigned long flags;

	/* Clear dma request */
	spin_lock_irqsave(&dmamux->lock, flags);

	stm32_dmamux_write(dmamux->iomem, STM32_DMAMUX_CCR(mux->chan_id), 0);
	clear_bit(mux->chan_id, dmamux->dma_inuse);

	pm_runtime_put_sync(dev);

	spin_unlock_irqrestore(&dmamux->lock, flags);

	dev_dbg(dev, "Unmapping DMAMUX(%u) to DMA%u(%u)\n",
		mux->request, mux->master, mux->chan_id);

	kfree(mux);
}