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
struct vmbus_channel {int dummy; } ;
struct hn_tx_ring {int hn_tx_flags; } ;
struct hn_softc {int hn_rx_ring_inuse; int hn_tx_ring_inuse; int /*<<< orphan*/  hn_ifp; struct hn_tx_ring* hn_tx_ring; struct hn_rx_ring* hn_rx_ring; } ;
struct hn_rx_ring {int hn_rx_flags; } ;

/* Variables and functions */
 int EISCONN ; 
 int HN_RX_FLAG_ATTACHED ; 
 int HN_RX_FLAG_BR_REF ; 
 int HN_TX_FLAG_ATTACHED ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  if_printf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,...) ; 
 int vmbus_chan_close_direct (struct vmbus_channel*) ; 
 int /*<<< orphan*/  vmbus_chan_id (struct vmbus_channel*) ; 
 int vmbus_chan_subidx (struct vmbus_channel*) ; 

__attribute__((used)) static void
hn_chan_detach(struct hn_softc *sc, struct vmbus_channel *chan)
{
	struct hn_rx_ring *rxr;
	int idx, error;

	idx = vmbus_chan_subidx(chan);

	/*
	 * Link this channel to RX/TX ring.
	 */
	KASSERT(idx >= 0 && idx < sc->hn_rx_ring_inuse,
	    ("invalid channel index %d, should > 0 && < %d",
	     idx, sc->hn_rx_ring_inuse));
	rxr = &sc->hn_rx_ring[idx];
	KASSERT((rxr->hn_rx_flags & HN_RX_FLAG_ATTACHED),
	    ("RX ring %d is not attached", idx));
	rxr->hn_rx_flags &= ~HN_RX_FLAG_ATTACHED;

	if (idx < sc->hn_tx_ring_inuse) {
		struct hn_tx_ring *txr = &sc->hn_tx_ring[idx];

		KASSERT((txr->hn_tx_flags & HN_TX_FLAG_ATTACHED),
		    ("TX ring %d is not attached attached", idx));
		txr->hn_tx_flags &= ~HN_TX_FLAG_ATTACHED;
	}

	/*
	 * Close this channel.
	 *
	 * NOTE:
	 * Channel closing does _not_ destroy the target channel.
	 */
	error = vmbus_chan_close_direct(chan);
	if (error == EISCONN) {
		if_printf(sc->hn_ifp, "chan%u bufring is connected "
		    "after being closed\n", vmbus_chan_id(chan));
		rxr->hn_rx_flags |= HN_RX_FLAG_BR_REF;
	} else if (error) {
		if_printf(sc->hn_ifp, "chan%u close failed: %d\n",
		    vmbus_chan_id(chan), error);
	}
}