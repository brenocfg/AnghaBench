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
struct TYPE_2__ {struct ifnet* rcvif; } ;
struct mbuf {TYPE_1__ m_pkthdr; } ;
struct lagg_softc {struct lagg_port* sc_primary; struct ifnet* sc_ifp; } ;
struct lagg_port {int dummy; } ;
struct ifnet {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  LAGG_PORTACTIVE (struct lagg_port*) ; 
 scalar_t__ V_lagg_failover_rx_all ; 
 struct lagg_port* lagg_link_active (struct lagg_softc*,struct lagg_port*) ; 
 int /*<<< orphan*/  m_freem (struct mbuf*) ; 

__attribute__((used)) static struct mbuf *
lagg_fail_input(struct lagg_softc *sc, struct lagg_port *lp, struct mbuf *m)
{
	struct ifnet *ifp = sc->sc_ifp;
	struct lagg_port *tmp_tp;

	if (lp == sc->sc_primary || V_lagg_failover_rx_all) {
		m->m_pkthdr.rcvif = ifp;
		return (m);
	}

	if (!LAGG_PORTACTIVE(sc->sc_primary)) {
		tmp_tp = lagg_link_active(sc, sc->sc_primary);
		/*
		 * If tmp_tp is null, we've received a packet when all
		 * our links are down. Weird, but process it anyways.
		 */
		if ((tmp_tp == NULL || tmp_tp == lp)) {
			m->m_pkthdr.rcvif = ifp;
			return (m);
		}
	}

	m_freem(m);
	return (NULL);
}