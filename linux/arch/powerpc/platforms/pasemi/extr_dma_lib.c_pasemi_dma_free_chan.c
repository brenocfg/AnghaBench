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
struct pasemi_dmachan {int chan_type; int /*<<< orphan*/  priv; int /*<<< orphan*/  chno; scalar_t__ ring_virt; } ;

/* Variables and functions */
#define  RXCHAN 129 
#define  TXCHAN 128 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pasemi_dma_free_ring (struct pasemi_dmachan*) ; 
 int /*<<< orphan*/  pasemi_free_rx_chan (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pasemi_free_tx_chan (int /*<<< orphan*/ ) ; 

void pasemi_dma_free_chan(struct pasemi_dmachan *chan)
{
	if (chan->ring_virt)
		pasemi_dma_free_ring(chan);

	switch (chan->chan_type & (RXCHAN|TXCHAN)) {
	case RXCHAN:
		pasemi_free_rx_chan(chan->chno);
		break;
	case TXCHAN:
		pasemi_free_tx_chan(chan->chno);
		break;
	}

	kfree(chan->priv);
}