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
struct TYPE_4__ {scalar_t__ rcvif; } ;
struct mbuf {TYPE_2__ m_pkthdr; } ;
struct ipw_softc {scalar_t__ txfree; int sc_tx_timer; int /*<<< orphan*/  sc_snd; } ;
struct ieee80211_node {TYPE_1__* ni_vap; } ;
struct TYPE_3__ {int /*<<< orphan*/  iv_ifp; } ;

/* Variables and functions */
 int /*<<< orphan*/  IFCOUNTER_OERRORS ; 
 int /*<<< orphan*/  IPW_LOCK_ASSERT (struct ipw_softc*) ; 
 scalar_t__ IPW_MAX_NSEG ; 
 int /*<<< orphan*/  ieee80211_free_node (struct ieee80211_node*) ; 
 int /*<<< orphan*/  if_inc_counter (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ ipw_tx_start (struct ipw_softc*,struct mbuf*,struct ieee80211_node*) ; 
 struct mbuf* mbufq_dequeue (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
ipw_start(struct ipw_softc *sc)
{
	struct ieee80211_node *ni;
	struct mbuf *m;

	IPW_LOCK_ASSERT(sc);

	while (sc->txfree >= 1 + IPW_MAX_NSEG &&
	    (m = mbufq_dequeue(&sc->sc_snd)) != NULL) {
		ni = (struct ieee80211_node *) m->m_pkthdr.rcvif;
		if (ipw_tx_start(sc, m, ni) != 0) {
			if_inc_counter(ni->ni_vap->iv_ifp,
			    IFCOUNTER_OERRORS, 1);
			ieee80211_free_node(ni);
			break;
		}
		/* start watchdog timer */
		sc->sc_tx_timer = 5;
	}
}