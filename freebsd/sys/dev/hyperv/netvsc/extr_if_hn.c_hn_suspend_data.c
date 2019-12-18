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
struct hn_tx_ring {int hn_suspended; int /*<<< orphan*/  hn_txeof_task; int /*<<< orphan*/  hn_tx_taskq; int /*<<< orphan*/  hn_tx_task; int /*<<< orphan*/  hn_tx_lock; } ;
struct hn_softc {int hn_tx_ring_inuse; struct hn_tx_ring* hn_tx_ring; int /*<<< orphan*/  hn_rx_ring_inuse; int /*<<< orphan*/  hn_prichan; } ;

/* Variables and functions */
 int /*<<< orphan*/  HN_LOCK_ASSERT (struct hn_softc*) ; 
 int /*<<< orphan*/  hn_disable_rx (struct hn_softc*) ; 
 int /*<<< orphan*/  hn_drain_rxtx (struct hn_softc*,int /*<<< orphan*/ ) ; 
 scalar_t__ hn_tx_ring_pending (struct hn_tx_ring*) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pause (char*,int) ; 
 int /*<<< orphan*/  taskqueue_drain (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vmbus_chan_is_revoked (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
hn_suspend_data(struct hn_softc *sc)
{
	struct hn_tx_ring *txr;
	int i;

	HN_LOCK_ASSERT(sc);

	/*
	 * Suspend TX.
	 */
	for (i = 0; i < sc->hn_tx_ring_inuse; ++i) {
		txr = &sc->hn_tx_ring[i];

		mtx_lock(&txr->hn_tx_lock);
		txr->hn_suspended = 1;
		mtx_unlock(&txr->hn_tx_lock);
		/* No one is able send more packets now. */

		/*
		 * Wait for all pending sends to finish.
		 *
		 * NOTE:
		 * We will _not_ receive all pending send-done, if the
		 * primary channel is revoked.
		 */
		while (hn_tx_ring_pending(txr) &&
		    !vmbus_chan_is_revoked(sc->hn_prichan))
			pause("hnwtx", 1 /* 1 tick */);
	}

	/*
	 * Disable RX.
	 */
	hn_disable_rx(sc);

	/*
	 * Drain RX/TX.
	 */
	hn_drain_rxtx(sc, sc->hn_rx_ring_inuse);

	/*
	 * Drain any pending TX tasks.
	 *
	 * NOTE:
	 * The above hn_drain_rxtx() can dispatch TX tasks, so the TX
	 * tasks will have to be drained _after_ the above hn_drain_rxtx().
	 */
	for (i = 0; i < sc->hn_tx_ring_inuse; ++i) {
		txr = &sc->hn_tx_ring[i];

		taskqueue_drain(txr->hn_tx_taskq, &txr->hn_tx_task);
		taskqueue_drain(txr->hn_tx_taskq, &txr->hn_txeof_task);
	}
}