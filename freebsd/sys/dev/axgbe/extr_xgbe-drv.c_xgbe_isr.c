#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  rx_buffer_unavailable; } ;
struct xgbe_hw_if {int /*<<< orphan*/  (* rx_mmc_int ) (struct xgbe_prv_data*) ;int /*<<< orphan*/  (* tx_mmc_int ) (struct xgbe_prv_data*) ;} ;
struct xgbe_prv_data {unsigned int channel_count; int /*<<< orphan*/  restart_work; TYPE_1__ ext_stats; int /*<<< orphan*/  per_channel_irq; struct xgbe_channel* channel; struct xgbe_hw_if hw_if; } ;
struct xgbe_channel {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_CH_SR ; 
 int /*<<< orphan*/  DMA_ISR ; 
 int /*<<< orphan*/  FBE ; 
 int /*<<< orphan*/  MACIS ; 
 int /*<<< orphan*/  MAC_ISR ; 
 int /*<<< orphan*/  MMCRXIS ; 
 int /*<<< orphan*/  MMCTXIS ; 
 int /*<<< orphan*/  RBU ; 
 int /*<<< orphan*/  RI ; 
 int /*<<< orphan*/  TI ; 
 unsigned int XGMAC_DMA_IOREAD (struct xgbe_channel*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XGMAC_DMA_IOWRITE (struct xgbe_channel*,int /*<<< orphan*/ ,unsigned int) ; 
 scalar_t__ XGMAC_GET_BITS (unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned int XGMAC_IOREAD (struct xgbe_prv_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct xgbe_prv_data*) ; 
 int /*<<< orphan*/  stub2 (struct xgbe_prv_data*) ; 
 int /*<<< orphan*/  taskqueue_enqueue (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  taskqueue_thread ; 
 int /*<<< orphan*/  xgbe_all_poll (struct xgbe_prv_data*,int) ; 

__attribute__((used)) static void xgbe_isr(void *data)
{
	struct xgbe_prv_data *pdata = data;
	struct xgbe_hw_if *hw_if = &pdata->hw_if;
	struct xgbe_channel *channel;
	unsigned int dma_isr, dma_ch_isr;
	unsigned int mac_isr;
	unsigned int i;

	/* The DMA interrupt status register also reports MAC and MTL
	 * interrupts. So for polling mode, we just need to check for
	 * this register to be non-zero
	 */
	dma_isr = XGMAC_IOREAD(pdata, DMA_ISR);
	if (!dma_isr)
		return;

	for (i = 0; i < pdata->channel_count; i++) {
		if (!(dma_isr & (1 << i)))
			continue;

		channel = pdata->channel + i;

		dma_ch_isr = XGMAC_DMA_IOREAD(channel, DMA_CH_SR);

		/* The TI or RI interrupt bits may still be set even if using
		 * per channel DMA interrupts. Check to be sure those are not
		 * enabled before using the private data napi structure.
		 */
		if (!pdata->per_channel_irq &&
		    (XGMAC_GET_BITS(dma_ch_isr, DMA_CH_SR, TI) ||
		     XGMAC_GET_BITS(dma_ch_isr, DMA_CH_SR, RI))) {
			xgbe_all_poll(pdata, 16);
		}

		if (XGMAC_GET_BITS(dma_ch_isr, DMA_CH_SR, RBU))
			pdata->ext_stats.rx_buffer_unavailable++;

		/* Restart the device on a Fatal Bus Error */
		if (XGMAC_GET_BITS(dma_ch_isr, DMA_CH_SR, FBE))
			taskqueue_enqueue(taskqueue_thread,
			    &pdata->restart_work);

		/* Clear all interrupt signals */
		XGMAC_DMA_IOWRITE(channel, DMA_CH_SR, dma_ch_isr);
	}

	if (XGMAC_GET_BITS(dma_isr, DMA_ISR, MACIS)) {
		mac_isr = XGMAC_IOREAD(pdata, MAC_ISR);

		if (XGMAC_GET_BITS(mac_isr, MAC_ISR, MMCTXIS))
			hw_if->tx_mmc_int(pdata);

		if (XGMAC_GET_BITS(mac_isr, MAC_ISR, MMCRXIS))
			hw_if->rx_mmc_int(pdata);
	}
}