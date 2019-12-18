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

/* Variables and functions */
 int /*<<< orphan*/  DMA_ERRATA_3_3 ; 
 int /*<<< orphan*/  DMA_ERRATA_IFRAME_BUFFERING ; 
 int /*<<< orphan*/  DMA_ERRATA_PARALLEL_CHANNELS ; 
 int /*<<< orphan*/  DMA_ERRATA_i378 ; 
 int /*<<< orphan*/  DMA_ERRATA_i541 ; 
 int /*<<< orphan*/  DMA_ERRATA_i88 ; 
 int /*<<< orphan*/  DMA_ROMCODE_BUG ; 
 scalar_t__ OMAP2430_REV_ES1_0 ; 
 scalar_t__ OMAP2_DEVICE_TYPE_GP ; 
 scalar_t__ OMAP3430_REV_ES1_0 ; 
 int /*<<< orphan*/  SET_DMA_ERRATA (int /*<<< orphan*/ ) ; 
 scalar_t__ cpu_class_is_omap2 () ; 
 scalar_t__ cpu_is_omap2420 () ; 
 scalar_t__ cpu_is_omap2430 () ; 
 scalar_t__ cpu_is_omap34xx () ; 
 scalar_t__ omap_type () ; 

__attribute__((used)) static unsigned configure_dma_errata(void)
{
	unsigned errata = 0;

	/*
	 * Errata applicable for OMAP2430ES1.0 and all omap2420
	 *
	 * I.
	 * Erratum ID: Not Available
	 * Inter Frame DMA buffering issue DMA will wrongly
	 * buffer elements if packing and bursting is enabled. This might
	 * result in data gets stalled in FIFO at the end of the block.
	 * Workaround: DMA channels must have BUFFERING_DISABLED bit set to
	 * guarantee no data will stay in the DMA FIFO in case inter frame
	 * buffering occurs
	 *
	 * II.
	 * Erratum ID: Not Available
	 * DMA may hang when several channels are used in parallel
	 * In the following configuration, DMA channel hanging can occur:
	 * a. Channel i, hardware synchronized, is enabled
	 * b. Another channel (Channel x), software synchronized, is enabled.
	 * c. Channel i is disabled before end of transfer
	 * d. Channel i is reenabled.
	 * e. Steps 1 to 4 are repeated a certain number of times.
	 * f. A third channel (Channel y), software synchronized, is enabled.
	 * Channel x and Channel y may hang immediately after step 'f'.
	 * Workaround:
	 * For any channel used - make sure NextLCH_ID is set to the value j.
	 */
	if (cpu_is_omap2420() || (cpu_is_omap2430() &&
				(omap_type() == OMAP2430_REV_ES1_0))) {

		SET_DMA_ERRATA(DMA_ERRATA_IFRAME_BUFFERING);
		SET_DMA_ERRATA(DMA_ERRATA_PARALLEL_CHANNELS);
	}

	/*
	 * Erratum ID: i378: OMAP2+: sDMA Channel is not disabled
	 * after a transaction error.
	 * Workaround: SW should explicitely disable the channel.
	 */
	if (cpu_class_is_omap2())
		SET_DMA_ERRATA(DMA_ERRATA_i378);

	/*
	 * Erratum ID: i541: sDMA FIFO draining does not finish
	 * If sDMA channel is disabled on the fly, sDMA enters standby even
	 * through FIFO Drain is still in progress
	 * Workaround: Put sDMA in NoStandby more before a logical channel is
	 * disabled, then put it back to SmartStandby right after the channel
	 * finishes FIFO draining.
	 */
	if (cpu_is_omap34xx())
		SET_DMA_ERRATA(DMA_ERRATA_i541);

	/*
	 * Erratum ID: i88 : Special programming model needed to disable DMA
	 * before end of block.
	 * Workaround: software must ensure that the DMA is configured in No
	 * Standby mode(DMAx_OCP_SYSCONFIG.MIDLEMODE = "01")
	 */
	if (omap_type() == OMAP3430_REV_ES1_0)
		SET_DMA_ERRATA(DMA_ERRATA_i88);

	/*
	 * Erratum 3.2/3.3: sometimes 0 is returned if CSAC/CDAC is
	 * read before the DMA controller finished disabling the channel.
	 */
	SET_DMA_ERRATA(DMA_ERRATA_3_3);

	/*
	 * Erratum ID: Not Available
	 * A bug in ROM code leaves IRQ status for channels 0 and 1 uncleared
	 * after secure sram context save and restore.
	 * Work around: Hence we need to manually clear those IRQs to avoid
	 * spurious interrupts. This affects only secure devices.
	 */
	if (cpu_is_omap34xx() && (omap_type() != OMAP2_DEVICE_TYPE_GP))
		SET_DMA_ERRATA(DMA_ROMCODE_BUG);

	return errata;
}