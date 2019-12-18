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
struct xgbe_ring_data {int /*<<< orphan*/  rdata_paddr; } ;
struct xgbe_ring {int cur; int rdesc_count; } ;
struct xgbe_channel {struct xgbe_ring* tx_ring; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBGPR (char*) ; 
 int /*<<< orphan*/  DMA_CH_TDLR_HI ; 
 int /*<<< orphan*/  DMA_CH_TDLR_LO ; 
 int /*<<< orphan*/  DMA_CH_TDRLR ; 
 struct xgbe_ring_data* XGBE_GET_DESC_DATA (struct xgbe_ring*,int) ; 
 int /*<<< orphan*/  XGMAC_DMA_IOWRITE (struct xgbe_channel*,int /*<<< orphan*/ ,int) ; 
 int lower_32_bits (int /*<<< orphan*/ ) ; 
 int upper_32_bits (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xgbe_tx_desc_reset (struct xgbe_ring_data*) ; 

__attribute__((used)) static void xgbe_tx_desc_init(struct xgbe_channel *channel)
{
	struct xgbe_ring *ring = channel->tx_ring;
	struct xgbe_ring_data *rdata;
	int i;
	int start_index = ring->cur;

	DBGPR("-->tx_desc_init\n");

	/* Initialze all descriptors */
	for (i = 0; i < ring->rdesc_count; i++) {
		rdata = XGBE_GET_DESC_DATA(ring, i);

		/* Initialize Tx descriptor */
		xgbe_tx_desc_reset(rdata);
	}

	/* Update the total number of Tx descriptors */
	XGMAC_DMA_IOWRITE(channel, DMA_CH_TDRLR, ring->rdesc_count - 1);

	/* Update the starting address of descriptor ring */
	rdata = XGBE_GET_DESC_DATA(ring, start_index);
	XGMAC_DMA_IOWRITE(channel, DMA_CH_TDLR_HI,
			  upper_32_bits(rdata->rdata_paddr));
	XGMAC_DMA_IOWRITE(channel, DMA_CH_TDLR_LO,
			  lower_32_bits(rdata->rdata_paddr));

	DBGPR("<--tx_desc_init\n");
}