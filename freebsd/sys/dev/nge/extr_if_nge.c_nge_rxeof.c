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
struct TYPE_5__ {int nge_rx_cons; int /*<<< orphan*/  nge_rx_ring_map; int /*<<< orphan*/  nge_rx_ring_tag; struct nge_rxdesc* nge_rxdesc; } ;
struct TYPE_4__ {struct nge_desc* nge_rx_ring; } ;
struct nge_softc {scalar_t__ rxcycles; TYPE_2__ nge_cdata; struct mbuf* nge_tail; struct mbuf* nge_head; TYPE_1__ nge_rdata; struct ifnet* nge_ifp; } ;
struct nge_rxdesc {struct mbuf* rx_m; } ;
struct nge_desc {int /*<<< orphan*/  nge_extsts; int /*<<< orphan*/  nge_cmdsts; } ;
struct TYPE_6__ {int len; int csum_flags; int csum_data; int /*<<< orphan*/  ether_vtag; struct ifnet* rcvif; } ;
struct mbuf {int m_len; int /*<<< orphan*/  m_flags; TYPE_3__ m_pkthdr; struct mbuf* m_next; } ;
struct ifnet {int if_drv_flags; int if_capenable; int /*<<< orphan*/  (* if_input ) (struct ifnet*,struct mbuf*) ;} ;

