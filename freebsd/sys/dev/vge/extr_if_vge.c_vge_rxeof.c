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
struct TYPE_6__ {int vge_rx_prodidx; scalar_t__ vge_rx_commit; int /*<<< orphan*/  vge_rx_ring_map; int /*<<< orphan*/  vge_rx_ring_tag; struct mbuf* vge_tail; struct mbuf* vge_head; struct vge_rxdesc* vge_rxdesc; } ;
struct TYPE_4__ {struct vge_rx_desc* vge_rx_ring; } ;
struct vge_softc {TYPE_3__ vge_cdata; TYPE_1__ vge_rdata; struct ifnet* vge_ifp; } ;
struct vge_rxdesc {struct mbuf* rx_m; } ;
struct vge_rx_desc {int /*<<< orphan*/  vge_ctl; int /*<<< orphan*/  vge_sts; } ;
struct TYPE_5__ {int len; int csum_flags; int csum_data; int /*<<< orphan*/  ether_vtag; struct ifnet* rcvif; } ;
struct mbuf {int m_len; int /*<<< orphan*/  m_flags; TYPE_2__ m_pkthdr; struct mbuf* m_next; } ;
struct ifnet {int if_drv_flags; int if_capenable; int /*<<< orphan*/  (* if_input ) (struct ifnet*,struct mbuf*) ;} ;

