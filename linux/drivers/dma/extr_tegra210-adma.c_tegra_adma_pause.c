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
struct tegra_adma_chan_regs {int ctrl; } ;
struct tegra_adma_desc {struct tegra_adma_chan_regs ch_regs; } ;
struct tegra_adma_chan {struct tegra_adma_desc* desc; } ;
struct dma_chan {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADMA_CH_CTRL ; 
 int ADMA_CH_CTRL_XFER_PAUSE_SHIFT ; 
 int EBUSY ; 
 int /*<<< orphan*/  TEGRA_ADMA_BURST_COMPLETE_TIME ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  tdc2dev (struct tegra_adma_chan*) ; 
 int tdma_ch_read (struct tegra_adma_chan*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tdma_ch_write (struct tegra_adma_chan*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  tegra_adma_is_paused (struct tegra_adma_chan*) ; 
 struct tegra_adma_chan* to_tegra_adma_chan (struct dma_chan*) ; 
 int /*<<< orphan*/  udelay (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int tegra_adma_pause(struct dma_chan *dc)
{
	struct tegra_adma_chan *tdc = to_tegra_adma_chan(dc);
	struct tegra_adma_desc *desc = tdc->desc;
	struct tegra_adma_chan_regs *ch_regs = &desc->ch_regs;
	int dcnt = 10;

	ch_regs->ctrl = tdma_ch_read(tdc, ADMA_CH_CTRL);
	ch_regs->ctrl |= (1 << ADMA_CH_CTRL_XFER_PAUSE_SHIFT);
	tdma_ch_write(tdc, ADMA_CH_CTRL, ch_regs->ctrl);

	while (dcnt-- && !tegra_adma_is_paused(tdc))
		udelay(TEGRA_ADMA_BURST_COMPLETE_TIME);

	if (dcnt < 0) {
		dev_err(tdc2dev(tdc), "unable to pause DMA channel\n");
		return -EBUSY;
	}

	return 0;
}