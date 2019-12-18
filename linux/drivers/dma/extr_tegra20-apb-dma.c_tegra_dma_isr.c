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
struct tegra_dma_channel {int /*<<< orphan*/  lock; int /*<<< orphan*/  tasklet; int /*<<< orphan*/  (* isr_handler ) (struct tegra_dma_channel*,int) ;int /*<<< orphan*/  dma_chan; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int /*<<< orphan*/  TEGRA_APBDMA_CHAN_STATUS ; 
 unsigned long TEGRA_APBDMA_STATUS_ISE_EOC ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*,unsigned long) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stub1 (struct tegra_dma_channel*,int) ; 
 int /*<<< orphan*/  tasklet_schedule (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tdc2dev (struct tegra_dma_channel*) ; 
 unsigned long tdc_read (struct tegra_dma_channel*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tdc_write (struct tegra_dma_channel*,int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  trace_tegra_dma_isr (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static irqreturn_t tegra_dma_isr(int irq, void *dev_id)
{
	struct tegra_dma_channel *tdc = dev_id;
	unsigned long status;
	unsigned long flags;

	spin_lock_irqsave(&tdc->lock, flags);

	trace_tegra_dma_isr(&tdc->dma_chan, irq);
	status = tdc_read(tdc, TEGRA_APBDMA_CHAN_STATUS);
	if (status & TEGRA_APBDMA_STATUS_ISE_EOC) {
		tdc_write(tdc, TEGRA_APBDMA_CHAN_STATUS, status);
		tdc->isr_handler(tdc, false);
		tasklet_schedule(&tdc->tasklet);
		spin_unlock_irqrestore(&tdc->lock, flags);
		return IRQ_HANDLED;
	}

	spin_unlock_irqrestore(&tdc->lock, flags);
	dev_info(tdc2dev(tdc),
		"Interrupt already served status 0x%08lx\n", status);
	return IRQ_NONE;
}