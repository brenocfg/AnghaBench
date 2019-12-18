#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int apb_ptr; int ahb_ptr; int wcount; int csr; } ;
struct tegra_dma_sg_req {int configured; scalar_t__ words_xferred; TYPE_3__ ch_regs; } ;
struct tegra_dma_channel {TYPE_2__* tdma; } ;
struct TYPE_5__ {TYPE_1__* chip_data; } ;
struct TYPE_4__ {scalar_t__ support_separate_wcount_reg; } ;

/* Variables and functions */
 int /*<<< orphan*/  TEGRA_APBDMA_CHAN_AHBPTR ; 
 int /*<<< orphan*/  TEGRA_APBDMA_CHAN_APBPTR ; 
 int /*<<< orphan*/  TEGRA_APBDMA_CHAN_CSR ; 
 int /*<<< orphan*/  TEGRA_APBDMA_CHAN_STATUS ; 
 int /*<<< orphan*/  TEGRA_APBDMA_CHAN_WCOUNT ; 
 int TEGRA_APBDMA_CSR_ENB ; 
 unsigned long TEGRA_APBDMA_STATUS_ISE_EOC ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  tdc2dev (struct tegra_dma_channel*) ; 
 unsigned long tdc_read (struct tegra_dma_channel*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tdc_write (struct tegra_dma_channel*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  tegra_dma_pause (struct tegra_dma_channel*,int) ; 
 int /*<<< orphan*/  tegra_dma_resume (struct tegra_dma_channel*) ; 

__attribute__((used)) static void tegra_dma_configure_for_next(struct tegra_dma_channel *tdc,
		struct tegra_dma_sg_req *nsg_req)
{
	unsigned long status;

	/*
	 * The DMA controller reloads the new configuration for next transfer
	 * after last burst of current transfer completes.
	 * If there is no IEC status then this makes sure that last burst
	 * has not be completed. There may be case that last burst is on
	 * flight and so it can complete but because DMA is paused, it
	 * will not generates interrupt as well as not reload the new
	 * configuration.
	 * If there is already IEC status then interrupt handler need to
	 * load new configuration.
	 */
	tegra_dma_pause(tdc, false);
	status = tdc_read(tdc, TEGRA_APBDMA_CHAN_STATUS);

	/*
	 * If interrupt is pending then do nothing as the ISR will handle
	 * the programing for new request.
	 */
	if (status & TEGRA_APBDMA_STATUS_ISE_EOC) {
		dev_err(tdc2dev(tdc),
			"Skipping new configuration as interrupt is pending\n");
		tegra_dma_resume(tdc);
		return;
	}

	/* Safe to program new configuration */
	tdc_write(tdc, TEGRA_APBDMA_CHAN_APBPTR, nsg_req->ch_regs.apb_ptr);
	tdc_write(tdc, TEGRA_APBDMA_CHAN_AHBPTR, nsg_req->ch_regs.ahb_ptr);
	if (tdc->tdma->chip_data->support_separate_wcount_reg)
		tdc_write(tdc, TEGRA_APBDMA_CHAN_WCOUNT,
						nsg_req->ch_regs.wcount);
	tdc_write(tdc, TEGRA_APBDMA_CHAN_CSR,
				nsg_req->ch_regs.csr | TEGRA_APBDMA_CSR_ENB);
	nsg_req->configured = true;
	nsg_req->words_xferred = 0;

	tegra_dma_resume(tdc);
}