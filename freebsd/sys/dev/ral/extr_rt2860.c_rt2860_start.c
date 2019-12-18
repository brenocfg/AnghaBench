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
struct rt2860_softc {int sc_flags; scalar_t__ qfullmsk; int sc_tx_timer; int /*<<< orphan*/  sc_snd; int /*<<< orphan*/  data_pool; } ;
struct TYPE_3__ {scalar_t__ rcvif; } ;
struct mbuf {TYPE_1__ m_pkthdr; } ;
struct ieee80211_node {TYPE_2__* ni_vap; } ;
struct TYPE_4__ {int /*<<< orphan*/  iv_ifp; } ;

/* Variables and functions */
 int /*<<< orphan*/  IFCOUNTER_OERRORS ; 
 int /*<<< orphan*/  RAL_LOCK_ASSERT (struct rt2860_softc*) ; 
 int RT2860_RUNNING ; 
 int /*<<< orphan*/  SLIST_EMPTY (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ieee80211_free_node (struct ieee80211_node*) ; 
 int /*<<< orphan*/  if_inc_counter (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct mbuf* mbufq_dequeue (int /*<<< orphan*/ *) ; 
 scalar_t__ rt2860_tx (struct rt2860_softc*,struct mbuf*,struct ieee80211_node*) ; 

__attribute__((used)) static void
rt2860_start(struct rt2860_softc *sc)
{
	struct ieee80211_node *ni;
	struct mbuf *m;

	RAL_LOCK_ASSERT(sc);

	if ((sc->sc_flags & RT2860_RUNNING) == 0)
		return;

	while (!SLIST_EMPTY(&sc->data_pool) && sc->qfullmsk == 0 &&
	    (m = mbufq_dequeue(&sc->sc_snd)) != NULL) {
		ni = (struct ieee80211_node *)m->m_pkthdr.rcvif;
		if (rt2860_tx(sc, m, ni) != 0) {
			if_inc_counter(ni->ni_vap->iv_ifp,
			    IFCOUNTER_OERRORS, 1);
			ieee80211_free_node(ni);
			continue;
		}
		sc->sc_tx_timer = 5;
	}
}