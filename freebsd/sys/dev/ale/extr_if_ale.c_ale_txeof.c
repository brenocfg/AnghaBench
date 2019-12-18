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
typedef  size_t uint32_t ;
struct ifnet {int /*<<< orphan*/  if_drv_flags; } ;
struct ale_txdesc {int /*<<< orphan*/ * tx_m; int /*<<< orphan*/  tx_dmamap; } ;
struct TYPE_2__ {scalar_t__ ale_tx_cnt; size_t* ale_tx_cmb; size_t ale_tx_cons; int /*<<< orphan*/  ale_tx_tag; struct ale_txdesc* ale_txdesc; int /*<<< orphan*/  ale_tx_cmb_map; int /*<<< orphan*/  ale_tx_cmb_tag; int /*<<< orphan*/  ale_tx_ring_map; int /*<<< orphan*/  ale_tx_ring_tag; } ;
struct ale_softc {int ale_flags; scalar_t__ ale_watchdog_timer; TYPE_1__ ale_cdata; struct ifnet* ale_ifp; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALE_DESC_INC (size_t,int /*<<< orphan*/ ) ; 
 int ALE_FLAG_TXCMB_BUG ; 
 int /*<<< orphan*/  ALE_LOCK_ASSERT (struct ale_softc*) ; 
 int /*<<< orphan*/  ALE_TPD_CONS_IDX ; 
 int /*<<< orphan*/  ALE_TX_RING_CNT ; 
 int BUS_DMASYNC_POSTREAD ; 
 int BUS_DMASYNC_POSTWRITE ; 
 size_t CSR_READ_2 (struct ale_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IFF_DRV_OACTIVE ; 
 size_t TPD_CNT_MASK ; 
 int /*<<< orphan*/  bus_dmamap_sync (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bus_dmamap_unload (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  m_freem (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
ale_txeof(struct ale_softc *sc)
{
	struct ifnet *ifp;
	struct ale_txdesc *txd;
	uint32_t cons, prod;
	int prog;

	ALE_LOCK_ASSERT(sc);

	ifp = sc->ale_ifp;

	if (sc->ale_cdata.ale_tx_cnt == 0)
		return;

	bus_dmamap_sync(sc->ale_cdata.ale_tx_ring_tag,
	    sc->ale_cdata.ale_tx_ring_map,
	    BUS_DMASYNC_POSTREAD | BUS_DMASYNC_POSTWRITE);
	if ((sc->ale_flags & ALE_FLAG_TXCMB_BUG) == 0) {
		bus_dmamap_sync(sc->ale_cdata.ale_tx_cmb_tag,
		    sc->ale_cdata.ale_tx_cmb_map,
		    BUS_DMASYNC_POSTREAD | BUS_DMASYNC_POSTWRITE);
		prod = *sc->ale_cdata.ale_tx_cmb & TPD_CNT_MASK;
	} else
		prod = CSR_READ_2(sc, ALE_TPD_CONS_IDX);
	cons = sc->ale_cdata.ale_tx_cons;
	/*
	 * Go through our Tx list and free mbufs for those
	 * frames which have been transmitted.
	 */
	for (prog = 0; cons != prod; prog++,
	    ALE_DESC_INC(cons, ALE_TX_RING_CNT)) {
		if (sc->ale_cdata.ale_tx_cnt <= 0)
			break;
		prog++;
		ifp->if_drv_flags &= ~IFF_DRV_OACTIVE;
		sc->ale_cdata.ale_tx_cnt--;
		txd = &sc->ale_cdata.ale_txdesc[cons];
		if (txd->tx_m != NULL) {
			/* Reclaim transmitted mbufs. */
			bus_dmamap_sync(sc->ale_cdata.ale_tx_tag,
			    txd->tx_dmamap, BUS_DMASYNC_POSTWRITE);
			bus_dmamap_unload(sc->ale_cdata.ale_tx_tag,
			    txd->tx_dmamap);
			m_freem(txd->tx_m);
			txd->tx_m = NULL;
		}
	}

	if (prog > 0) {
		sc->ale_cdata.ale_tx_cons = cons;
		/*
		 * Unarm watchdog timer only when there is no pending
		 * Tx descriptors in queue.
		 */
		if (sc->ale_cdata.ale_tx_cnt == 0)
			sc->ale_watchdog_timer = 0;
	}
}