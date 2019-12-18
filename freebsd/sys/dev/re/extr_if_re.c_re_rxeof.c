#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u_int32_t ;
struct TYPE_8__ {int rl_rx_prodidx; int /*<<< orphan*/  rl_rx_list_map; int /*<<< orphan*/  rl_rx_list_tag; TYPE_3__* rl_rx_desc; TYPE_2__* rl_jrx_desc; struct rl_desc* rl_rx_list; } ;
struct rl_softc {int rl_flags; int rl_rxlenmask; scalar_t__ rl_type; TYPE_4__ rl_ldata; struct mbuf* rl_tail; struct mbuf* rl_head; struct ifnet* rl_ifp; } ;
struct rl_desc {int /*<<< orphan*/  rl_vlanctl; int /*<<< orphan*/  rl_cmdstat; } ;
struct TYPE_5__ {int len; int csum_flags; int csum_data; int /*<<< orphan*/  ether_vtag; struct ifnet* rcvif; } ;
struct mbuf {int m_len; int /*<<< orphan*/  m_flags; TYPE_1__ m_pkthdr; struct mbuf* m_next; } ;
struct ifnet {scalar_t__ if_mtu; int if_drv_flags; int if_capenable; int /*<<< orphan*/  (* if_input ) (struct ifnet*,struct mbuf*) ;} ;
struct TYPE_7__ {struct mbuf* rx_m; } ;
struct TYPE_6__ {struct mbuf* rx_m; } ;

