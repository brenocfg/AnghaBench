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
struct TYPE_4__ {int csum_flags; TYPE_1__* snd_tag; } ;
struct mbuf {TYPE_2__ m_pkthdr; } ;
struct lagg_softc {scalar_t__ sc_proto; scalar_t__ sc_count; } ;
struct ifnet {scalar_t__ if_softc; } ;
struct TYPE_3__ {struct ifnet* ifp; } ;

/* Variables and functions */
 int CSUM_SND_TAG ; 
 int ENXIO ; 
 int /*<<< orphan*/  ETHER_BPF_MTAP (struct ifnet*,struct mbuf*) ; 
 int /*<<< orphan*/  IFCOUNTER_OERRORS ; 
 scalar_t__ LAGG_PROTO_NONE ; 
 int /*<<< orphan*/  LAGG_RLOCK () ; 
 int /*<<< orphan*/  LAGG_RUNLOCK () ; 
 int /*<<< orphan*/  MPASS (int) ; 
 int /*<<< orphan*/  if_inc_counter (struct ifnet*,int /*<<< orphan*/ ,int) ; 
 int lagg_proto_start (struct lagg_softc*,struct mbuf*) ; 
 int /*<<< orphan*/  m_freem (struct mbuf*) ; 

__attribute__((used)) static int
lagg_transmit(struct ifnet *ifp, struct mbuf *m)
{
	struct lagg_softc *sc = (struct lagg_softc *)ifp->if_softc;
	int error;

#if defined(KERN_TLS) || defined(RATELIMIT)
	if (m->m_pkthdr.csum_flags & CSUM_SND_TAG)
		MPASS(m->m_pkthdr.snd_tag->ifp == ifp);
#endif
	LAGG_RLOCK();
	/* We need a Tx algorithm and at least one port */
	if (sc->sc_proto == LAGG_PROTO_NONE || sc->sc_count == 0) {
		LAGG_RUNLOCK();
		m_freem(m);
		if_inc_counter(ifp, IFCOUNTER_OERRORS, 1);
		return (ENXIO);
	}

	ETHER_BPF_MTAP(ifp, m);

	error = lagg_proto_start(sc, m);
	LAGG_RUNLOCK();

	if (error != 0)
		if_inc_counter(ifp, IFCOUNTER_OERRORS, 1);

	return (error);
}