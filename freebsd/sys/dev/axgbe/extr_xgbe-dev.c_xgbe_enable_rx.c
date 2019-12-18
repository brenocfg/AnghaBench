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
struct xgbe_prv_data {unsigned int channel_count; unsigned int rx_q_count; struct xgbe_channel* channel; } ;
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
 int /*<<< orphan*/  XGMAC_DMA_IOWRITE_BITS (struct xgbe_channel*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  XGMAC_IOWRITE (struct xgbe_prv_data*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  XGMAC_IOWRITE_BITS (struct xgbe_prv_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void xgbe_enable_rx(struct xgbe_prv_data *pdata)
{
	struct xgbe_channel *channel;
	unsigned int reg_val, i;

	/* Enable each Rx DMA channel */
	channel = pdata->channel;
	for (i = 0; i < pdata->channel_count; i++, channel++) {
		if (!channel->rx_ring)
			break;

		XGMAC_DMA_IOWRITE_BITS(channel, DMA_CH_RCR, SR, 1);
	}

	/* Enable each Rx queue */
	reg_val = 0;
	for (i = 0; i < pdata->rx_q_count; i++)
		reg_val |= (0x02 << (i << 1));
	XGMAC_IOWRITE(pdata, MAC_RQC0R, reg_val);

	/* Enable MAC Rx */
	XGMAC_IOWRITE_BITS(pdata, MAC_RCR, DCRCC, 1);
	XGMAC_IOWRITE_BITS(pdata, MAC_RCR, CST, 1);
	XGMAC_IOWRITE_BITS(pdata, MAC_RCR, ACS, 1);
	XGMAC_IOWRITE_BITS(pdata, MAC_RCR, RE, 1);
}