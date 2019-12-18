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
typedef  int uint32_t ;
struct sis_softc {int sis_rx_cons; scalar_t__ rxcycles; int /*<<< orphan*/  sis_rx_list_map; int /*<<< orphan*/  sis_rx_list_tag; struct sis_rxdesc* sis_rxdesc; struct sis_desc* sis_rx_list; struct ifnet* sis_ifp; } ;
struct sis_rxdesc {struct mbuf* rx_m; } ;
struct sis_desc {int /*<<< orphan*/  sis_cmdsts; } ;
struct TYPE_2__ {int len; struct ifnet* rcvif; } ;
struct mbuf {int m_len; TYPE_1__ m_pkthdr; } ;
struct ifnet {int if_drv_flags; int if_capenable; int /*<<< orphan*/  (* if_input ) (struct ifnet*,struct mbuf*) ;} ;

/* Variables and functions */
 int BUS_DMASYNC_POSTREAD ; 
 int BUS_DMASYNC_POSTWRITE ; 
 int BUS_DMASYNC_PREREAD ; 
 int BUS_DMASYNC_PREWRITE ; 
 int ETHER_CRC_LEN ; 
 int ETHER_MAX_LEN ; 
 int ETHER_VLAN_ENCAP_LEN ; 
 int IFCAP_POLLING ; 
 int IFCAP_VLAN_MTU ; 
 int /*<<< orphan*/  IFCOUNTER_COLLISIONS ; 
 int /*<<< orphan*/  IFCOUNTER_IERRORS ; 
 int /*<<< orphan*/  IFCOUNTER_IPACKETS ; 
 int /*<<< orphan*/  IFCOUNTER_IQDROPS ; 
 int IFF_DRV_RUNNING ; 
 int SIS_CMDSTS_BUFLEN ; 
 int SIS_CMDSTS_OWN ; 
 int /*<<< orphan*/  SIS_INC (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SIS_LOCK (struct sis_softc*) ; 
 int /*<<< orphan*/  SIS_LOCK_ASSERT (struct sis_softc*) ; 
 int SIS_RXSTAT_COLL ; 
 scalar_t__ SIS_RXSTAT_ERROR (int) ; 
 int SIS_RXSTAT_GIANT ; 
 int /*<<< orphan*/  SIS_RX_LIST_CNT ; 
 int /*<<< orphan*/  SIS_UNLOCK (struct sis_softc*) ; 
 int /*<<< orphan*/  bus_dmamap_sync (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  if_inc_counter (struct ifnet*,int /*<<< orphan*/ ,int) ; 
 int le32toh (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sis_discard_rxbuf (struct sis_rxdesc*) ; 
 int /*<<< orphan*/  sis_fixup_rx (struct mbuf*) ; 
 scalar_t__ sis_newbuf (struct sis_softc*,struct sis_rxdesc*) ; 
 int /*<<< orphan*/  stub1 (struct ifnet*,struct mbuf*) ; 

__attribute__((used)) static int
sis_rxeof(struct sis_softc *sc)
{
	struct mbuf		*m;
	struct ifnet		*ifp;
	struct sis_rxdesc	*rxd;
	struct sis_desc		*cur_rx;
	int			prog, rx_cons, rx_npkts = 0, total_len;
	uint32_t		rxstat;

	SIS_LOCK_ASSERT(sc);

	bus_dmamap_sync(sc->sis_rx_list_tag, sc->sis_rx_list_map,
	    BUS_DMASYNC_POSTREAD | BUS_DMASYNC_POSTWRITE);

	rx_cons = sc->sis_rx_cons;
	ifp = sc->sis_ifp;

	for (prog = 0; (ifp->if_drv_flags & IFF_DRV_RUNNING) != 0;
	    SIS_INC(rx_cons, SIS_RX_LIST_CNT), prog++) {
#ifdef DEVICE_POLLING
		if (ifp->if_capenable & IFCAP_POLLING) {
			if (sc->rxcycles <= 0)
				break;
			sc->rxcycles--;
		}
#endif
		cur_rx = &sc->sis_rx_list[rx_cons];
		rxstat = le32toh(cur_rx->sis_cmdsts);
		if ((rxstat & SIS_CMDSTS_OWN) == 0)
			break;
		rxd = &sc->sis_rxdesc[rx_cons];

		total_len = (rxstat & SIS_CMDSTS_BUFLEN) - ETHER_CRC_LEN;
		if ((ifp->if_capenable & IFCAP_VLAN_MTU) != 0 &&
		    total_len <= (ETHER_MAX_LEN + ETHER_VLAN_ENCAP_LEN -
		    ETHER_CRC_LEN))
			rxstat &= ~SIS_RXSTAT_GIANT;
		if (SIS_RXSTAT_ERROR(rxstat) != 0) {
			if_inc_counter(ifp, IFCOUNTER_IERRORS, 1);
			if (rxstat & SIS_RXSTAT_COLL)
				if_inc_counter(ifp, IFCOUNTER_COLLISIONS, 1);
			sis_discard_rxbuf(rxd);
			continue;
		}

		/* Add a new receive buffer to the ring. */
		m = rxd->rx_m;
		if (sis_newbuf(sc, rxd) != 0) {
			if_inc_counter(ifp, IFCOUNTER_IQDROPS, 1);
			sis_discard_rxbuf(rxd);
			continue;
		}

		/* No errors; receive the packet. */
		m->m_pkthdr.len = m->m_len = total_len;
#ifndef __NO_STRICT_ALIGNMENT
		/*
		 * On architectures without alignment problems we try to
		 * allocate a new buffer for the receive ring, and pass up
		 * the one where the packet is already, saving the expensive
		 * copy operation.
		 */
		sis_fixup_rx(m);
#endif
		if_inc_counter(ifp, IFCOUNTER_IPACKETS, 1);
		m->m_pkthdr.rcvif = ifp;

		SIS_UNLOCK(sc);
		(*ifp->if_input)(ifp, m);
		SIS_LOCK(sc);
		rx_npkts++;
	}

	if (prog > 0) {
		sc->sis_rx_cons = rx_cons;
		bus_dmamap_sync(sc->sis_rx_list_tag, sc->sis_rx_list_map,
		    BUS_DMASYNC_PREREAD | BUS_DMASYNC_PREWRITE);
	}

	return (rx_npkts);
}