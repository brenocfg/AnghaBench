#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {struct ifnet* rcvif; scalar_t__ len; } ;
struct mbuf {TYPE_2__ m_pkthdr; scalar_t__ m_len; } ;
struct ifnet {int /*<<< orphan*/  (* if_input ) (struct ifnet*,struct mbuf*) ;} ;
struct TYPE_6__ {int are_rx_cons; int /*<<< orphan*/  are_rx_ring_map; int /*<<< orphan*/  are_rx_ring_tag; int /*<<< orphan*/  are_rx_tag; struct are_rxdesc* are_rxdesc; } ;
struct TYPE_4__ {struct are_desc* are_rx_ring; } ;
struct are_softc {TYPE_3__ are_cdata; int /*<<< orphan*/  are_dev; TYPE_1__ are_rdata; struct ifnet* are_ifp; } ;
struct are_rxdesc {int saved_ctl; scalar_t__ saved_ca; struct mbuf* rx_m; int /*<<< orphan*/  rx_dmamap; } ;
struct are_desc {int are_stat; scalar_t__ are_addr; int /*<<< orphan*/  are_devcs; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADCTL_ER ; 
 int ADSTAT_OWN ; 
 int ADSTAT_Rx_DE ; 
 int ADSTAT_Rx_LENGTH (int) ; 
 int /*<<< orphan*/  ARE_INC (int,int) ; 
 int /*<<< orphan*/  ARE_LOCK (struct are_softc*) ; 
 int /*<<< orphan*/  ARE_LOCK_ASSERT (struct are_softc*) ; 
 int ARE_RX_RING_CNT ; 
 int /*<<< orphan*/  ARE_UNLOCK (struct are_softc*) ; 
 int BUS_DMASYNC_POSTREAD ; 
 int BUS_DMASYNC_POSTWRITE ; 
 int BUS_DMASYNC_PREREAD ; 
 int BUS_DMASYNC_PREWRITE ; 
 scalar_t__ ETHER_CRC_LEN ; 
 int /*<<< orphan*/  IFCOUNTER_IERRORS ; 
 int /*<<< orphan*/  IFCOUNTER_IPACKETS ; 
 int /*<<< orphan*/  are_fixup_rx (struct mbuf*) ; 
 scalar_t__ are_newbuf (struct are_softc*,int) ; 
 int /*<<< orphan*/  bus_dmamap_sync (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  if_inc_counter (struct ifnet*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (struct ifnet*,struct mbuf*) ; 

__attribute__((used)) static void
are_rx(struct are_softc *sc)
{
	struct are_rxdesc	*rxd;
	struct ifnet		*ifp = sc->are_ifp;
	int			cons, prog, packet_len, error;
	struct are_desc		*cur_rx;
	struct mbuf		*m;

	ARE_LOCK_ASSERT(sc);

	cons = sc->are_cdata.are_rx_cons;

	bus_dmamap_sync(sc->are_cdata.are_rx_ring_tag,
	    sc->are_cdata.are_rx_ring_map,
	    BUS_DMASYNC_POSTREAD | BUS_DMASYNC_POSTWRITE);

	for (prog = 0; prog < ARE_RX_RING_CNT; ARE_INC(cons, ARE_RX_RING_CNT)) {
		cur_rx = &sc->are_rdata.are_rx_ring[cons];
		rxd = &sc->are_cdata.are_rxdesc[cons];
		m = rxd->rx_m;

		if ((cur_rx->are_stat & ADSTAT_OWN) == ADSTAT_OWN)
		       break;	

		prog++;

		packet_len = ADSTAT_Rx_LENGTH(cur_rx->are_stat);
		/* Assume it's error */
		error = 1;

		if (packet_len < 64)
			if_inc_counter(ifp, IFCOUNTER_IERRORS, 1);
		else if ((cur_rx->are_stat & ADSTAT_Rx_DE) == 0) {
			error = 0;
			bus_dmamap_sync(sc->are_cdata.are_rx_tag, rxd->rx_dmamap,
			    BUS_DMASYNC_POSTREAD | BUS_DMASYNC_POSTWRITE);
			m = rxd->rx_m;
			/* Skip 4 bytes of CRC */
			m->m_pkthdr.len = m->m_len = packet_len - ETHER_CRC_LEN;
			are_fixup_rx(m);
			m->m_pkthdr.rcvif = ifp;
			if_inc_counter(ifp, IFCOUNTER_IPACKETS, 1);

			ARE_UNLOCK(sc);
			(*ifp->if_input)(ifp, m);
			ARE_LOCK(sc);
		}

		if (error) {
			/* Restore CONTROL and CA values, reset DEVCS */
			cur_rx->are_stat = rxd->saved_ctl;
			cur_rx->are_addr = rxd->saved_ca;
			cur_rx->are_devcs = 0;
		}
		else {
			/* Reinit descriptor */
			cur_rx->are_stat = ADSTAT_OWN;
			cur_rx->are_devcs = 0;
			if (cons == ARE_RX_RING_CNT - 1)
				cur_rx->are_devcs |= ADCTL_ER;
			cur_rx->are_addr = 0;
			if (are_newbuf(sc, cons) != 0) {
				device_printf(sc->are_dev, 
				    "Failed to allocate buffer\n");
				break;
			}
		}

		bus_dmamap_sync(sc->are_cdata.are_rx_ring_tag,
		    sc->are_cdata.are_rx_ring_map,
		    BUS_DMASYNC_POSTREAD | BUS_DMASYNC_POSTWRITE);

	}

	if (prog > 0) {
		sc->are_cdata.are_rx_cons = cons;

		bus_dmamap_sync(sc->are_cdata.are_rx_ring_tag,
		    sc->are_cdata.are_rx_ring_map,
		    BUS_DMASYNC_PREREAD | BUS_DMASYNC_PREWRITE);
	}
}