/* Variables and functions */
 int BUS_DMASYNC_POSTREAD ; 
 int BUS_DMASYNC_POSTWRITE ; 
 int BUS_DMASYNC_PREREAD ; 
 int BUS_DMASYNC_PREWRITE ; 
 int /*<<< orphan*/  CSR_WRITE_2 (struct vge_softc*,int /*<<< orphan*/ ,scalar_t__) ; 
 int CSUM_DATA_VALID ; 
 int CSUM_IP_CHECKED ; 
 int CSUM_IP_VALID ; 
 int CSUM_PSEUDO_HDR ; 
 int ETHER_CRC_LEN ; 
 int IFCAP_RXCSUM ; 
 int /*<<< orphan*/  IFCOUNTER_IERRORS ; 
 int /*<<< orphan*/  IFCOUNTER_IQDROPS ; 
 int IFF_DRV_RUNNING ; 
 int MCLBYTES ; 
 int /*<<< orphan*/  M_PKTHDR ; 
 int /*<<< orphan*/  M_VLANTAG ; 
 int /*<<< orphan*/  VGE_CHAIN_RESET (struct vge_softc*) ; 
 int /*<<< orphan*/  VGE_LOCK (struct vge_softc*) ; 
 int /*<<< orphan*/  VGE_LOCK_ASSERT (struct vge_softc*) ; 
 int VGE_RDCTL_FRAG ; 
 int VGE_RDCTL_IPCSUMOK ; 
 int VGE_RDCTL_IPPKT ; 
 int VGE_RDCTL_PROTOCSUMOK ; 
 int VGE_RDCTL_TCPPKT ; 
 int VGE_RDCTL_UDPPKT ; 
 int VGE_RDCTL_VLANID ; 
 int VGE_RDSTS_CSUMERR ; 
 int VGE_RDSTS_OWN ; 
 int VGE_RDSTS_RLERR ; 
 int VGE_RDSTS_RXOK ; 
 int VGE_RDSTS_VIDM ; 
 int VGE_RDSTS_VTAG ; 
 int VGE_RXBYTES (int) ; 
 int /*<<< orphan*/  VGE_RXDESC_RESIDUECNT ; 
 int VGE_RXPKT_SOF ; 
 int VGE_RX_BUF_ALIGN ; 
 int /*<<< orphan*/  VGE_RX_DESC_INC (int) ; 
 int /*<<< orphan*/  VGE_UNLOCK (struct vge_softc*) ; 
 int /*<<< orphan*/  bswap16 (int) ; 
 int /*<<< orphan*/  bus_dmamap_sync (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  if_inc_counter (struct ifnet*,int /*<<< orphan*/ ,int) ; 
 int le32toh (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  m_freem (struct mbuf*) ; 
 int /*<<< orphan*/  stub1 (struct ifnet*,struct mbuf*) ; 
 int /*<<< orphan*/  vge_discard_rxbuf (struct vge_softc*,int) ; 
 int /*<<< orphan*/  vge_fixup_rx (struct mbuf*) ; 
 scalar_t__ vge_newbuf (struct vge_softc*,int) ; 

__attribute__((used)) static int
vge_rxeof(struct vge_softc *sc, int count)
{
	struct mbuf *m;
	struct ifnet *ifp;
	int prod, prog, total_len;
	struct vge_rxdesc *rxd;
	struct vge_rx_desc *cur_rx;
	uint32_t rxstat, rxctl;

	VGE_LOCK_ASSERT(sc);

	ifp = sc->vge_ifp;

	bus_dmamap_sync(sc->vge_cdata.vge_rx_ring_tag,
	    sc->vge_cdata.vge_rx_ring_map,
	    BUS_DMASYNC_POSTREAD | BUS_DMASYNC_POSTWRITE);

	prod = sc->vge_cdata.vge_rx_prodidx;
	for (prog = 0; count > 0 &&
	    (ifp->if_drv_flags & IFF_DRV_RUNNING) != 0;
	    VGE_RX_DESC_INC(prod)) {
		cur_rx = &sc->vge_rdata.vge_rx_ring[prod];
		rxstat = le32toh(cur_rx->vge_sts);
		if ((rxstat & VGE_RDSTS_OWN) != 0)
			break;
		count--;
		prog++;
		rxctl = le32toh(cur_rx->vge_ctl);
		total_len = VGE_RXBYTES(rxstat);
		rxd = &sc->vge_cdata.vge_rxdesc[prod];
		m = rxd->rx_m;

		/*
		 * If the 'start of frame' bit is set, this indicates
		 * either the first fragment in a multi-fragment receive,
		 * or an intermediate fragment. Either way, we want to
		 * accumulate the buffers.
		 */
		if ((rxstat & VGE_RXPKT_SOF) != 0) {
			if (vge_newbuf(sc, prod) != 0) {
				if_inc_counter(ifp, IFCOUNTER_IQDROPS, 1);
				VGE_CHAIN_RESET(sc);
				vge_discard_rxbuf(sc, prod);
				continue;
			}
			m->m_len = MCLBYTES - VGE_RX_BUF_ALIGN;
			if (sc->vge_cdata.vge_head == NULL) {
				sc->vge_cdata.vge_head = m;
				sc->vge_cdata.vge_tail = m;
			} else {
				m->m_flags &= ~M_PKTHDR;
				sc->vge_cdata.vge_tail->m_next = m;
				sc->vge_cdata.vge_tail = m;
			}
			continue;
		}

		/*
		 * Bad/error frames will have the RXOK bit cleared.
		 * However, there's one error case we want to allow:
		 * if a VLAN tagged frame arrives and the chip can't
		 * match it against the CAM filter, it considers this
		 * a 'VLAN CAM filter miss' and clears the 'RXOK' bit.
		 * We don't want to drop the frame though: our VLAN
		 * filtering is done in software.
		 * We also want to receive bad-checksummed frames and
		 * and frames with bad-length.
		 */
		if ((rxstat & VGE_RDSTS_RXOK) == 0 &&
		    (rxstat & (VGE_RDSTS_VIDM | VGE_RDSTS_RLERR |
		    VGE_RDSTS_CSUMERR)) == 0) {
			if_inc_counter(ifp, IFCOUNTER_IERRORS, 1);
			/*
			 * If this is part of a multi-fragment packet,
			 * discard all the pieces.
			 */
			VGE_CHAIN_RESET(sc);
			vge_discard_rxbuf(sc, prod);
			continue;
		}

		if (vge_newbuf(sc, prod) != 0) {
			if_inc_counter(ifp, IFCOUNTER_IQDROPS, 1);
			VGE_CHAIN_RESET(sc);
			vge_discard_rxbuf(sc, prod);
			continue;
		}

		/* Chain received mbufs. */
		if (sc->vge_cdata.vge_head != NULL) {
			m->m_len = total_len % (MCLBYTES - VGE_RX_BUF_ALIGN);
			/*
			 * Special case: if there's 4 bytes or less
			 * in this buffer, the mbuf can be discarded:
			 * the last 4 bytes is the CRC, which we don't
			 * care about anyway.
			 */
			if (m->m_len <= ETHER_CRC_LEN) {
				sc->vge_cdata.vge_tail->m_len -=
				    (ETHER_CRC_LEN - m->m_len);
				m_freem(m);
			} else {
				m->m_len -= ETHER_CRC_LEN;
				m->m_flags &= ~M_PKTHDR;
				sc->vge_cdata.vge_tail->m_next = m;
			}
			m = sc->vge_cdata.vge_head;
			m->m_flags |= M_PKTHDR;
			m->m_pkthdr.len = total_len - ETHER_CRC_LEN;
		} else {
			m->m_flags |= M_PKTHDR;
			m->m_pkthdr.len = m->m_len =
			    (total_len - ETHER_CRC_LEN);
		}

#ifndef	__NO_STRICT_ALIGNMENT
		vge_fixup_rx(m);
#endif
		m->m_pkthdr.rcvif = ifp;

		/* Do RX checksumming if enabled */
		if ((ifp->if_capenable & IFCAP_RXCSUM) != 0 &&
		    (rxctl & VGE_RDCTL_FRAG) == 0) {
			/* Check IP header checksum */
			if ((rxctl & VGE_RDCTL_IPPKT) != 0)
				m->m_pkthdr.csum_flags |= CSUM_IP_CHECKED;
			if ((rxctl & VGE_RDCTL_IPCSUMOK) != 0)
				m->m_pkthdr.csum_flags |= CSUM_IP_VALID;

			/* Check TCP/UDP checksum */
			if (rxctl & (VGE_RDCTL_TCPPKT | VGE_RDCTL_UDPPKT) &&
			    rxctl & VGE_RDCTL_PROTOCSUMOK) {
				m->m_pkthdr.csum_flags |=
				    CSUM_DATA_VALID | CSUM_PSEUDO_HDR;
				m->m_pkthdr.csum_data = 0xffff;
			}
		}

		if ((rxstat & VGE_RDSTS_VTAG) != 0) {
			/*
			 * The 32-bit rxctl register is stored in little-endian.
			 * However, the 16-bit vlan tag is stored in big-endian,
			 * so we have to byte swap it.
			 */
			m->m_pkthdr.ether_vtag =
			    bswap16(rxctl & VGE_RDCTL_VLANID);
			m->m_flags |= M_VLANTAG;
		}

		VGE_UNLOCK(sc);
		(*ifp->if_input)(ifp, m);
		VGE_LOCK(sc);
		sc->vge_cdata.vge_head = NULL;
		sc->vge_cdata.vge_tail = NULL;
	}

	if (prog > 0) {
		sc->vge_cdata.vge_rx_prodidx = prod;
		bus_dmamap_sync(sc->vge_cdata.vge_rx_ring_tag,
		    sc->vge_cdata.vge_rx_ring_map,
		    BUS_DMASYNC_PREREAD | BUS_DMASYNC_PREWRITE);
		/* Update residue counter. */
		if (sc->vge_cdata.vge_rx_commit != 0) {
			CSR_WRITE_2(sc, VGE_RXDESC_RESIDUECNT,
			    sc->vge_cdata.vge_rx_commit);
			sc->vge_cdata.vge_rx_commit = 0;
		}
	}
	return (prog);
}