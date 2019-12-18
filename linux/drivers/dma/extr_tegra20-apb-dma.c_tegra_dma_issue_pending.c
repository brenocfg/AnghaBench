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
struct tegra_dma_channel {int /*<<< orphan*/  lock; scalar_t__ cyclic; int /*<<< orphan*/  busy; int /*<<< orphan*/  pending_sg_req; } ;
struct dma_chan {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  TEGRA_APBDMA_BURST_COMPLETE_TIME ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  tdc2dev (struct tegra_dma_channel*) ; 
 int /*<<< orphan*/  tdc_configure_next_head_desc (struct tegra_dma_channel*) ; 
 int /*<<< orphan*/  tdc_start_head_req (struct tegra_dma_channel*) ; 
 struct tegra_dma_channel* to_tegra_dma_chan (struct dma_chan*) ; 
 int /*<<< orphan*/  udelay (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void tegra_dma_issue_pending(struct dma_chan *dc)
{
	struct tegra_dma_channel *tdc = to_tegra_dma_chan(dc);
	unsigned long flags;

	spin_lock_irqsave(&tdc->lock, flags);
	if (list_empty(&tdc->pending_sg_req)) {
		dev_err(tdc2dev(tdc), "No DMA request\n");
		goto end;
	}
	if (!tdc->busy) {
		tdc_start_head_req(tdc);

		/* Continuous single mode: Configure next req */
		if (tdc->cyclic) {
			/*
			 * Wait for 1 burst time for configure DMA for
			 * next transfer.
			 */
			udelay(TEGRA_APBDMA_BURST_COMPLETE_TIME);
			tdc_configure_next_head_desc(tdc);
		}
	}
end:
	spin_unlock_irqrestore(&tdc->lock, flags);
}