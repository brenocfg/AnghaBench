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
typedef  int uint32_t ;
struct ifnet {int /*<<< orphan*/  if_drv_flags; } ;
struct TYPE_4__ {scalar_t__ dc_tx_cnt; int dc_tx_cons; int dc_tx_prod; int /*<<< orphan*/ ** dc_tx_chain; int /*<<< orphan*/ * dc_tx_map; } ;
struct TYPE_3__ {struct dc_desc* dc_tx_list; } ;
struct dc_softc {scalar_t__ dc_pmode; int /*<<< orphan*/  dc_tx_lmap; int /*<<< orphan*/  dc_tx_ltag; scalar_t__ dc_wdog_timer; TYPE_2__ dc_cdata; int /*<<< orphan*/  dc_tx_mtag; int /*<<< orphan*/  dc_smap; int /*<<< orphan*/  dc_stag; TYPE_1__ dc_ldata; struct ifnet* dc_ifp; } ;
struct dc_desc {int /*<<< orphan*/  dc_ctl; int /*<<< orphan*/  dc_status; } ;

/* Variables and functions */
 int BUS_DMASYNC_POSTREAD ; 
 int BUS_DMASYNC_POSTWRITE ; 
 int BUS_DMASYNC_PREREAD ; 
 int BUS_DMASYNC_PREWRITE ; 
 int /*<<< orphan*/  DC_INC (int,scalar_t__) ; 
 scalar_t__ DC_IS_CONEXANT (struct dc_softc*) ; 
 scalar_t__ DC_IS_PNIC (struct dc_softc*) ; 
 scalar_t__ DC_IS_XIRCOM (struct dc_softc*) ; 
 scalar_t__ DC_PMODE_MII ; 
 int DC_TXCTL_SETUP ; 
 int DC_TXSTAT_CARRLOST ; 
 int DC_TXSTAT_COLLCNT ; 
 int DC_TXSTAT_ERRSUM ; 
 int DC_TXSTAT_EXCESSCOLL ; 
 int DC_TXSTAT_LATECOLL ; 
 int DC_TXSTAT_NOCARRIER ; 
 int DC_TXSTAT_OWN ; 
 int DC_TXSTAT_UNDERRUN ; 
 scalar_t__ DC_TX_LIST_CNT ; 
 scalar_t__ DC_TX_LIST_RSVD ; 
 int /*<<< orphan*/  IFCOUNTER_COLLISIONS ; 
 int /*<<< orphan*/  IFCOUNTER_OERRORS ; 
 int /*<<< orphan*/  IFCOUNTER_OPACKETS ; 
 int /*<<< orphan*/  IFF_DRV_OACTIVE ; 
 int /*<<< orphan*/  IFF_DRV_RUNNING ; 
 int /*<<< orphan*/  bus_dmamap_sync (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bus_dmamap_unload (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dc_init_locked (struct dc_softc*) ; 
 int /*<<< orphan*/  dc_setfilt (struct dc_softc*) ; 
 int /*<<< orphan*/  htole32 (int) ; 
 int /*<<< orphan*/  if_inc_counter (struct ifnet*,int /*<<< orphan*/ ,int) ; 
 int le32toh (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  m_freem (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
dc_txeof(struct dc_softc *sc)
{
	struct dc_desc *cur_tx;
	struct ifnet *ifp;
	int idx, setup;
	uint32_t ctl, txstat;

	if (sc->dc_cdata.dc_tx_cnt == 0)
		return;

	ifp = sc->dc_ifp;

	/*
	 * Go through our tx list and free mbufs for those
	 * frames that have been transmitted.
	 */
	bus_dmamap_sync(sc->dc_tx_ltag, sc->dc_tx_lmap, BUS_DMASYNC_POSTREAD |
	    BUS_DMASYNC_POSTWRITE);
	setup = 0;
	for (idx = sc->dc_cdata.dc_tx_cons; idx != sc->dc_cdata.dc_tx_prod;
	    DC_INC(idx, DC_TX_LIST_CNT), sc->dc_cdata.dc_tx_cnt--) {
		cur_tx = &sc->dc_ldata.dc_tx_list[idx];
		txstat = le32toh(cur_tx->dc_status);
		ctl = le32toh(cur_tx->dc_ctl);

		if (txstat & DC_TXSTAT_OWN)
			break;

		if (sc->dc_cdata.dc_tx_chain[idx] == NULL)
			continue;

		if (ctl & DC_TXCTL_SETUP) {
			cur_tx->dc_ctl = htole32(ctl & ~DC_TXCTL_SETUP);
			setup++;
			bus_dmamap_sync(sc->dc_stag, sc->dc_smap,
			    BUS_DMASYNC_POSTWRITE);
			/*
			 * Yes, the PNIC is so brain damaged
			 * that it will sometimes generate a TX
			 * underrun error while DMAing the RX
			 * filter setup frame. If we detect this,
			 * we have to send the setup frame again,
			 * or else the filter won't be programmed
			 * correctly.
			 */
			if (DC_IS_PNIC(sc)) {
				if (txstat & DC_TXSTAT_ERRSUM)
					dc_setfilt(sc);
			}
			sc->dc_cdata.dc_tx_chain[idx] = NULL;
			continue;
		}

		if (DC_IS_XIRCOM(sc) || DC_IS_CONEXANT(sc)) {
			/*
			 * XXX: Why does my Xircom taunt me so?
			 * For some reason it likes setting the CARRLOST flag
			 * even when the carrier is there. wtf?!?
			 * Who knows, but Conexant chips have the
			 * same problem. Maybe they took lessons
			 * from Xircom.
			 */
			if (/*sc->dc_type == DC_TYPE_21143 &&*/
			    sc->dc_pmode == DC_PMODE_MII &&
			    ((txstat & 0xFFFF) & ~(DC_TXSTAT_ERRSUM |
			    DC_TXSTAT_NOCARRIER)))
				txstat &= ~DC_TXSTAT_ERRSUM;
		} else {
			if (/*sc->dc_type == DC_TYPE_21143 &&*/
			    sc->dc_pmode == DC_PMODE_MII &&
			    ((txstat & 0xFFFF) & ~(DC_TXSTAT_ERRSUM |
			    DC_TXSTAT_NOCARRIER | DC_TXSTAT_CARRLOST)))
				txstat &= ~DC_TXSTAT_ERRSUM;
		}

		if (txstat & DC_TXSTAT_ERRSUM) {
			if_inc_counter(ifp, IFCOUNTER_OERRORS, 1);
			if (txstat & DC_TXSTAT_EXCESSCOLL)
				if_inc_counter(ifp, IFCOUNTER_COLLISIONS, 1);
			if (txstat & DC_TXSTAT_LATECOLL)
				if_inc_counter(ifp, IFCOUNTER_COLLISIONS, 1);
			if (!(txstat & DC_TXSTAT_UNDERRUN)) {
				ifp->if_drv_flags &= ~IFF_DRV_RUNNING;
				dc_init_locked(sc);
				return;
			}
		} else
			if_inc_counter(ifp, IFCOUNTER_OPACKETS, 1);
		if_inc_counter(ifp, IFCOUNTER_COLLISIONS, (txstat & DC_TXSTAT_COLLCNT) >> 3);

		bus_dmamap_sync(sc->dc_tx_mtag, sc->dc_cdata.dc_tx_map[idx],
		    BUS_DMASYNC_POSTWRITE);
		bus_dmamap_unload(sc->dc_tx_mtag, sc->dc_cdata.dc_tx_map[idx]);
		m_freem(sc->dc_cdata.dc_tx_chain[idx]);
		sc->dc_cdata.dc_tx_chain[idx] = NULL;
	}
	sc->dc_cdata.dc_tx_cons = idx;

	if (sc->dc_cdata.dc_tx_cnt <= DC_TX_LIST_CNT - DC_TX_LIST_RSVD) {
		ifp->if_drv_flags &= ~IFF_DRV_OACTIVE;
		if (sc->dc_cdata.dc_tx_cnt == 0)
			sc->dc_wdog_timer = 0;
	}
	if (setup > 0)
		bus_dmamap_sync(sc->dc_tx_ltag, sc->dc_tx_lmap,
		    BUS_DMASYNC_PREREAD | BUS_DMASYNC_PREWRITE);
}