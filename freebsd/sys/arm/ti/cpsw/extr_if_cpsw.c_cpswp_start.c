#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct ifnet {int if_drv_flags; struct cpswp_softc* if_softc; } ;
struct cpswp_softc {TYPE_2__* swsc; } ;
struct TYPE_5__ {scalar_t__ running; } ;
struct TYPE_6__ {TYPE_1__ tx; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPSW_TX_LOCK (TYPE_2__*) ; 
 int /*<<< orphan*/  CPSW_TX_UNLOCK (TYPE_2__*) ; 
 int IFF_DRV_RUNNING ; 
 int /*<<< orphan*/  cpsw_tx_dequeue (TYPE_2__*) ; 
 int /*<<< orphan*/  cpswp_tx_enqueue (struct cpswp_softc*) ; 

__attribute__((used)) static void
cpswp_start(struct ifnet *ifp)
{
	struct cpswp_softc *sc;

	sc = ifp->if_softc;
	if ((ifp->if_drv_flags & IFF_DRV_RUNNING) == 0 ||
	    sc->swsc->tx.running == 0) {
		return;
	}
	CPSW_TX_LOCK(sc->swsc);
	cpswp_tx_enqueue(sc);
	cpsw_tx_dequeue(sc->swsc);
	CPSW_TX_UNLOCK(sc->swsc);
}