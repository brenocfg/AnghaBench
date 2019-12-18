#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct vmbus_channel {int dummy; } ;
struct hn_softc {int hn_rx_ring_inuse; int hn_rx_ring_cnt; int hn_tx_ring_cnt; TYPE_2__* hn_tx_ring; TYPE_1__* hn_rx_ring; struct vmbus_channel* hn_prichan; } ;
struct TYPE_4__ {int hn_tx_flags; } ;
struct TYPE_3__ {int hn_rx_flags; } ;

/* Variables and functions */
 int HN_RX_FLAG_ATTACHED ; 
 int HN_TX_FLAG_ATTACHED ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  hn_chan_detach (struct hn_softc*,struct vmbus_channel*) ; 
 int /*<<< orphan*/  vmbus_subchan_drain (struct vmbus_channel*) ; 
 struct vmbus_channel** vmbus_subchan_get (struct vmbus_channel*,int) ; 
 int /*<<< orphan*/  vmbus_subchan_rel (struct vmbus_channel**,int) ; 

__attribute__((used)) static void
hn_detach_allchans(struct hn_softc *sc)
{
	struct vmbus_channel **subchans;
	int subchan_cnt = sc->hn_rx_ring_inuse - 1;
	int i;

	if (subchan_cnt == 0)
		goto back;

	/* Detach the sub-channels. */
	subchans = vmbus_subchan_get(sc->hn_prichan, subchan_cnt);
	for (i = 0; i < subchan_cnt; ++i)
		hn_chan_detach(sc, subchans[i]);
	vmbus_subchan_rel(subchans, subchan_cnt);

back:
	/*
	 * Detach the primary channel, _after_ all sub-channels
	 * are detached.
	 */
	hn_chan_detach(sc, sc->hn_prichan);

	/* Wait for sub-channels to be destroyed, if any. */
	vmbus_subchan_drain(sc->hn_prichan);

#ifdef INVARIANTS
	for (i = 0; i < sc->hn_rx_ring_cnt; ++i) {
		KASSERT((sc->hn_rx_ring[i].hn_rx_flags &
		    HN_RX_FLAG_ATTACHED) == 0,
		    ("%dth RX ring is still attached", i));
	}
	for (i = 0; i < sc->hn_tx_ring_cnt; ++i) {
		KASSERT((sc->hn_tx_ring[i].hn_tx_flags &
		    HN_TX_FLAG_ATTACHED) == 0,
		    ("%dth TX ring is still attached", i));
	}
#endif
}