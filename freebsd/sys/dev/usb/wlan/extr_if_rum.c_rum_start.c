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
struct rum_softc {scalar_t__ tx_nfree; int /*<<< orphan*/  sc_snd; int /*<<< orphan*/  sc_running; } ;
struct TYPE_4__ {scalar_t__ rcvif; } ;
struct mbuf {TYPE_2__ m_pkthdr; } ;
struct ieee80211_node {TYPE_1__* ni_vap; } ;
struct TYPE_3__ {int /*<<< orphan*/  iv_ifp; } ;

/* Variables and functions */
 int /*<<< orphan*/  IFCOUNTER_OERRORS ; 
 int /*<<< orphan*/  RUM_LOCK_ASSERT (struct rum_softc*) ; 
 scalar_t__ RUM_TX_MINFREE ; 
 int /*<<< orphan*/  ieee80211_free_node (struct ieee80211_node*) ; 
 int /*<<< orphan*/  if_inc_counter (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct mbuf* mbufq_dequeue (int /*<<< orphan*/ *) ; 
 scalar_t__ rum_tx_data (struct rum_softc*,struct mbuf*,struct ieee80211_node*) ; 

__attribute__((used)) static void
rum_start(struct rum_softc *sc)
{
	struct ieee80211_node *ni;
	struct mbuf *m;

	RUM_LOCK_ASSERT(sc);

	if (!sc->sc_running)
		return;

	while (sc->tx_nfree >= RUM_TX_MINFREE &&
	    (m = mbufq_dequeue(&sc->sc_snd)) != NULL) {
		ni = (struct ieee80211_node *) m->m_pkthdr.rcvif;
		if (rum_tx_data(sc, m, ni) != 0) {
			if_inc_counter(ni->ni_vap->iv_ifp,
			    IFCOUNTER_OERRORS, 1);
			ieee80211_free_node(ni);
			break;
		}
	}
}