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
struct ifnet {struct hn_softc* if_softc; } ;
struct hn_tx_ring {int /*<<< orphan*/  hn_tx_task; int /*<<< orphan*/  hn_tx_taskq; int /*<<< orphan*/  hn_tx_lock; int /*<<< orphan*/  hn_direct_tx_size; scalar_t__ hn_sched_tx; } ;
struct hn_softc {struct hn_tx_ring* hn_tx_ring; } ;

/* Variables and functions */
 int hn_start_locked (struct hn_tx_ring*,int /*<<< orphan*/ ) ; 
 scalar_t__ mtx_trylock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  taskqueue_enqueue (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
hn_start(struct ifnet *ifp)
{
	struct hn_softc *sc = ifp->if_softc;
	struct hn_tx_ring *txr = &sc->hn_tx_ring[0];

	if (txr->hn_sched_tx)
		goto do_sched;

	if (mtx_trylock(&txr->hn_tx_lock)) {
		int sched;

		sched = hn_start_locked(txr, txr->hn_direct_tx_size);
		mtx_unlock(&txr->hn_tx_lock);
		if (!sched)
			return;
	}
do_sched:
	taskqueue_enqueue(txr->hn_tx_taskq, &txr->hn_tx_task);
}