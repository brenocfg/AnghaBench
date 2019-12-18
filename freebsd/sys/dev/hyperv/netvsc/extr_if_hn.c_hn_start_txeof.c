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
struct ifnet {int /*<<< orphan*/  if_drv_flags; } ;
struct hn_tx_ring {int /*<<< orphan*/  hn_txeof_task; int /*<<< orphan*/  hn_tx_taskq; int /*<<< orphan*/  hn_tx_task; int /*<<< orphan*/  hn_tx_lock; int /*<<< orphan*/  hn_direct_tx_size; scalar_t__ hn_sched_tx; struct hn_softc* hn_sc; } ;
struct hn_softc {struct hn_tx_ring* hn_tx_ring; struct ifnet* hn_ifp; } ;

/* Variables and functions */
 int /*<<< orphan*/  IFF_DRV_OACTIVE ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  atomic_clear_int (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int hn_start_locked (struct hn_tx_ring*,int /*<<< orphan*/ ) ; 
 scalar_t__ mtx_trylock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  taskqueue_enqueue (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
hn_start_txeof(struct hn_tx_ring *txr)
{
	struct hn_softc *sc = txr->hn_sc;
	struct ifnet *ifp = sc->hn_ifp;

	KASSERT(txr == &sc->hn_tx_ring[0], ("not the first TX ring"));

	if (txr->hn_sched_tx)
		goto do_sched;

	if (mtx_trylock(&txr->hn_tx_lock)) {
		int sched;

		atomic_clear_int(&ifp->if_drv_flags, IFF_DRV_OACTIVE);
		sched = hn_start_locked(txr, txr->hn_direct_tx_size);
		mtx_unlock(&txr->hn_tx_lock);
		if (sched) {
			taskqueue_enqueue(txr->hn_tx_taskq,
			    &txr->hn_tx_task);
		}
	} else {
do_sched:
		/*
		 * Release the OACTIVE earlier, with the hope, that
		 * others could catch up.  The task will clear the
		 * flag again with the hn_tx_lock to avoid possible
		 * races.
		 */
		atomic_clear_int(&ifp->if_drv_flags, IFF_DRV_OACTIVE);
		taskqueue_enqueue(txr->hn_tx_taskq, &txr->hn_txeof_task);
	}
}