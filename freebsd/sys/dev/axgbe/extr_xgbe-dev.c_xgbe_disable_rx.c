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
struct xgbe_prv_data {unsigned int rx_q_count; unsigned int channel_count; struct xgbe_channel* channel; } ;
struct xgbe_channel {int /*<<< orphan*/  rx_ring; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACS ; 
 int /*<<< orphan*/  CST ; 
 int /*<<< orphan*/  DCRCC ; 
 int /*<<< orphan*/  DMA_CH_RCR ; 
 int /*<<< orphan*/  MAC_RCR ; 
 int /*<<< orphan*/  MAC_RQC0R ; 
 int /*<<< orphan*/  RE ; 
 int /*<<< orphan*/  SR ; 
 int /*<<< orphan*/  XGMAC_DMA_IOWRITE_BITS (struct xgbe_channel*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XGMAC_IOWRITE (struct xgbe_prv_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XGMAC_IOWRITE_BITS (struct xgbe_prv_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xgbe_prepare_rx_stop (struct xgbe_prv_data*,unsigned int) ; 

__attribute__((used)) static void xgbe_disable_rx(struct xgbe_prv_data *pdata)
{
	struct xgbe_channel *channel;
	unsigned int i;

	/* Disable MAC Rx */
	XGMAC_IOWRITE_BITS(pdata, MAC_RCR, DCRCC, 0);
	XGMAC_IOWRITE_BITS(pdata, MAC_RCR, CST, 0);
	XGMAC_IOWRITE_BITS(pdata, MAC_RCR, ACS, 0);
	XGMAC_IOWRITE_BITS(pdata, MAC_RCR, RE, 0);

	/* Prepare for Rx DMA channel stop */
	for (i = 0; i < pdata->rx_q_count; i++)
		xgbe_prepare_rx_stop(pdata, i);

	/* Disable each Rx queue */
	XGMAC_IOWRITE(pdata, MAC_RQC0R, 0);

	/* Disable each Rx DMA channel */
	channel = pdata->channel;
	for (i = 0; i < pdata->channel_count; i++, channel++) {
		if (!channel->rx_ring)
			break;

		XGMAC_DMA_IOWRITE_BITS(channel, DMA_CH_RCR, SR, 0);
	}
}