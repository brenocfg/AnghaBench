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
typedef  size_t uint32_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct TYPE_8__ {int /*<<< orphan*/  ti_rx_jumbo_ring_map; int /*<<< orphan*/  ti_rx_jumbo_ring_tag; int /*<<< orphan*/  ti_rx_mini_ring_map; int /*<<< orphan*/  ti_rx_mini_ring_tag; int /*<<< orphan*/  ti_rx_std_ring_map; int /*<<< orphan*/  ti_rx_std_ring_tag; int /*<<< orphan*/  ti_rx_return_ring_map; int /*<<< orphan*/  ti_rx_return_ring_tag; struct mbuf** ti_rx_std_chain; struct mbuf** ti_rx_mini_chain; int /*<<< orphan*/  ti_rx_jumbo_tag; int /*<<< orphan*/ * ti_rx_jumbo_maps; struct mbuf** ti_rx_jumbo_chain; } ;
struct TYPE_6__ {struct ti_rx_desc* ti_rx_return_ring; int /*<<< orphan*/ * ti_rx_mini_ring; } ;
struct TYPE_5__ {scalar_t__ ti_idx; } ;
struct ti_softc {scalar_t__ ti_rx_saved_considx; size_t ti_jumbo; size_t ti_mini; size_t ti_std; scalar_t__ ti_hwrev; TYPE_4__ ti_cdata; scalar_t__ ti_hdrsplit; TYPE_2__ ti_rdata; TYPE_1__ ti_return_prodidx; struct ifnet* ti_ifp; } ;
struct ti_rx_desc {size_t ti_idx; int ti_len; int ti_flags; int ti_ip_cksum; int /*<<< orphan*/  ti_tcp_udp_cksum; int /*<<< orphan*/  ti_addr; int /*<<< orphan*/  ti_vlan_tag; } ;
struct ti_cmd_desc {int dummy; } ;
struct TYPE_7__ {int len; int /*<<< orphan*/  ether_vtag; int /*<<< orphan*/  csum_flags; int /*<<< orphan*/  csum_data; struct ifnet* rcvif; } ;
struct mbuf {int m_len; int /*<<< orphan*/  m_flags; TYPE_3__ m_pkthdr; } ;
struct ifnet {scalar_t__ if_mtu; int if_capenable; int /*<<< orphan*/  (* if_input ) (struct ifnet*,struct mbuf*) ;} ;
typedef  int /*<<< orphan*/  bus_dmamap_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_DMASYNC_POSTREAD ; 
 int /*<<< orphan*/  BUS_DMASYNC_POSTWRITE ; 
 int /*<<< orphan*/  BUS_DMASYNC_PREREAD ; 
 int /*<<< orphan*/  BUS_DMASYNC_PREWRITE ; 
 int /*<<< orphan*/  CSR_WRITE_4 (struct ti_softc*,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  CSUM_DATA_VALID ; 
 int /*<<< orphan*/  CSUM_IP_CHECKED ; 
 int /*<<< orphan*/  CSUM_IP_VALID ; 
 scalar_t__ ENOBUFS ; 
 scalar_t__ ETHERMTU ; 
 scalar_t__ ETHER_HDR_LEN ; 
 scalar_t__ ETHER_VLAN_ENCAP_LEN ; 
 int IFCAP_RXCSUM ; 
 int /*<<< orphan*/  IFCOUNTER_IERRORS ; 
 int /*<<< orphan*/  IFCOUNTER_IPACKETS ; 
 int /*<<< orphan*/  IFCOUNTER_IQDROPS ; 
 int /*<<< orphan*/  M_VLANTAG ; 
 int TI_BDFLAG_ERROR ; 
 int TI_BDFLAG_IP_CKSUM ; 
 int TI_BDFLAG_JUMBO_RING ; 
 int TI_BDFLAG_MINI_RING ; 
 int TI_BDFLAG_TCP_UDP_CKSUM ; 
 int TI_BDFLAG_VLAN_TAG ; 
 int /*<<< orphan*/  TI_GCR_RXRETURNCONS_IDX ; 
 int /*<<< orphan*/  TI_HOSTADDR (int /*<<< orphan*/ ) ; 
 scalar_t__ TI_HWREV_TIGON ; 
 int /*<<< orphan*/  TI_INC (size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TI_JUMBO_RX_RING_CNT ; 
 int /*<<< orphan*/  TI_LOCK (struct ti_softc*) ; 
 int /*<<< orphan*/  TI_LOCK_ASSERT (struct ti_softc*) ; 
 int /*<<< orphan*/  TI_MINI_RX_RING_CNT ; 
 int /*<<< orphan*/  TI_RETURN_RING_CNT ; 
 int /*<<< orphan*/  TI_STD_RX_RING_CNT ; 
 int /*<<< orphan*/  TI_UNLOCK (struct ti_softc*) ; 
 int /*<<< orphan*/  TI_UPDATE_JUMBOPROD (struct ti_softc*,size_t) ; 
 int /*<<< orphan*/  TI_UPDATE_MINIPROD (struct ti_softc*,size_t) ; 
 int /*<<< orphan*/  TI_UPDATE_STDPROD (struct ti_softc*,size_t) ; 
 int /*<<< orphan*/  bus_dmamap_sync (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_dmamap_unload (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  if_inc_counter (struct ifnet*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  m_adj (struct mbuf*,int) ; 
 int /*<<< orphan*/  stub1 (struct ifnet*,struct mbuf*) ; 
 int /*<<< orphan*/  ti_discard_jumbo (struct ti_softc*,size_t) ; 
 int /*<<< orphan*/  ti_discard_mini (struct ti_softc*,size_t) ; 
 int /*<<< orphan*/  ti_discard_std (struct ti_softc*,size_t) ; 
 int /*<<< orphan*/  ti_hdr_split (struct mbuf*,int /*<<< orphan*/ ,int,size_t) ; 
 scalar_t__ ti_newbuf_jumbo (struct ti_softc*,size_t,struct mbuf*) ; 
 scalar_t__ ti_newbuf_mini (struct ti_softc*,size_t) ; 
 scalar_t__ ti_newbuf_std (struct ti_softc*,size_t) ; 

__attribute__((used)) static void
ti_rxeof(struct ti_softc *sc)
{
	struct ifnet *ifp;
#ifdef TI_SF_BUF_JUMBO
	bus_dmamap_t map;
#endif
	struct ti_cmd_desc cmd;
	int jumbocnt, minicnt, stdcnt, ti_len;

	TI_LOCK_ASSERT(sc);

	ifp = sc->ti_ifp;

	bus_dmamap_sync(sc->ti_cdata.ti_rx_std_ring_tag,
	    sc->ti_cdata.ti_rx_std_ring_map, BUS_DMASYNC_POSTWRITE);
	if (ifp->if_mtu > ETHERMTU + ETHER_HDR_LEN + ETHER_VLAN_ENCAP_LEN)
		bus_dmamap_sync(sc->ti_cdata.ti_rx_jumbo_ring_tag,
		    sc->ti_cdata.ti_rx_jumbo_ring_map, BUS_DMASYNC_POSTWRITE);
	if (sc->ti_rdata.ti_rx_mini_ring != NULL)
		bus_dmamap_sync(sc->ti_cdata.ti_rx_mini_ring_tag,
		    sc->ti_cdata.ti_rx_mini_ring_map, BUS_DMASYNC_POSTWRITE);
	bus_dmamap_sync(sc->ti_cdata.ti_rx_return_ring_tag,
	    sc->ti_cdata.ti_rx_return_ring_map, BUS_DMASYNC_POSTREAD);

	jumbocnt = minicnt = stdcnt = 0;
	while (sc->ti_rx_saved_considx != sc->ti_return_prodidx.ti_idx) {
		struct ti_rx_desc *cur_rx;
		uint32_t rxidx;
		struct mbuf *m = NULL;
		uint16_t vlan_tag = 0;
		int have_tag = 0;

		cur_rx =
		    &sc->ti_rdata.ti_rx_return_ring[sc->ti_rx_saved_considx];
		rxidx = cur_rx->ti_idx;
		ti_len = cur_rx->ti_len;
		TI_INC(sc->ti_rx_saved_considx, TI_RETURN_RING_CNT);

		if (cur_rx->ti_flags & TI_BDFLAG_VLAN_TAG) {
			have_tag = 1;
			vlan_tag = cur_rx->ti_vlan_tag;
		}

		if (cur_rx->ti_flags & TI_BDFLAG_JUMBO_RING) {
			jumbocnt++;
			TI_INC(sc->ti_jumbo, TI_JUMBO_RX_RING_CNT);
			m = sc->ti_cdata.ti_rx_jumbo_chain[rxidx];
#ifndef TI_SF_BUF_JUMBO
			if (cur_rx->ti_flags & TI_BDFLAG_ERROR) {
				if_inc_counter(ifp, IFCOUNTER_IERRORS, 1);
				ti_discard_jumbo(sc, rxidx);
				continue;
			}
			if (ti_newbuf_jumbo(sc, rxidx, NULL) != 0) {
				if_inc_counter(ifp, IFCOUNTER_IQDROPS, 1);
				ti_discard_jumbo(sc, rxidx);
				continue;
			}
			m->m_len = ti_len;
#else /* !TI_SF_BUF_JUMBO */
			sc->ti_cdata.ti_rx_jumbo_chain[rxidx] = NULL;
			map = sc->ti_cdata.ti_rx_jumbo_maps[rxidx];
			bus_dmamap_sync(sc->ti_cdata.ti_rx_jumbo_tag, map,
			    BUS_DMASYNC_POSTREAD);
			bus_dmamap_unload(sc->ti_cdata.ti_rx_jumbo_tag, map);
			if (cur_rx->ti_flags & TI_BDFLAG_ERROR) {
				if_inc_counter(ifp, IFCOUNTER_IERRORS, 1);
				ti_newbuf_jumbo(sc, sc->ti_jumbo, m);
				continue;
			}
			if (ti_newbuf_jumbo(sc, sc->ti_jumbo, NULL) == ENOBUFS) {
				if_inc_counter(ifp, IFCOUNTER_IQDROPS, 1);
				ti_newbuf_jumbo(sc, sc->ti_jumbo, m);
				continue;
			}
#ifdef TI_JUMBO_HDRSPLIT
			if (sc->ti_hdrsplit)
				ti_hdr_split(m, TI_HOSTADDR(cur_rx->ti_addr),
					     ti_len, rxidx);
			else
#endif /* TI_JUMBO_HDRSPLIT */
			m_adj(m, ti_len - m->m_pkthdr.len);
#endif /* TI_SF_BUF_JUMBO */
		} else if (cur_rx->ti_flags & TI_BDFLAG_MINI_RING) {
			minicnt++;
			TI_INC(sc->ti_mini, TI_MINI_RX_RING_CNT);
			m = sc->ti_cdata.ti_rx_mini_chain[rxidx];
			if (cur_rx->ti_flags & TI_BDFLAG_ERROR) {
				if_inc_counter(ifp, IFCOUNTER_IERRORS, 1);
				ti_discard_mini(sc, rxidx);
				continue;
			}
			if (ti_newbuf_mini(sc, rxidx) != 0) {
				if_inc_counter(ifp, IFCOUNTER_IQDROPS, 1);
				ti_discard_mini(sc, rxidx);
				continue;
			}
			m->m_len = ti_len;
		} else {
			stdcnt++;
			TI_INC(sc->ti_std, TI_STD_RX_RING_CNT);
			m = sc->ti_cdata.ti_rx_std_chain[rxidx];
			if (cur_rx->ti_flags & TI_BDFLAG_ERROR) {
				if_inc_counter(ifp, IFCOUNTER_IERRORS, 1);
				ti_discard_std(sc, rxidx);
				continue;
			}
			if (ti_newbuf_std(sc, rxidx) != 0) {
				if_inc_counter(ifp, IFCOUNTER_IQDROPS, 1);
				ti_discard_std(sc, rxidx);
				continue;
			}
			m->m_len = ti_len;
		}

		m->m_pkthdr.len = ti_len;
		if_inc_counter(ifp, IFCOUNTER_IPACKETS, 1);
		m->m_pkthdr.rcvif = ifp;

		if (ifp->if_capenable & IFCAP_RXCSUM) {
			if (cur_rx->ti_flags & TI_BDFLAG_IP_CKSUM) {
				m->m_pkthdr.csum_flags |= CSUM_IP_CHECKED;
				if ((cur_rx->ti_ip_cksum ^ 0xffff) == 0)
					m->m_pkthdr.csum_flags |= CSUM_IP_VALID;
			}
			if (cur_rx->ti_flags & TI_BDFLAG_TCP_UDP_CKSUM) {
				m->m_pkthdr.csum_data =
				    cur_rx->ti_tcp_udp_cksum;
				m->m_pkthdr.csum_flags |= CSUM_DATA_VALID;
			}
		}

		/*
		 * If we received a packet with a vlan tag,
		 * tag it before passing the packet upward.
		 */
		if (have_tag) {
			m->m_pkthdr.ether_vtag = vlan_tag;
			m->m_flags |= M_VLANTAG;
		}
		TI_UNLOCK(sc);
		(*ifp->if_input)(ifp, m);
		TI_LOCK(sc);
	}

	bus_dmamap_sync(sc->ti_cdata.ti_rx_return_ring_tag,
	    sc->ti_cdata.ti_rx_return_ring_map, BUS_DMASYNC_PREREAD);
	/* Only necessary on the Tigon 1. */
	if (sc->ti_hwrev == TI_HWREV_TIGON)
		CSR_WRITE_4(sc, TI_GCR_RXRETURNCONS_IDX,
		    sc->ti_rx_saved_considx);

	if (stdcnt > 0) {
		bus_dmamap_sync(sc->ti_cdata.ti_rx_std_ring_tag,
		    sc->ti_cdata.ti_rx_std_ring_map, BUS_DMASYNC_PREWRITE);
		TI_UPDATE_STDPROD(sc, sc->ti_std);
	}
	if (minicnt > 0) {
		bus_dmamap_sync(sc->ti_cdata.ti_rx_mini_ring_tag,
		    sc->ti_cdata.ti_rx_mini_ring_map, BUS_DMASYNC_PREWRITE);
		TI_UPDATE_MINIPROD(sc, sc->ti_mini);
	}
	if (jumbocnt > 0) {
		bus_dmamap_sync(sc->ti_cdata.ti_rx_jumbo_ring_tag,
		    sc->ti_cdata.ti_rx_jumbo_ring_map, BUS_DMASYNC_PREWRITE);
		TI_UPDATE_JUMBOPROD(sc, sc->ti_jumbo);
	}
}