/* Variables and functions */
 int BUS_DMASYNC_POSTREAD ; 
 int BUS_DMASYNC_POSTWRITE ; 
 int BUS_DMASYNC_PREREAD ; 
 int BUS_DMASYNC_PREWRITE ; 
 int CSUM_DATA_VALID ; 
 int CSUM_IP_CHECKED ; 
 int CSUM_IP_VALID ; 
 int CSUM_PSEUDO_HDR ; 
 int ETHER_CRC_LEN ; 
 int ETHER_MIN_LEN ; 
 int IFCAP_POLLING ; 
 int IFCAP_RXCSUM ; 
 int IFCAP_VLAN_HWTAGGING ; 
 int /*<<< orphan*/  IFCOUNTER_IPACKETS ; 
 int /*<<< orphan*/  IFCOUNTER_IQDROPS ; 
 int IFF_DRV_RUNNING ; 
 int /*<<< orphan*/  M_PKTHDR ; 
 int /*<<< orphan*/  M_VLANTAG ; 
 int NGE_CMDSTS_BUFLEN ; 
 int NGE_CMDSTS_MORE ; 
 int NGE_CMDSTS_OWN ; 
 int NGE_CMDSTS_PKT_OK ; 
 int /*<<< orphan*/  NGE_INC (int,int) ; 
 int /*<<< orphan*/  NGE_LOCK (struct nge_softc*) ; 
 int /*<<< orphan*/  NGE_LOCK_ASSERT (struct nge_softc*) ; 
 int NGE_RXEXTSTS_IPCSUMERR ; 
 int NGE_RXEXTSTS_IPPKT ; 
 int NGE_RXEXTSTS_TCPCSUMERR ; 
 int NGE_RXEXTSTS_TCPPKT ; 
 int NGE_RXEXTSTS_UDPCSUMERR ; 
 int NGE_RXEXTSTS_UDPPKT ; 
 int NGE_RXEXTSTS_VLANPKT ; 
 int NGE_RXEXTSTS_VTCI ; 
 int NGE_RXSTAT_RUNT ; 
 int NGE_RX_RING_CNT ; 
 int /*<<< orphan*/  NGE_UNLOCK (struct nge_softc*) ; 
 int /*<<< orphan*/  bswap16 (int) ; 
 int /*<<< orphan*/  bus_dmamap_sync (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  if_inc_counter (struct ifnet*,int /*<<< orphan*/ ,int) ; 
 int le32toh (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  m_freem (struct mbuf*) ; 
 int /*<<< orphan*/  nge_discard_rxbuf (struct nge_softc*,int) ; 
 int /*<<< orphan*/  nge_fixup_rx (struct mbuf*) ; 
 scalar_t__ nge_newbuf (struct nge_softc*,int) ; 
 int /*<<< orphan*/  stub1 (struct ifnet*,struct mbuf*) ; 

__attribute__((used)) static int
nge_rxeof(struct nge_softc *sc)
{
	struct mbuf *m;
	struct ifnet *ifp;
	struct nge_desc *cur_rx;
	struct nge_rxdesc *rxd;
	int cons, prog, rx_npkts, total_len;
	uint32_t cmdsts, extsts;

	NGE_LOCK_ASSERT(sc);

	ifp = sc->nge_ifp;
	cons = sc->nge_cdata.nge_rx_cons;
	rx_npkts = 0;

	bus_dmamap_sync(sc->nge_cdata.nge_rx_ring_tag,
	    sc->nge_cdata.nge_rx_ring_map,
	    BUS_DMASYNC_POSTREAD | BUS_DMASYNC_POSTWRITE);

	for (prog = 0; prog < NGE_RX_RING_CNT &&
	    (ifp->if_drv_flags & IFF_DRV_RUNNING) != 0;
	    NGE_INC(cons, NGE_RX_RING_CNT)) {
#ifdef DEVICE_POLLING
		if (ifp->if_capenable & IFCAP_POLLING) {
			if (sc->rxcycles <= 0)
				break;
			sc->rxcycles--;
		}
#endif
		cur_rx = &sc->nge_rdata.nge_rx_ring[cons];
		cmdsts = le32toh(cur_rx->nge_cmdsts);
		extsts = le32toh(cur_rx->nge_extsts);
		if ((cmdsts & NGE_CMDSTS_OWN) == 0)
			break;
		prog++;
		rxd = &sc->nge_cdata.nge_rxdesc[cons];
		m = rxd->rx_m;
		total_len = cmdsts & NGE_CMDSTS_BUFLEN;

		if ((cmdsts & NGE_CMDSTS_MORE) != 0) {
			if (nge_newbuf(sc, cons) != 0) {
				if_inc_counter(ifp, IFCOUNTER_IQDROPS, 1);
				if (sc->nge_head != NULL) {
					m_freem(sc->nge_head);
					sc->nge_head = sc->nge_tail = NULL;
				}
				nge_discard_rxbuf(sc, cons);
				continue;
			}
			m->m_len = total_len;
			if (sc->nge_head == NULL) {
				m->m_pkthdr.len = total_len;
				sc->nge_head = sc->nge_tail = m;
			} else {
				m->m_flags &= ~M_PKTHDR;
				sc->nge_head->m_pkthdr.len += total_len;
				sc->nge_tail->m_next = m;
				sc->nge_tail = m;
			}
			continue;
		}

		/*
		 * If an error occurs, update stats, clear the
		 * status word and leave the mbuf cluster in place:
		 * it should simply get re-used next time this descriptor
	 	 * comes up in the ring.
		 */
		if ((cmdsts & NGE_CMDSTS_PKT_OK) == 0) {
			if ((cmdsts & NGE_RXSTAT_RUNT) &&
			    total_len >= (ETHER_MIN_LEN - ETHER_CRC_LEN - 4)) {
				/*
				 * Work-around hardware bug, accept runt frames
				 * if its length is larger than or equal to 56.
				 */
			} else {
				/*
				 * Input error counters are updated by hardware.
				 */
				if (sc->nge_head != NULL) {
					m_freem(sc->nge_head);
					sc->nge_head = sc->nge_tail = NULL;
				}
				nge_discard_rxbuf(sc, cons);
				continue;
			}
		}

		/* Try conjure up a replacement mbuf. */

		if (nge_newbuf(sc, cons) != 0) {
			if_inc_counter(ifp, IFCOUNTER_IQDROPS, 1);
			if (sc->nge_head != NULL) {
				m_freem(sc->nge_head);
				sc->nge_head = sc->nge_tail = NULL;
			}
			nge_discard_rxbuf(sc, cons);
			continue;
		}

		/* Chain received mbufs. */
		if (sc->nge_head != NULL) {
			m->m_len = total_len;
			m->m_flags &= ~M_PKTHDR;
			sc->nge_tail->m_next = m;
			m = sc->nge_head;
			m->m_pkthdr.len += total_len;
			sc->nge_head = sc->nge_tail = NULL;
		} else
			m->m_pkthdr.len = m->m_len = total_len;

		/*
		 * Ok. NatSemi really screwed up here. This is the
		 * only gigE chip I know of with alignment constraints
		 * on receive buffers. RX buffers must be 64-bit aligned.
		 */
		/*
		 * By popular demand, ignore the alignment problems
		 * on the non-strict alignment platform. The performance hit
		 * incurred due to unaligned accesses is much smaller
		 * than the hit produced by forcing buffer copies all
		 * the time, especially with jumbo frames. We still
		 * need to fix up the alignment everywhere else though.
		 */
#ifndef __NO_STRICT_ALIGNMENT
		nge_fixup_rx(m);
#endif
		m->m_pkthdr.rcvif = ifp;
		if_inc_counter(ifp, IFCOUNTER_IPACKETS, 1);

		if ((ifp->if_capenable & IFCAP_RXCSUM) != 0) {
			/* Do IP checksum checking. */
			if ((extsts & NGE_RXEXTSTS_IPPKT) != 0)
				m->m_pkthdr.csum_flags |= CSUM_IP_CHECKED;
			if ((extsts & NGE_RXEXTSTS_IPCSUMERR) == 0)
				m->m_pkthdr.csum_flags |= CSUM_IP_VALID;
			if ((extsts & NGE_RXEXTSTS_TCPPKT &&
			    !(extsts & NGE_RXEXTSTS_TCPCSUMERR)) ||
			    (extsts & NGE_RXEXTSTS_UDPPKT &&
			    !(extsts & NGE_RXEXTSTS_UDPCSUMERR))) {
				m->m_pkthdr.csum_flags |=
				    CSUM_DATA_VALID | CSUM_PSEUDO_HDR;
				m->m_pkthdr.csum_data = 0xffff;
			}
		}

		/*
		 * If we received a packet with a vlan tag, pass it
		 * to vlan_input() instead of ether_input().
		 */
		if ((extsts & NGE_RXEXTSTS_VLANPKT) != 0 &&
		    (ifp->if_capenable & IFCAP_VLAN_HWTAGGING) != 0) {
			m->m_pkthdr.ether_vtag =
			    bswap16(extsts & NGE_RXEXTSTS_VTCI);
			m->m_flags |= M_VLANTAG;
		}
		NGE_UNLOCK(sc);
		(*ifp->if_input)(ifp, m);
		NGE_LOCK(sc);
		rx_npkts++;
	}

	if (prog > 0) {
		sc->nge_cdata.nge_rx_cons = cons;
		bus_dmamap_sync(sc->nge_cdata.nge_rx_ring_tag,
		    sc->nge_cdata.nge_rx_ring_map,
		    BUS_DMASYNC_PREREAD | BUS_DMASYNC_PREWRITE);
	}
	return (rx_npkts);
}