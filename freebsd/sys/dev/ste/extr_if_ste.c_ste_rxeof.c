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
typedef  int uint32_t ;
struct TYPE_6__ {int /*<<< orphan*/  ste_rx_list_map; int /*<<< orphan*/  ste_rx_list_tag; struct ste_chain_onefrag* ste_rx_head; } ;
struct ste_softc {TYPE_3__ ste_cdata; struct ifnet* ste_ifp; } ;
struct ste_chain_onefrag {TYPE_1__* ste_ptr; struct mbuf* ste_mbuf; struct ste_chain_onefrag* ste_next; } ;
struct TYPE_5__ {int len; struct ifnet* rcvif; } ;
struct mbuf {int m_len; TYPE_2__ m_pkthdr; } ;
struct ifnet {int if_capenable; int if_drv_flags; int /*<<< orphan*/  (* if_input ) (struct ifnet*,struct mbuf*) ;} ;
struct TYPE_4__ {scalar_t__ ste_status; } ;

/* Variables and functions */
 int BUS_DMASYNC_POSTREAD ; 
 int BUS_DMASYNC_POSTWRITE ; 
 int BUS_DMASYNC_PREREAD ; 
 int BUS_DMASYNC_PREWRITE ; 
 int IFCAP_POLLING ; 
 int /*<<< orphan*/  IFCOUNTER_IERRORS ; 
 int /*<<< orphan*/  IFCOUNTER_IPACKETS ; 
 int /*<<< orphan*/  IFCOUNTER_IQDROPS ; 
 int IFF_DRV_RUNNING ; 
 int /*<<< orphan*/  STE_LOCK (struct ste_softc*) ; 
 int STE_RXSTAT_DMADONE ; 
 int STE_RXSTAT_FRAME_ERR ; 
 int STE_RX_BYTES (int) ; 
 int STE_RX_LIST_CNT ; 
 int /*<<< orphan*/  STE_UNLOCK (struct ste_softc*) ; 
 int /*<<< orphan*/  bus_dmamap_sync (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  if_inc_counter (struct ifnet*,int /*<<< orphan*/ ,int) ; 
 int le32toh (scalar_t__) ; 
 scalar_t__ ste_newbuf (struct ste_softc*,struct ste_chain_onefrag*) ; 
 int /*<<< orphan*/  stub1 (struct ifnet*,struct mbuf*) ; 

__attribute__((used)) static int
ste_rxeof(struct ste_softc *sc, int count)
{
        struct mbuf *m;
        struct ifnet *ifp;
	struct ste_chain_onefrag *cur_rx;
	uint32_t rxstat;
	int total_len, rx_npkts;

	ifp = sc->ste_ifp;

	bus_dmamap_sync(sc->ste_cdata.ste_rx_list_tag,
	    sc->ste_cdata.ste_rx_list_map,
	    BUS_DMASYNC_POSTREAD | BUS_DMASYNC_POSTWRITE);

	cur_rx = sc->ste_cdata.ste_rx_head;
	for (rx_npkts = 0; rx_npkts < STE_RX_LIST_CNT; rx_npkts++,
	    cur_rx = cur_rx->ste_next) {
		rxstat = le32toh(cur_rx->ste_ptr->ste_status);
		if ((rxstat & STE_RXSTAT_DMADONE) == 0)
			break;
#ifdef DEVICE_POLLING
		if (ifp->if_capenable & IFCAP_POLLING) {
			if (count == 0)
				break;
			count--;
		}
#endif
		if ((ifp->if_drv_flags & IFF_DRV_RUNNING) == 0)
			break;
		/*
		 * If an error occurs, update stats, clear the
		 * status word and leave the mbuf cluster in place:
		 * it should simply get re-used next time this descriptor
	 	 * comes up in the ring.
		 */
		if (rxstat & STE_RXSTAT_FRAME_ERR) {
			if_inc_counter(ifp, IFCOUNTER_IERRORS, 1);
			cur_rx->ste_ptr->ste_status = 0;
			continue;
		}

		/* No errors; receive the packet. */
		m = cur_rx->ste_mbuf;
		total_len = STE_RX_BYTES(rxstat);

		/*
		 * Try to conjure up a new mbuf cluster. If that
		 * fails, it means we have an out of memory condition and
		 * should leave the buffer in place and continue. This will
		 * result in a lost packet, but there's little else we
		 * can do in this situation.
		 */
		if (ste_newbuf(sc, cur_rx) != 0) {
			if_inc_counter(ifp, IFCOUNTER_IQDROPS, 1);
			cur_rx->ste_ptr->ste_status = 0;
			continue;
		}

		m->m_pkthdr.rcvif = ifp;
		m->m_pkthdr.len = m->m_len = total_len;

		if_inc_counter(ifp, IFCOUNTER_IPACKETS, 1);
		STE_UNLOCK(sc);
		(*ifp->if_input)(ifp, m);
		STE_LOCK(sc);
	}

	if (rx_npkts > 0) {
		sc->ste_cdata.ste_rx_head = cur_rx;
		bus_dmamap_sync(sc->ste_cdata.ste_rx_list_tag,
		    sc->ste_cdata.ste_rx_list_map,
		    BUS_DMASYNC_PREREAD | BUS_DMASYNC_PREWRITE);
	}

	return (rx_npkts);
}