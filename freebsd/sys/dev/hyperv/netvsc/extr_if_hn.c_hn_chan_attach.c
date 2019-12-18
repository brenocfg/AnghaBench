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
struct vmbus_channel {int dummy; } ;
struct vmbus_chan_br {int /*<<< orphan*/  cbr_rxsz; int /*<<< orphan*/  cbr_txsz; int /*<<< orphan*/  cbr_paddr; int /*<<< orphan*/  cbr; } ;
struct hn_tx_ring {int hn_tx_flags; struct vmbus_channel* hn_chan; } ;
struct hn_softc {int hn_rx_ring_inuse; int hn_tx_ring_inuse; int /*<<< orphan*/  hn_ifp; struct hn_tx_ring* hn_tx_ring; struct hn_rx_ring* hn_rx_ring; } ;
struct TYPE_2__ {int /*<<< orphan*/  hv_paddr; } ;
struct hn_rx_ring {int hn_rx_flags; TYPE_1__ hn_br_dma; int /*<<< orphan*/  hn_br; struct vmbus_channel* hn_chan; } ;

/* Variables and functions */
 int EISCONN ; 
 int /*<<< orphan*/  HN_RING_IDX2CPU (struct hn_softc*,int) ; 
 int /*<<< orphan*/  HN_RXBR_SIZE ; 
 int HN_RX_FLAG_ATTACHED ; 
 int HN_RX_FLAG_BR_REF ; 
 int /*<<< orphan*/  HN_TXBR_SIZE ; 
 int HN_TX_FLAG_ATTACHED ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 scalar_t__ bootverbose ; 
 int /*<<< orphan*/  hn_chan_callback ; 
 int /*<<< orphan*/  if_printf (int /*<<< orphan*/ ,char*,int,...) ; 
 int /*<<< orphan*/  vmbus_chan_cpu_set (struct vmbus_channel*,int /*<<< orphan*/ ) ; 
 int vmbus_chan_id (struct vmbus_channel*) ; 
 int vmbus_chan_open_br (struct vmbus_channel*,struct vmbus_chan_br*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct hn_rx_ring*) ; 
 int vmbus_chan_subidx (struct vmbus_channel*) ; 

__attribute__((used)) static int
hn_chan_attach(struct hn_softc *sc, struct vmbus_channel *chan)
{
	struct vmbus_chan_br cbr;
	struct hn_rx_ring *rxr;
	struct hn_tx_ring *txr = NULL;
	int idx, error;

	idx = vmbus_chan_subidx(chan);

	/*
	 * Link this channel to RX/TX ring.
	 */
	KASSERT(idx >= 0 && idx < sc->hn_rx_ring_inuse,
	    ("invalid channel index %d, should > 0 && < %d",
	     idx, sc->hn_rx_ring_inuse));
	rxr = &sc->hn_rx_ring[idx];
	KASSERT((rxr->hn_rx_flags & HN_RX_FLAG_ATTACHED) == 0,
	    ("RX ring %d already attached", idx));
	rxr->hn_rx_flags |= HN_RX_FLAG_ATTACHED;
	rxr->hn_chan = chan;

	if (bootverbose) {
		if_printf(sc->hn_ifp, "link RX ring %d to chan%u\n",
		    idx, vmbus_chan_id(chan));
	}

	if (idx < sc->hn_tx_ring_inuse) {
		txr = &sc->hn_tx_ring[idx];
		KASSERT((txr->hn_tx_flags & HN_TX_FLAG_ATTACHED) == 0,
		    ("TX ring %d already attached", idx));
		txr->hn_tx_flags |= HN_TX_FLAG_ATTACHED;

		txr->hn_chan = chan;
		if (bootverbose) {
			if_printf(sc->hn_ifp, "link TX ring %d to chan%u\n",
			    idx, vmbus_chan_id(chan));
		}
	}

	/* Bind this channel to a proper CPU. */
	vmbus_chan_cpu_set(chan, HN_RING_IDX2CPU(sc, idx));

	/*
	 * Open this channel
	 */
	cbr.cbr = rxr->hn_br;
	cbr.cbr_paddr = rxr->hn_br_dma.hv_paddr;
	cbr.cbr_txsz = HN_TXBR_SIZE;
	cbr.cbr_rxsz = HN_RXBR_SIZE;
	error = vmbus_chan_open_br(chan, &cbr, NULL, 0, hn_chan_callback, rxr);
	if (error) {
		if (error == EISCONN) {
			if_printf(sc->hn_ifp, "bufring is connected after "
			    "chan%u open failure\n", vmbus_chan_id(chan));
			rxr->hn_rx_flags |= HN_RX_FLAG_BR_REF;
		} else {
			if_printf(sc->hn_ifp, "open chan%u failed: %d\n",
			    vmbus_chan_id(chan), error);
		}
	}
	return (error);
}