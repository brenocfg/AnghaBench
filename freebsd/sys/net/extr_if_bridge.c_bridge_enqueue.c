#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int len; int /*<<< orphan*/  ether_vtag; } ;
struct mbuf {short m_flags; TYPE_1__ m_pkthdr; struct mbuf* m_nextpkt; } ;
struct ifnet {int if_capenable; int (* if_transmit ) (struct ifnet*,struct mbuf*) ;} ;
struct bridge_softc {struct ifnet* sc_ifp; } ;

/* Variables and functions */
 int IFCAP_VLAN_HWTAGGING ; 
 int /*<<< orphan*/  IFCOUNTER_OBYTES ; 
 int /*<<< orphan*/  IFCOUNTER_OERRORS ; 
 int /*<<< orphan*/  IFCOUNTER_OMCASTS ; 
 int /*<<< orphan*/  IFCOUNTER_OPACKETS ; 
 int /*<<< orphan*/  M_ASSERTPKTHDR (struct mbuf*) ; 
 short M_MCAST ; 
 int M_VLANTAG ; 
 struct mbuf* ether_vlanencap (struct mbuf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  if_inc_counter (struct ifnet*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  if_printf (struct ifnet*,char*) ; 
 int /*<<< orphan*/  m_freem (struct mbuf*) ; 
 int stub1 (struct ifnet*,struct mbuf*) ; 

__attribute__((used)) static int
bridge_enqueue(struct bridge_softc *sc, struct ifnet *dst_ifp, struct mbuf *m)
{
	int len, err = 0;
	short mflags;
	struct mbuf *m0;

	/* We may be sending a fragment so traverse the mbuf */
	for (; m; m = m0) {
		m0 = m->m_nextpkt;
		m->m_nextpkt = NULL;
		len = m->m_pkthdr.len;
		mflags = m->m_flags;

		/*
		 * If underlying interface can not do VLAN tag insertion itself
		 * then attach a packet tag that holds it.
		 */
		if ((m->m_flags & M_VLANTAG) &&
		    (dst_ifp->if_capenable & IFCAP_VLAN_HWTAGGING) == 0) {
			m = ether_vlanencap(m, m->m_pkthdr.ether_vtag);
			if (m == NULL) {
				if_printf(dst_ifp,
				    "unable to prepend VLAN header\n");
				if_inc_counter(dst_ifp, IFCOUNTER_OERRORS, 1);
				continue;
			}
			m->m_flags &= ~M_VLANTAG;
		}

		M_ASSERTPKTHDR(m); /* We shouldn't transmit mbuf without pkthdr */
		if ((err = dst_ifp->if_transmit(dst_ifp, m))) {
			m_freem(m0);
			if_inc_counter(sc->sc_ifp, IFCOUNTER_OERRORS, 1);
			break;
		}

		if_inc_counter(sc->sc_ifp, IFCOUNTER_OPACKETS, 1);
		if_inc_counter(sc->sc_ifp, IFCOUNTER_OBYTES, len);
		if (mflags & M_MCAST)
			if_inc_counter(sc->sc_ifp, IFCOUNTER_OMCASTS, 1);
	}

	return (err);
}