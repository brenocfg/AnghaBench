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
typedef  size_t uint32_t ;
struct sis_txdesc {int /*<<< orphan*/ * tx_m; int /*<<< orphan*/  tx_dmamap; } ;
struct sis_softc {size_t sis_tx_cons; size_t sis_tx_prod; scalar_t__ sis_tx_cnt; scalar_t__ sis_watchdog_timer; int /*<<< orphan*/  sis_tx_tag; struct sis_txdesc* sis_txdesc; struct sis_desc* sis_tx_list; int /*<<< orphan*/  sis_tx_list_map; int /*<<< orphan*/  sis_tx_list_tag; struct ifnet* sis_ifp; } ;
struct sis_desc {int /*<<< orphan*/  sis_cmdsts; } ;
struct ifnet {int /*<<< orphan*/  if_drv_flags; } ;

/* Variables and functions */
 int BUS_DMASYNC_POSTREAD ; 
 int BUS_DMASYNC_POSTWRITE ; 
 int /*<<< orphan*/  IFCOUNTER_COLLISIONS ; 
 int /*<<< orphan*/  IFCOUNTER_OERRORS ; 
 int /*<<< orphan*/  IFCOUNTER_OPACKETS ; 
 int /*<<< orphan*/  IFF_DRV_OACTIVE ; 
 size_t SIS_CMDSTS_OWN ; 
 size_t SIS_CMDSTS_PKT_OK ; 
 int /*<<< orphan*/  SIS_INC (size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SIS_LOCK_ASSERT (struct sis_softc*) ; 
 size_t SIS_TXSTAT_COLLCNT ; 
 size_t SIS_TXSTAT_EXCESSCOLLS ; 
 size_t SIS_TXSTAT_OUTOFWINCOLL ; 
 int /*<<< orphan*/  SIS_TX_LIST_CNT ; 
 int /*<<< orphan*/  bus_dmamap_sync (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bus_dmamap_unload (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  if_inc_counter (struct ifnet*,int /*<<< orphan*/ ,int) ; 
 size_t le32toh (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  m_freem (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
sis_txeof(struct sis_softc *sc)
{
	struct ifnet		*ifp;
	struct sis_desc		*cur_tx;
	struct sis_txdesc	*txd;
	uint32_t		cons, txstat;

	SIS_LOCK_ASSERT(sc);

	cons = sc->sis_tx_cons;
	if (cons == sc->sis_tx_prod)
		return;

	ifp = sc->sis_ifp;
	bus_dmamap_sync(sc->sis_tx_list_tag, sc->sis_tx_list_map,
	    BUS_DMASYNC_POSTREAD | BUS_DMASYNC_POSTWRITE);

	/*
	 * Go through our tx list and free mbufs for those
	 * frames that have been transmitted.
	 */
	for (; cons != sc->sis_tx_prod; SIS_INC(cons, SIS_TX_LIST_CNT)) {
		cur_tx = &sc->sis_tx_list[cons];
		txstat = le32toh(cur_tx->sis_cmdsts);
		if ((txstat & SIS_CMDSTS_OWN) != 0)
			break;
		txd = &sc->sis_txdesc[cons];
		if (txd->tx_m != NULL) {
			bus_dmamap_sync(sc->sis_tx_tag, txd->tx_dmamap,
			    BUS_DMASYNC_POSTWRITE);
			bus_dmamap_unload(sc->sis_tx_tag, txd->tx_dmamap);
			m_freem(txd->tx_m);
			txd->tx_m = NULL;
			if ((txstat & SIS_CMDSTS_PKT_OK) != 0) {
				if_inc_counter(ifp, IFCOUNTER_OPACKETS, 1);
				if_inc_counter(ifp, IFCOUNTER_COLLISIONS,
				    (txstat & SIS_TXSTAT_COLLCNT) >> 16);
			} else {
				if_inc_counter(ifp, IFCOUNTER_OERRORS, 1);
				if (txstat & SIS_TXSTAT_EXCESSCOLLS)
					if_inc_counter(ifp, IFCOUNTER_COLLISIONS, 1);
				if (txstat & SIS_TXSTAT_OUTOFWINCOLL)
					if_inc_counter(ifp, IFCOUNTER_COLLISIONS, 1);
			}
		}
		sc->sis_tx_cnt--;
		ifp->if_drv_flags &= ~IFF_DRV_OACTIVE;
	}
	sc->sis_tx_cons = cons;
	if (sc->sis_tx_cnt == 0)
		sc->sis_watchdog_timer = 0;
}