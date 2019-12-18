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
struct hn_tx_ring {int /*<<< orphan*/  hn_txeof_task; int /*<<< orphan*/  hn_tx_taskq; } ;
struct hn_softc {int hn_tx_ring_cnt; int hn_tx_ring_inuse; struct hn_tx_ring* hn_tx_ring; } ;

/* Variables and functions */
 int /*<<< orphan*/  HN_LOCK_ASSERT (struct hn_softc*) ; 
 int /*<<< orphan*/  hn_resume_tx (struct hn_softc*,int) ; 
 int /*<<< orphan*/  hn_rxfilter_config (struct hn_softc*) ; 
 int /*<<< orphan*/  hn_tx_ring_qflush (struct hn_tx_ring*) ; 
 int /*<<< orphan*/  hn_use_if_start ; 
 int /*<<< orphan*/  taskqueue_enqueue (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
hn_resume_data(struct hn_softc *sc)
{
	int i;

	HN_LOCK_ASSERT(sc);

	/*
	 * Re-enable RX.
	 */
	hn_rxfilter_config(sc);

	/*
	 * Make sure to clear suspend status on "all" TX rings,
	 * since hn_tx_ring_inuse can be changed after
	 * hn_suspend_data().
	 */
	hn_resume_tx(sc, sc->hn_tx_ring_cnt);

#ifdef HN_IFSTART_SUPPORT
	if (!hn_use_if_start)
#endif
	{
		/*
		 * Flush unused drbrs, since hn_tx_ring_inuse may be
		 * reduced.
		 */
		for (i = sc->hn_tx_ring_inuse; i < sc->hn_tx_ring_cnt; ++i)
			hn_tx_ring_qflush(&sc->hn_tx_ring[i]);
	}

	/*
	 * Kick start TX.
	 */
	for (i = 0; i < sc->hn_tx_ring_inuse; ++i) {
		struct hn_tx_ring *txr = &sc->hn_tx_ring[i];

		/*
		 * Use txeof task, so that any pending oactive can be
		 * cleared properly.
		 */
		taskqueue_enqueue(txr->hn_tx_taskq, &txr->hn_txeof_task);
	}
}