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
struct TYPE_4__ {struct sge_desc* sge_rx_ring; } ;
struct sge_chain_data {int sge_rx_cons; int /*<<< orphan*/  sge_rx_dmamap; int /*<<< orphan*/  sge_rx_tag; TYPE_2__* sge_rxdesc; } ;
struct sge_softc {int /*<<< orphan*/  sge_dev; TYPE_1__ sge_ldata; struct sge_chain_data sge_cdata; struct ifnet* sge_ifp; } ;
struct sge_desc {int /*<<< orphan*/  sge_sts_size; int /*<<< orphan*/  sge_cmdsts; } ;
struct TYPE_6__ {int csum_flags; int csum_data; int ether_vtag; struct ifnet* rcvif; scalar_t__ len; } ;
struct mbuf {TYPE_3__ m_pkthdr; scalar_t__ m_len; int /*<<< orphan*/  m_data; int /*<<< orphan*/  m_flags; } ;
struct ifnet {int if_drv_flags; int if_capenable; int /*<<< orphan*/  (* if_input ) (struct ifnet*,struct mbuf*) ;} ;
struct TYPE_5__ {struct mbuf* rx_m; } ;

/* Variables and functions */
 int BUS_DMASYNC_POSTREAD ; 
 int BUS_DMASYNC_POSTWRITE ; 
 int BUS_DMASYNC_PREREAD ; 
 int BUS_DMASYNC_PREWRITE ; 
 int CSUM_DATA_VALID ; 
 int CSUM_IP_CHECKED ; 
 int CSUM_IP_VALID ; 
 int CSUM_PSEUDO_HDR ; 
 int IFCAP_RXCSUM ; 
 int IFCAP_VLAN_HWTAGGING ; 
 int /*<<< orphan*/  IFCOUNTER_IERRORS ; 
 int /*<<< orphan*/  IFCOUNTER_IPACKETS ; 
 int /*<<< orphan*/  IFCOUNTER_IQDROPS ; 
 int IFF_DRV_RUNNING ; 
 int /*<<< orphan*/  M_VLANTAG ; 
 int RDC_IP_CSUM ; 
 int RDC_IP_CSUM_OK ; 
 int RDC_OWN ; 
 int RDC_TCP_CSUM ; 
 int RDC_TCP_CSUM_OK ; 
 int RDC_UDP_CSUM ; 
 int RDC_UDP_CSUM_OK ; 
 int RDC_VLAN_MASK ; 
 int RDS_CRCOK ; 
 int RDS_VLAN ; 
 int /*<<< orphan*/  RX_ERR_BITS ; 
 int /*<<< orphan*/  SGE_INC (int,int) ; 
 int /*<<< orphan*/  SGE_LOCK (struct sge_softc*) ; 
 int /*<<< orphan*/  SGE_LOCK_ASSERT (struct sge_softc*) ; 
 scalar_t__ SGE_RX_BYTES (int) ; 
 scalar_t__ SGE_RX_ERROR (int) ; 
 int SGE_RX_NSEGS (int) ; 
 scalar_t__ SGE_RX_PAD_BYTES ; 
 int SGE_RX_RING_CNT ; 
 int /*<<< orphan*/  SGE_UNLOCK (struct sge_softc*) ; 
 int /*<<< orphan*/  bus_dmamap_sync (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  if_inc_counter (struct ifnet*,int /*<<< orphan*/ ,int) ; 
 int le32toh (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sge_discard_rxbuf (struct sge_softc*,int) ; 
 scalar_t__ sge_newbuf (struct sge_softc*,int) ; 
 int /*<<< orphan*/  stub1 (struct ifnet*,struct mbuf*) ; 

__attribute__((used)) static void
sge_rxeof(struct sge_softc *sc)
{
        struct ifnet *ifp;
        struct mbuf *m;
	struct sge_chain_data *cd;
	struct sge_desc	*cur_rx;
	uint32_t rxinfo, rxstat;
	int cons, prog;

	SGE_LOCK_ASSERT(sc);

	ifp = sc->sge_ifp;
	cd = &sc->sge_cdata;

	bus_dmamap_sync(cd->sge_rx_tag, cd->sge_rx_dmamap,
	    BUS_DMASYNC_POSTREAD | BUS_DMASYNC_POSTWRITE);
	cons = cd->sge_rx_cons;
	for (prog = 0; prog < SGE_RX_RING_CNT; prog++,
	    SGE_INC(cons, SGE_RX_RING_CNT)) {
		if ((ifp->if_drv_flags & IFF_DRV_RUNNING) == 0)
			break;
		cur_rx = &sc->sge_ldata.sge_rx_ring[cons];
		rxinfo = le32toh(cur_rx->sge_cmdsts);
		if ((rxinfo & RDC_OWN) != 0)
			break;
		rxstat = le32toh(cur_rx->sge_sts_size);
		if ((rxstat & RDS_CRCOK) == 0 || SGE_RX_ERROR(rxstat) != 0 ||
		    SGE_RX_NSEGS(rxstat) != 1) {
			/* XXX We don't support multi-segment frames yet. */
#ifdef SGE_SHOW_ERRORS
			device_printf(sc->sge_dev, "Rx error : 0x%b\n", rxstat,
			    RX_ERR_BITS);
#endif
			sge_discard_rxbuf(sc, cons);
			if_inc_counter(ifp, IFCOUNTER_IERRORS, 1);
			continue;
		}
		m = cd->sge_rxdesc[cons].rx_m;
		if (sge_newbuf(sc, cons) != 0) {
			sge_discard_rxbuf(sc, cons);
			if_inc_counter(ifp, IFCOUNTER_IQDROPS, 1);
			continue;
		}
		if ((ifp->if_capenable & IFCAP_RXCSUM) != 0) {
			if ((rxinfo & RDC_IP_CSUM) != 0 &&
			    (rxinfo & RDC_IP_CSUM_OK) != 0)
				m->m_pkthdr.csum_flags |=
				    CSUM_IP_CHECKED | CSUM_IP_VALID;
			if (((rxinfo & RDC_TCP_CSUM) != 0 &&
			    (rxinfo & RDC_TCP_CSUM_OK) != 0) ||
			    ((rxinfo & RDC_UDP_CSUM) != 0 &&
			    (rxinfo & RDC_UDP_CSUM_OK) != 0)) {
				m->m_pkthdr.csum_flags |=
				    CSUM_DATA_VALID | CSUM_PSEUDO_HDR;
				m->m_pkthdr.csum_data = 0xffff;
			}
		}
		/* Check for VLAN tagged frame. */
		if ((ifp->if_capenable & IFCAP_VLAN_HWTAGGING) != 0 &&
		    (rxstat & RDS_VLAN) != 0) {
			m->m_pkthdr.ether_vtag = rxinfo & RDC_VLAN_MASK;
			m->m_flags |= M_VLANTAG;
		}
		/*
		 * Account for 10bytes auto padding which is used
		 * to align IP header on 32bit boundary.  Also note,
		 * CRC bytes is automatically removed by the
		 * hardware.
		 */
		m->m_data += SGE_RX_PAD_BYTES;
		m->m_pkthdr.len = m->m_len = SGE_RX_BYTES(rxstat) -
		    SGE_RX_PAD_BYTES;
		m->m_pkthdr.rcvif = ifp;
		if_inc_counter(ifp, IFCOUNTER_IPACKETS, 1);
		SGE_UNLOCK(sc);
		(*ifp->if_input)(ifp, m);
		SGE_LOCK(sc);
	}

	if (prog > 0) {
		bus_dmamap_sync(cd->sge_rx_tag, cd->sge_rx_dmamap,
		    BUS_DMASYNC_PREREAD | BUS_DMASYNC_PREWRITE);
		cd->sge_rx_cons = cons;
	}
}