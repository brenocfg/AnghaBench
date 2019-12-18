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
typedef  int /*<<< orphan*/  u_int32_t ;
struct TYPE_6__ {scalar_t__ len; struct ifnet* rcvif; } ;
struct mbuf {scalar_t__ m_len; TYPE_3__ m_pkthdr; } ;
struct ifnet {int if_capenable; int /*<<< orphan*/  (* if_input ) (struct ifnet*,struct mbuf*) ;} ;
struct TYPE_5__ {TYPE_1__* rb_rxdesc; } ;
struct hme_softc {TYPE_2__ sc_rb; int /*<<< orphan*/  sc_dev; struct ifnet* sc_ifp; } ;
struct ether_header {int dummy; } ;
struct TYPE_4__ {struct mbuf* hrx_m; } ;

/* Variables and functions */
 int /*<<< orphan*/  CTR1 (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  HME_LOCK (struct hme_softc*) ; 
 int HME_MAX_FRAMESIZE ; 
 scalar_t__ HME_RXOFFS ; 
 int /*<<< orphan*/  HME_UNLOCK (struct hme_softc*) ; 
 int /*<<< orphan*/  HME_WHINE (int /*<<< orphan*/ ,char*,int) ; 
 int IFCAP_RXCSUM ; 
 int /*<<< orphan*/  IFCOUNTER_IERRORS ; 
 int /*<<< orphan*/  IFCOUNTER_IPACKETS ; 
 int /*<<< orphan*/  IFCOUNTER_IQDROPS ; 
 int /*<<< orphan*/  KTR_HME ; 
 scalar_t__ hme_add_rxbuf (struct hme_softc*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hme_discard_rxbuf (struct hme_softc*,int) ; 
 int /*<<< orphan*/  hme_rxcksum (struct mbuf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  if_inc_counter (struct ifnet*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  m_adj (struct mbuf*,scalar_t__) ; 
 int /*<<< orphan*/  stub1 (struct ifnet*,struct mbuf*) ; 

__attribute__((used)) static void
hme_read(struct hme_softc *sc, int ix, int len, u_int32_t flags)
{
	struct ifnet *ifp = sc->sc_ifp;
	struct mbuf *m;

	if (len <= sizeof(struct ether_header) ||
	    len > HME_MAX_FRAMESIZE) {
#ifdef HMEDEBUG
		HME_WHINE(sc->sc_dev, "invalid packet size %d; dropping\n",
		    len);
#endif
		if_inc_counter(ifp, IFCOUNTER_IERRORS, 1);
		hme_discard_rxbuf(sc, ix);
		return;
	}

	m = sc->sc_rb.rb_rxdesc[ix].hrx_m;
	CTR1(KTR_HME, "hme_read: len %d", len);

	if (hme_add_rxbuf(sc, ix, 0) != 0) {
		/*
		 * hme_add_rxbuf will leave the old buffer in the ring until
		 * it is sure that a new buffer can be mapped. If it can not,
		 * drop the packet, but leave the interface up.
		 */
		if_inc_counter(ifp, IFCOUNTER_IQDROPS, 1);
		hme_discard_rxbuf(sc, ix);
		return;
	}

	if_inc_counter(ifp, IFCOUNTER_IPACKETS, 1);

	m->m_pkthdr.rcvif = ifp;
	m->m_pkthdr.len = m->m_len = len + HME_RXOFFS;
	m_adj(m, HME_RXOFFS);
	/* RX TCP/UDP checksum */
	if (ifp->if_capenable & IFCAP_RXCSUM)
		hme_rxcksum(m, flags);
	/* Pass the packet up. */
	HME_UNLOCK(sc);
	(*ifp->if_input)(ifp, m);
	HME_LOCK(sc);
}