/* Variables and functions */
 int BUS_DMASYNC_POSTREAD ; 
 int BUS_DMASYNC_POSTWRITE ; 
 int BUS_DMASYNC_PREREAD ; 
 int BUS_DMASYNC_PREWRITE ; 
 int CSUM_DATA_VALID ; 
 int CSUM_IP_CHECKED ; 
 int CSUM_IP_VALID ; 
 int CSUM_PSEUDO_HDR ; 
 int EAGAIN ; 
 int ETHER_CRC_LEN ; 
 int IFCAP_RXCSUM ; 
 int /*<<< orphan*/  IFCOUNTER_IERRORS ; 
 int /*<<< orphan*/  IFCOUNTER_IPACKETS ; 
 int /*<<< orphan*/  IFCOUNTER_IQDROPS ; 
 int IFF_DRV_RUNNING ; 
 int /*<<< orphan*/  M_PKTHDR ; 
 int /*<<< orphan*/  M_VLANTAG ; 
 int RE_RX_DESC_BUFLEN ; 
 scalar_t__ RL_8169 ; 
 int RL_FLAG_DESCV2 ; 
 int RL_FLAG_JUMBOV2 ; 
 int /*<<< orphan*/  RL_LOCK (struct rl_softc*) ; 
 int /*<<< orphan*/  RL_LOCK_ASSERT (struct rl_softc*) ; 
 scalar_t__ RL_MTU ; 
 int RL_RDESC_IPV4 ; 
 int RL_RDESC_STAT_EOF ; 
 int RL_RDESC_STAT_ERRS ; 
 int RL_RDESC_STAT_GIANT ; 
 int RL_RDESC_STAT_IPSUMBAD ; 
 int RL_RDESC_STAT_OWN ; 
 int RL_RDESC_STAT_PROTOID ; 
 int RL_RDESC_STAT_RXERRSUM ; 
 int RL_RDESC_STAT_SOF ; 
 int RL_RDESC_STAT_TCP ; 
 int RL_RDESC_STAT_TCPSUMBAD ; 
 int RL_RDESC_STAT_UDP ; 
 int RL_RDESC_STAT_UDPSUMBAD ; 
 int RL_RDESC_VLANCTL_DATA ; 
 int RL_RDESC_VLANCTL_TAG ; 
 int RL_RX_DESC_NXT (struct rl_softc*,int) ; 
 scalar_t__ RL_TCPPKT (int) ; 
 scalar_t__ RL_UDPPKT (int) ; 
 int /*<<< orphan*/  RL_UNLOCK (struct rl_softc*) ; 
 int /*<<< orphan*/  bswap16 (int) ; 
 int /*<<< orphan*/  bus_dmamap_sync (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  if_inc_counter (struct ifnet*,int /*<<< orphan*/ ,int) ; 
 int le32toh (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  m_freem (struct mbuf*) ; 
 scalar_t__ netmap_rx_irq (struct ifnet*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  re_discard_rxbuf (struct rl_softc*,int) ; 
 int /*<<< orphan*/  re_fixup_rx (struct mbuf*) ; 
 int re_jumbo_newbuf (struct rl_softc*,int) ; 
 int re_newbuf (struct rl_softc*,int) ; 
 int /*<<< orphan*/  stub1 (struct ifnet*,struct mbuf*) ; 

__attribute__((used)) static int
re_rxeof(struct rl_softc *sc, int *rx_npktsp)
{
	struct mbuf		*m;
	struct ifnet		*ifp;
	int			i, rxerr, total_len;
	struct rl_desc		*cur_rx;
	u_int32_t		rxstat, rxvlan;
	int			jumbo, maxpkt = 16, rx_npkts = 0;

	RL_LOCK_ASSERT(sc);

	ifp = sc->rl_ifp;
#ifdef DEV_NETMAP
	if (netmap_rx_irq(ifp, 0, &rx_npkts))
		return 0;
#endif /* DEV_NETMAP */
	if (ifp->if_mtu > RL_MTU && (sc->rl_flags & RL_FLAG_JUMBOV2) != 0)
		jumbo = 1;
	else
		jumbo = 0;

	/* Invalidate the descriptor memory */

	bus_dmamap_sync(sc->rl_ldata.rl_rx_list_tag,
	    sc->rl_ldata.rl_rx_list_map,
	    BUS_DMASYNC_POSTREAD | BUS_DMASYNC_POSTWRITE);

	for (i = sc->rl_ldata.rl_rx_prodidx; maxpkt > 0;
	    i = RL_RX_DESC_NXT(sc, i)) {
		if ((ifp->if_drv_flags & IFF_DRV_RUNNING) == 0)
			break;
		cur_rx = &sc->rl_ldata.rl_rx_list[i];
		rxstat = le32toh(cur_rx->rl_cmdstat);
		if ((rxstat & RL_RDESC_STAT_OWN) != 0)
			break;
		total_len = rxstat & sc->rl_rxlenmask;
		rxvlan = le32toh(cur_rx->rl_vlanctl);
		if (jumbo != 0)
			m = sc->rl_ldata.rl_jrx_desc[i].rx_m;
		else
			m = sc->rl_ldata.rl_rx_desc[i].rx_m;

		if ((sc->rl_flags & RL_FLAG_JUMBOV2) != 0 &&
		    (rxstat & (RL_RDESC_STAT_SOF | RL_RDESC_STAT_EOF)) !=
		    (RL_RDESC_STAT_SOF | RL_RDESC_STAT_EOF)) {
			/*
			 * RTL8168C or later controllers do not
			 * support multi-fragment packet.
			 */
			re_discard_rxbuf(sc, i);
			continue;
		} else if ((rxstat & RL_RDESC_STAT_EOF) == 0) {
			if (re_newbuf(sc, i) != 0) {
				/*
				 * If this is part of a multi-fragment packet,
				 * discard all the pieces.
				 */
				if (sc->rl_head != NULL) {
					m_freem(sc->rl_head);
					sc->rl_head = sc->rl_tail = NULL;
				}
				re_discard_rxbuf(sc, i);
				continue;
			}
			m->m_len = RE_RX_DESC_BUFLEN;
			if (sc->rl_head == NULL)
				sc->rl_head = sc->rl_tail = m;
			else {
				m->m_flags &= ~M_PKTHDR;
				sc->rl_tail->m_next = m;
				sc->rl_tail = m;
			}
			continue;
		}

		/*
		 * NOTE: for the 8139C+, the frame length field
		 * is always 12 bits in size, but for the gigE chips,
		 * it is 13 bits (since the max RX frame length is 16K).
		 * Unfortunately, all 32 bits in the status word
		 * were already used, so to make room for the extra
		 * length bit, RealTek took out the 'frame alignment
		 * error' bit and shifted the other status bits
		 * over one slot. The OWN, EOR, FS and LS bits are
		 * still in the same places. We have already extracted
		 * the frame length and checked the OWN bit, so rather
		 * than using an alternate bit mapping, we shift the
		 * status bits one space to the right so we can evaluate
		 * them using the 8169 status as though it was in the
		 * same format as that of the 8139C+.
		 */
		if (sc->rl_type == RL_8169)
			rxstat >>= 1;

		/*
		 * if total_len > 2^13-1, both _RXERRSUM and _GIANT will be
		 * set, but if CRC is clear, it will still be a valid frame.
		 */
		if ((rxstat & RL_RDESC_STAT_RXERRSUM) != 0) {
			rxerr = 1;
			if ((sc->rl_flags & RL_FLAG_JUMBOV2) == 0 &&
			    total_len > 8191 &&
			    (rxstat & RL_RDESC_STAT_ERRS) == RL_RDESC_STAT_GIANT)
				rxerr = 0;
			if (rxerr != 0) {
				if_inc_counter(ifp, IFCOUNTER_IERRORS, 1);
				/*
				 * If this is part of a multi-fragment packet,
				 * discard all the pieces.
				 */
				if (sc->rl_head != NULL) {
					m_freem(sc->rl_head);
					sc->rl_head = sc->rl_tail = NULL;
				}
				re_discard_rxbuf(sc, i);
				continue;
			}
		}

		/*
		 * If allocating a replacement mbuf fails,
		 * reload the current one.
		 */
		if (jumbo != 0)
			rxerr = re_jumbo_newbuf(sc, i);
		else
			rxerr = re_newbuf(sc, i);
		if (rxerr != 0) {
			if_inc_counter(ifp, IFCOUNTER_IQDROPS, 1);
			if (sc->rl_head != NULL) {
				m_freem(sc->rl_head);
				sc->rl_head = sc->rl_tail = NULL;
			}
			re_discard_rxbuf(sc, i);
			continue;
		}

		if (sc->rl_head != NULL) {
			if (jumbo != 0)
				m->m_len = total_len;
			else {
				m->m_len = total_len % RE_RX_DESC_BUFLEN;
				if (m->m_len == 0)
					m->m_len = RE_RX_DESC_BUFLEN;
			}
			/*
			 * Special case: if there's 4 bytes or less
			 * in this buffer, the mbuf can be discarded:
			 * the last 4 bytes is the CRC, which we don't
			 * care about anyway.
			 */
			if (m->m_len <= ETHER_CRC_LEN) {
				sc->rl_tail->m_len -=
				    (ETHER_CRC_LEN - m->m_len);
				m_freem(m);
			} else {
				m->m_len -= ETHER_CRC_LEN;
				m->m_flags &= ~M_PKTHDR;
				sc->rl_tail->m_next = m;
			}
			m = sc->rl_head;
			sc->rl_head = sc->rl_tail = NULL;
			m->m_pkthdr.len = total_len - ETHER_CRC_LEN;
		} else
			m->m_pkthdr.len = m->m_len =
			    (total_len - ETHER_CRC_LEN);

#ifdef RE_FIXUP_RX
		re_fixup_rx(m);
#endif
		if_inc_counter(ifp, IFCOUNTER_IPACKETS, 1);
		m->m_pkthdr.rcvif = ifp;

		/* Do RX checksumming if enabled */

		if (ifp->if_capenable & IFCAP_RXCSUM) {
			if ((sc->rl_flags & RL_FLAG_DESCV2) == 0) {
				/* Check IP header checksum */
				if (rxstat & RL_RDESC_STAT_PROTOID)
					m->m_pkthdr.csum_flags |=
					    CSUM_IP_CHECKED;
				if (!(rxstat & RL_RDESC_STAT_IPSUMBAD))
					m->m_pkthdr.csum_flags |=
					    CSUM_IP_VALID;

				/* Check TCP/UDP checksum */
				if ((RL_TCPPKT(rxstat) &&
				    !(rxstat & RL_RDESC_STAT_TCPSUMBAD)) ||
				    (RL_UDPPKT(rxstat) &&
				     !(rxstat & RL_RDESC_STAT_UDPSUMBAD))) {
					m->m_pkthdr.csum_flags |=
						CSUM_DATA_VALID|CSUM_PSEUDO_HDR;
					m->m_pkthdr.csum_data = 0xffff;
				}
			} else {
				/*
				 * RTL8168C/RTL816CP/RTL8111C/RTL8111CP
				 */
				if ((rxstat & RL_RDESC_STAT_PROTOID) &&
				    (rxvlan & RL_RDESC_IPV4))
					m->m_pkthdr.csum_flags |=
					    CSUM_IP_CHECKED;
				if (!(rxstat & RL_RDESC_STAT_IPSUMBAD) &&
				    (rxvlan & RL_RDESC_IPV4))
					m->m_pkthdr.csum_flags |=
					    CSUM_IP_VALID;
				if (((rxstat & RL_RDESC_STAT_TCP) &&
				    !(rxstat & RL_RDESC_STAT_TCPSUMBAD)) ||
				    ((rxstat & RL_RDESC_STAT_UDP) &&
				    !(rxstat & RL_RDESC_STAT_UDPSUMBAD))) {
					m->m_pkthdr.csum_flags |=
						CSUM_DATA_VALID|CSUM_PSEUDO_HDR;
					m->m_pkthdr.csum_data = 0xffff;
				}
			}
		}
		maxpkt--;
		if (rxvlan & RL_RDESC_VLANCTL_TAG) {
			m->m_pkthdr.ether_vtag =
			    bswap16((rxvlan & RL_RDESC_VLANCTL_DATA));
			m->m_flags |= M_VLANTAG;
		}
		RL_UNLOCK(sc);
		(*ifp->if_input)(ifp, m);
		RL_LOCK(sc);
		rx_npkts++;
	}

	/* Flush the RX DMA ring */

	bus_dmamap_sync(sc->rl_ldata.rl_rx_list_tag,
	    sc->rl_ldata.rl_rx_list_map,
	    BUS_DMASYNC_PREWRITE|BUS_DMASYNC_PREREAD);

	sc->rl_ldata.rl_rx_prodidx = i;

	if (rx_npktsp != NULL)
		*rx_npktsp = rx_npkts;
	if (maxpkt)
		return (EAGAIN);

	return (0);
}