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
struct tegra_adma_chan {int /*<<< orphan*/ * desc; scalar_t__ chan_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADMA_CH_CMD ; 
 scalar_t__ ADMA_CH_STATUS ; 
 unsigned int ADMA_CH_STATUS_XFER_EN ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  readl ; 
 scalar_t__ readx_poll_timeout_atomic (int /*<<< orphan*/ ,scalar_t__,unsigned int,int,int,int) ; 
 int /*<<< orphan*/  tdc2dev (struct tegra_adma_chan*) ; 
 int /*<<< orphan*/  tdma_ch_write (struct tegra_adma_chan*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tegra_adma_irq_clear (struct tegra_adma_chan*) ; 

__attribute__((used)) static void tegra_adma_stop(struct tegra_adma_chan *tdc)
{
	unsigned int status;

	/* Disable ADMA */
	tdma_ch_write(tdc, ADMA_CH_CMD, 0);

	/* Clear interrupt status */
	tegra_adma_irq_clear(tdc);

	if (readx_poll_timeout_atomic(readl, tdc->chan_addr + ADMA_CH_STATUS,
			status, !(status & ADMA_CH_STATUS_XFER_EN),
			20, 10000)) {
		dev_err(tdc2dev(tdc), "unable to stop DMA channel\n");
		return;
	}

	kfree(tdc->desc);
	tdc->desc = NULL;
}