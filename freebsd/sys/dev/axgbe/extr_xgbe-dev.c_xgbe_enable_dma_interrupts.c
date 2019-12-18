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
struct xgbe_prv_data {unsigned int channel_count; int /*<<< orphan*/  per_channel_irq; struct xgbe_channel* channel; } ;
struct xgbe_channel {scalar_t__ rx_ring; scalar_t__ tx_ring; } ;

/* Variables and functions */
 int /*<<< orphan*/  AIE ; 
 int /*<<< orphan*/  DMA_CH_IER ; 
 int /*<<< orphan*/  DMA_CH_SR ; 
 int /*<<< orphan*/  FBEE ; 
 int /*<<< orphan*/  NIE ; 
 int /*<<< orphan*/  RBUE ; 
 int /*<<< orphan*/  RIE ; 
 int /*<<< orphan*/  TIE ; 
 unsigned int XGMAC_DMA_IOREAD (struct xgbe_channel*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XGMAC_DMA_IOWRITE (struct xgbe_channel*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  XGMAC_SET_BITS (unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void xgbe_enable_dma_interrupts(struct xgbe_prv_data *pdata)
{
	struct xgbe_channel *channel;
	unsigned int dma_ch_isr, dma_ch_ier;
	unsigned int i;

	channel = pdata->channel;
	for (i = 0; i < pdata->channel_count; i++, channel++) {
		/* Clear all the interrupts which are set */
		dma_ch_isr = XGMAC_DMA_IOREAD(channel, DMA_CH_SR);
		XGMAC_DMA_IOWRITE(channel, DMA_CH_SR, dma_ch_isr);

		/* Clear all interrupt enable bits */
		dma_ch_ier = 0;

		/* Enable following interrupts
		 *   NIE  - Normal Interrupt Summary Enable
		 *   AIE  - Abnormal Interrupt Summary Enable
		 *   FBEE - Fatal Bus Error Enable
		 */
		XGMAC_SET_BITS(dma_ch_ier, DMA_CH_IER, NIE, 1);
		XGMAC_SET_BITS(dma_ch_ier, DMA_CH_IER, AIE, 1);
		XGMAC_SET_BITS(dma_ch_ier, DMA_CH_IER, FBEE, 1);

		if (channel->tx_ring) {
			/* Enable the following Tx interrupts
			 *   TIE  - Transmit Interrupt Enable (unless using
			 *          per channel interrupts)
			 */
			if (!pdata->per_channel_irq)
				XGMAC_SET_BITS(dma_ch_ier, DMA_CH_IER, TIE, 1);
		}
		if (channel->rx_ring) {
			/* Enable following Rx interrupts
			 *   RBUE - Receive Buffer Unavailable Enable
			 *   RIE  - Receive Interrupt Enable (unless using
			 *          per channel interrupts)
			 */
			XGMAC_SET_BITS(dma_ch_ier, DMA_CH_IER, RBUE, 1);
			if (!pdata->per_channel_irq)
				XGMAC_SET_BITS(dma_ch_ier, DMA_CH_IER, RIE, 1);
		}

		XGMAC_DMA_IOWRITE(channel, DMA_CH_IER, dma_ch_ier);
	}
}