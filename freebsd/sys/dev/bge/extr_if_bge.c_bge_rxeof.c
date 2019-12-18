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
typedef  size_t uint32_t ;
typedef  size_t uint16_t ;
struct TYPE_5__ {size_t ether_vtag; int /*<<< orphan*/  rcvif; scalar_t__ len; } ;
struct mbuf {scalar_t__ m_data; int /*<<< orphan*/  m_flags; TYPE_2__ m_pkthdr; scalar_t__ m_len; } ;
struct TYPE_6__ {int /*<<< orphan*/  bge_rx_jumbo_ring_map; int /*<<< orphan*/  bge_rx_jumbo_ring_tag; int /*<<< orphan*/  bge_rx_std_ring_map; int /*<<< orphan*/  bge_rx_std_ring_tag; int /*<<< orphan*/  bge_rx_return_ring_map; int /*<<< orphan*/  bge_rx_return_ring_tag; struct mbuf** bge_rx_std_chain; struct mbuf** bge_rx_jumbo_chain; } ;
struct TYPE_4__ {struct bge_rx_bd* bge_rx_return_ring; } ;
struct bge_softc {size_t bge_rx_saved_considx; scalar_t__ rxcycles; int bge_return_ring_cnt; size_t bge_jumbo; size_t bge_std; int bge_flags; TYPE_3__ bge_cdata; TYPE_1__ bge_ldata; int /*<<< orphan*/  bge_ifp; } ;
struct bge_rx_bd {size_t bge_idx; int bge_flags; size_t bge_vlan_tag; scalar_t__ bge_len; } ;
typedef  int /*<<< orphan*/  if_t ;

