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
struct ifnet {int /*<<< orphan*/  if_drv_flags; } ;
struct age_txdesc {int /*<<< orphan*/ * tx_m; int /*<<< orphan*/  tx_dmamap; TYPE_1__* tx_desc; } ;
struct TYPE_4__ {int age_tx_cons; scalar_t__ age_tx_cnt; int /*<<< orphan*/  age_tx_ring_map; int /*<<< orphan*/  age_tx_ring_tag; int /*<<< orphan*/  age_tx_tag; struct age_txdesc* age_txdesc; } ;
struct age_softc {TYPE_2__ age_cdata; scalar_t__ age_watchdog_timer; struct ifnet* age_ifp; } ;
struct TYPE_3__ {scalar_t__ flags; scalar_t__ len; scalar_t__ addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  AGE_DESC_INC (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AGE_LOCK_ASSERT (struct age_softc*) ; 
 int /*<<< orphan*/  AGE_TX_RING_CNT ; 
 int BUS_DMASYNC_POSTREAD ; 
 int BUS_DMASYNC_POSTWRITE ; 
 int BUS_DMASYNC_PREREAD ; 
 int BUS_DMASYNC_PREWRITE ; 
 int /*<<< orphan*/  IFF_DRV_OACTIVE ; 
 int /*<<< orphan*/  bus_dmamap_sync (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bus_dmamap_unload (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  m_freem (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
age_txintr(struct age_softc *sc, int tpd_cons)
{
	struct ifnet *ifp;
	struct age_txdesc *txd;
	int cons, prog;

	AGE_LOCK_ASSERT(sc);

	ifp = sc->age_ifp;

	bus_dmamap_sync(sc->age_cdata.age_tx_ring_tag,
	    sc->age_cdata.age_tx_ring_map,
	    BUS_DMASYNC_POSTREAD | BUS_DMASYNC_POSTWRITE);

	/*
	 * Go through our Tx list and free mbufs for those
	 * frames which have been transmitted.
	 */
	cons = sc->age_cdata.age_tx_cons;
	for (prog = 0; cons != tpd_cons; AGE_DESC_INC(cons, AGE_TX_RING_CNT)) {
		if (sc->age_cdata.age_tx_cnt <= 0)
			break;
		prog++;
		ifp->if_drv_flags &= ~IFF_DRV_OACTIVE;
		sc->age_cdata.age_tx_cnt--;
		txd = &sc->age_cdata.age_txdesc[cons];
		/*
		 * Clear Tx descriptors, it's not required but would
		 * help debugging in case of Tx issues.
		 */
		txd->tx_desc->addr = 0;
		txd->tx_desc->len = 0;
		txd->tx_desc->flags = 0;

		if (txd->tx_m == NULL)
			continue;
		/* Reclaim transmitted mbufs. */
		bus_dmamap_sync(sc->age_cdata.age_tx_tag, txd->tx_dmamap,
		    BUS_DMASYNC_POSTWRITE);
		bus_dmamap_unload(sc->age_cdata.age_tx_tag, txd->tx_dmamap);
		m_freem(txd->tx_m);
		txd->tx_m = NULL;
	}

	if (prog > 0) {
		sc->age_cdata.age_tx_cons = cons;

		/*
		 * Unarm watchdog timer only when there are no pending
		 * Tx descriptors in queue.
		 */
		if (sc->age_cdata.age_tx_cnt == 0)
			sc->age_watchdog_timer = 0;
		bus_dmamap_sync(sc->age_cdata.age_tx_ring_tag,
		    sc->age_cdata.age_tx_ring_map,
		    BUS_DMASYNC_PREREAD | BUS_DMASYNC_PREWRITE);
	}
}