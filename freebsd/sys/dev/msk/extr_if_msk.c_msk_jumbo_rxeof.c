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
struct msk_rxdesc {struct mbuf* rx_m; } ;
struct TYPE_4__ {int msk_rx_cons; int msk_rx_prod; struct msk_rxdesc* msk_jumbo_rxdesc; } ;
struct msk_if_softc {int msk_framesize; int msk_flags; TYPE_2__ msk_cdata; int /*<<< orphan*/  msk_vtag; struct ifnet* msk_ifp; } ;
struct TYPE_3__ {int len; int /*<<< orphan*/  ether_vtag; struct ifnet* rcvif; } ;
struct mbuf {int m_len; int /*<<< orphan*/  m_flags; TYPE_1__ m_pkthdr; } ;
struct ifnet {int if_capenable; int /*<<< orphan*/  (* if_input ) (struct ifnet*,struct mbuf*) ;} ;

/* Variables and functions */
 scalar_t__ ETHER_VLAN_ENCAP_LEN ; 
 int GMR_FS_ANY_ERR ; 
 int GMR_FS_GOOD_FC ; 
 int GMR_FS_RX_OK ; 
 int GMR_FS_VLAN ; 
 int IFCAP_RXCSUM ; 
 int IFCAP_VLAN_HWTAGGING ; 
 int /*<<< orphan*/  IFCOUNTER_IERRORS ; 
 int /*<<< orphan*/  IFCOUNTER_IPACKETS ; 
 int /*<<< orphan*/  IFCOUNTER_IQDROPS ; 
 int MSK_FLAG_RAMBUF ; 
 int /*<<< orphan*/  MSK_IF_LOCK (struct msk_if_softc*) ; 
 int /*<<< orphan*/  MSK_IF_LOCK_ASSERT (struct msk_if_softc*) ; 
 int /*<<< orphan*/  MSK_IF_UNLOCK (struct msk_if_softc*) ; 
 int MSK_JUMBO_RX_RING_CNT ; 
 int /*<<< orphan*/  MSK_RX_INC (int,int) ; 
 int /*<<< orphan*/  M_VLANTAG ; 
 int /*<<< orphan*/  if_inc_counter (struct ifnet*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  msk_discard_jumbo_rxbuf (struct msk_if_softc*,int) ; 
 int /*<<< orphan*/  msk_fixup_rx (struct mbuf*) ; 
 scalar_t__ msk_jumbo_newbuf (struct msk_if_softc*,int) ; 
 int /*<<< orphan*/  msk_rxcsum (struct msk_if_softc*,int,struct mbuf*) ; 
 int /*<<< orphan*/  stub1 (struct ifnet*,struct mbuf*) ; 

__attribute__((used)) static void
msk_jumbo_rxeof(struct msk_if_softc *sc_if, uint32_t status, uint32_t control,
    int len)
{
	struct mbuf *m;
	struct ifnet *ifp;
	struct msk_rxdesc *jrxd;
	int cons, rxlen;

	ifp = sc_if->msk_ifp;

	MSK_IF_LOCK_ASSERT(sc_if);

	cons = sc_if->msk_cdata.msk_rx_cons;
	do {
		rxlen = status >> 16;
		if ((status & GMR_FS_VLAN) != 0 &&
		    (ifp->if_capenable & IFCAP_VLAN_HWTAGGING) != 0)
			rxlen -= ETHER_VLAN_ENCAP_LEN;
		if (len > sc_if->msk_framesize ||
		    ((status & GMR_FS_ANY_ERR) != 0) ||
		    ((status & GMR_FS_RX_OK) == 0) || (rxlen != len)) {
			/* Don't count flow-control packet as errors. */
			if ((status & GMR_FS_GOOD_FC) == 0)
				if_inc_counter(ifp, IFCOUNTER_IERRORS, 1);
			msk_discard_jumbo_rxbuf(sc_if, cons);
			break;
		}
#ifdef MSK_64BIT_DMA
		jrxd = &sc_if->msk_cdata.msk_jumbo_rxdesc[(cons + 1) %
		    MSK_JUMBO_RX_RING_CNT];
#else
		jrxd = &sc_if->msk_cdata.msk_jumbo_rxdesc[cons];
#endif
		m = jrxd->rx_m;
		if (msk_jumbo_newbuf(sc_if, cons) != 0) {
			if_inc_counter(ifp, IFCOUNTER_IQDROPS, 1);
			/* Reuse old buffer. */
			msk_discard_jumbo_rxbuf(sc_if, cons);
			break;
		}
		m->m_pkthdr.rcvif = ifp;
		m->m_pkthdr.len = m->m_len = len;
#ifndef __NO_STRICT_ALIGNMENT
		if ((sc_if->msk_flags & MSK_FLAG_RAMBUF) != 0)
			msk_fixup_rx(m);
#endif
		if_inc_counter(ifp, IFCOUNTER_IPACKETS, 1);
		if ((ifp->if_capenable & IFCAP_RXCSUM) != 0)
			msk_rxcsum(sc_if, control, m);
		/* Check for VLAN tagged packets. */
		if ((status & GMR_FS_VLAN) != 0 &&
		    (ifp->if_capenable & IFCAP_VLAN_HWTAGGING) != 0) {
			m->m_pkthdr.ether_vtag = sc_if->msk_vtag;
			m->m_flags |= M_VLANTAG;
		}
		MSK_IF_UNLOCK(sc_if);
		(*ifp->if_input)(ifp, m);
		MSK_IF_LOCK(sc_if);
	} while (0);

	MSK_RX_INC(sc_if->msk_cdata.msk_rx_cons, MSK_JUMBO_RX_RING_CNT);
	MSK_RX_INC(sc_if->msk_cdata.msk_rx_prod, MSK_JUMBO_RX_RING_CNT);
}