/* Variables and functions */
 int BGE_FLAG_RX_ALIGNBUG ; 
 int /*<<< orphan*/  BGE_INC (size_t,int) ; 
 scalar_t__ BGE_IS_5705_PLUS (struct bge_softc*) ; 
 scalar_t__ BGE_IS_JUMBO_CAPABLE (struct bge_softc*) ; 
 int BGE_JUMBO_RX_RING_CNT ; 
 int /*<<< orphan*/  BGE_LOCK (struct bge_softc*) ; 
 int /*<<< orphan*/  BGE_MBX_RX_CONS0_LO ; 
 int /*<<< orphan*/  BGE_MBX_RX_JUMBO_PROD_LO ; 
 int /*<<< orphan*/  BGE_MBX_RX_STD_PROD_LO ; 
 int BGE_RXBDFLAG_ERROR ; 
 int BGE_RXBDFLAG_JUMBO_RING ; 
 int BGE_RXBDFLAG_VLAN_TAG ; 
 int /*<<< orphan*/  BGE_RXLP_LOCSTAT_IFIN_DROPS ; 
 int BGE_STD_RX_RING_CNT ; 
 int /*<<< orphan*/  BGE_UNLOCK (struct bge_softc*) ; 
 int /*<<< orphan*/  BUS_DMASYNC_POSTREAD ; 
 int /*<<< orphan*/  BUS_DMASYNC_POSTWRITE ; 
 int /*<<< orphan*/  BUS_DMASYNC_PREREAD ; 
 int /*<<< orphan*/  BUS_DMASYNC_PREWRITE ; 
 int /*<<< orphan*/  CSR_READ_4 (struct bge_softc*,int /*<<< orphan*/ ) ; 
 scalar_t__ ETHER_ALIGN ; 
 scalar_t__ ETHER_CRC_LEN ; 
 scalar_t__ ETHER_HDR_LEN ; 
 scalar_t__ ETHER_VLAN_ENCAP_LEN ; 
 int IFCAP_POLLING ; 
 int IFCAP_RXCSUM ; 
 int IFCAP_VLAN_HWTAGGING ; 
 int /*<<< orphan*/  IFCOUNTER_IPACKETS ; 
 int /*<<< orphan*/  IFCOUNTER_IQDROPS ; 
 int IFF_DRV_RUNNING ; 
 scalar_t__ MCLBYTES ; 
 int /*<<< orphan*/  M_VLANTAG ; 
 int /*<<< orphan*/  bcopy (scalar_t__,scalar_t__,scalar_t__) ; 
 scalar_t__ bge_newbuf_jumbo (struct bge_softc*,size_t) ; 
 scalar_t__ bge_newbuf_std (struct bge_softc*,size_t) ; 
 int /*<<< orphan*/  bge_rxcsum (struct bge_softc*,struct bge_rx_bd*,struct mbuf*) ; 
 int /*<<< orphan*/  bge_rxreuse_jumbo (struct bge_softc*,size_t) ; 
 int /*<<< orphan*/  bge_rxreuse_std (struct bge_softc*,size_t) ; 
 int /*<<< orphan*/  bge_writembx (struct bge_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bus_dmamap_sync (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int if_getcapenable (int /*<<< orphan*/ ) ; 
 int if_getdrvflags (int /*<<< orphan*/ ) ; 
 scalar_t__ if_getmtu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  if_inc_counter (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  if_incierrors (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  if_input (int /*<<< orphan*/ ,struct mbuf*) ; 

__attribute__((used)) static int
bge_rxeof(struct bge_softc *sc, uint16_t rx_prod, int holdlck)
{
	if_t ifp;
	int rx_npkts = 0, stdcnt = 0, jumbocnt = 0;
	uint16_t rx_cons;

	rx_cons = sc->bge_rx_saved_considx;

	/* Nothing to do. */
	if (rx_cons == rx_prod)
		return (rx_npkts);

	ifp = sc->bge_ifp;

	bus_dmamap_sync(sc->bge_cdata.bge_rx_return_ring_tag,
	    sc->bge_cdata.bge_rx_return_ring_map, BUS_DMASYNC_POSTREAD);
	bus_dmamap_sync(sc->bge_cdata.bge_rx_std_ring_tag,
	    sc->bge_cdata.bge_rx_std_ring_map, BUS_DMASYNC_POSTWRITE);
	if (BGE_IS_JUMBO_CAPABLE(sc) &&
	    if_getmtu(ifp) + ETHER_HDR_LEN + ETHER_CRC_LEN + 
	    ETHER_VLAN_ENCAP_LEN > (MCLBYTES - ETHER_ALIGN))
		bus_dmamap_sync(sc->bge_cdata.bge_rx_jumbo_ring_tag,
		    sc->bge_cdata.bge_rx_jumbo_ring_map, BUS_DMASYNC_POSTWRITE);

	while (rx_cons != rx_prod) {
		struct bge_rx_bd	*cur_rx;
		uint32_t		rxidx;
		struct mbuf		*m = NULL;
		uint16_t		vlan_tag = 0;
		int			have_tag = 0;

#ifdef DEVICE_POLLING
		if (if_getcapenable(ifp) & IFCAP_POLLING) {
			if (sc->rxcycles <= 0)
				break;
			sc->rxcycles--;
		}
#endif

		cur_rx = &sc->bge_ldata.bge_rx_return_ring[rx_cons];

		rxidx = cur_rx->bge_idx;
		BGE_INC(rx_cons, sc->bge_return_ring_cnt);

		if (if_getcapenable(ifp) & IFCAP_VLAN_HWTAGGING &&
		    cur_rx->bge_flags & BGE_RXBDFLAG_VLAN_TAG) {
			have_tag = 1;
			vlan_tag = cur_rx->bge_vlan_tag;
		}

		if (cur_rx->bge_flags & BGE_RXBDFLAG_JUMBO_RING) {
			jumbocnt++;
			m = sc->bge_cdata.bge_rx_jumbo_chain[rxidx];
			if (cur_rx->bge_flags & BGE_RXBDFLAG_ERROR) {
				bge_rxreuse_jumbo(sc, rxidx);
				continue;
			}
			if (bge_newbuf_jumbo(sc, rxidx) != 0) {
				bge_rxreuse_jumbo(sc, rxidx);
				if_inc_counter(ifp, IFCOUNTER_IQDROPS, 1);
				continue;
			}
			BGE_INC(sc->bge_jumbo, BGE_JUMBO_RX_RING_CNT);
		} else {
			stdcnt++;
			m = sc->bge_cdata.bge_rx_std_chain[rxidx];
			if (cur_rx->bge_flags & BGE_RXBDFLAG_ERROR) {
				bge_rxreuse_std(sc, rxidx);
				continue;
			}
			if (bge_newbuf_std(sc, rxidx) != 0) {
				bge_rxreuse_std(sc, rxidx);
				if_inc_counter(ifp, IFCOUNTER_IQDROPS, 1);
				continue;
			}
			BGE_INC(sc->bge_std, BGE_STD_RX_RING_CNT);
		}

		if_inc_counter(ifp, IFCOUNTER_IPACKETS, 1);
#ifndef __NO_STRICT_ALIGNMENT
		/*
		 * For architectures with strict alignment we must make sure
		 * the payload is aligned.
		 */
		if (sc->bge_flags & BGE_FLAG_RX_ALIGNBUG) {
			bcopy(m->m_data, m->m_data + ETHER_ALIGN,
			    cur_rx->bge_len);
			m->m_data += ETHER_ALIGN;
		}
#endif
		m->m_pkthdr.len = m->m_len = cur_rx->bge_len - ETHER_CRC_LEN;
		m->m_pkthdr.rcvif = ifp;

		if (if_getcapenable(ifp) & IFCAP_RXCSUM)
			bge_rxcsum(sc, cur_rx, m);

		/*
		 * If we received a packet with a vlan tag,
		 * attach that information to the packet.
		 */
		if (have_tag) {
			m->m_pkthdr.ether_vtag = vlan_tag;
			m->m_flags |= M_VLANTAG;
		}

		if (holdlck != 0) {
			BGE_UNLOCK(sc);
			if_input(ifp, m);
			BGE_LOCK(sc);
		} else
			if_input(ifp, m);
		rx_npkts++;

		if (!(if_getdrvflags(ifp) & IFF_DRV_RUNNING))
			return (rx_npkts);
	}

	bus_dmamap_sync(sc->bge_cdata.bge_rx_return_ring_tag,
	    sc->bge_cdata.bge_rx_return_ring_map, BUS_DMASYNC_PREREAD);
	if (stdcnt > 0)
		bus_dmamap_sync(sc->bge_cdata.bge_rx_std_ring_tag,
		    sc->bge_cdata.bge_rx_std_ring_map, BUS_DMASYNC_PREWRITE);

	if (jumbocnt > 0)
		bus_dmamap_sync(sc->bge_cdata.bge_rx_jumbo_ring_tag,
		    sc->bge_cdata.bge_rx_jumbo_ring_map, BUS_DMASYNC_PREWRITE);

	sc->bge_rx_saved_considx = rx_cons;
	bge_writembx(sc, BGE_MBX_RX_CONS0_LO, sc->bge_rx_saved_considx);
	if (stdcnt)
		bge_writembx(sc, BGE_MBX_RX_STD_PROD_LO, (sc->bge_std +
		    BGE_STD_RX_RING_CNT - 1) % BGE_STD_RX_RING_CNT);
	if (jumbocnt)
		bge_writembx(sc, BGE_MBX_RX_JUMBO_PROD_LO, (sc->bge_jumbo +
		    BGE_JUMBO_RX_RING_CNT - 1) % BGE_JUMBO_RX_RING_CNT);
#ifdef notyet
	/*
	 * This register wraps very quickly under heavy packet drops.
	 * If you need correct statistics, you can enable this check.
	 */
	if (BGE_IS_5705_PLUS(sc))
		if_incierrors(ifp, CSR_READ_4(sc, BGE_RXLP_LOCSTAT_IFIN_DROPS));
#endif
	return (rx_npkts);
}