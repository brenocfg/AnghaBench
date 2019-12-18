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
struct TYPE_2__ {scalar_t__ rcvif; } ;
struct mbuf {TYPE_1__ m_pkthdr; } ;
struct iwm_softc {int /*<<< orphan*/  sc_snd; } ;
struct ieee80211_node {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ieee80211_free_node (struct ieee80211_node*) ; 
 int /*<<< orphan*/  m_freem (struct mbuf*) ; 
 struct mbuf* mbufq_dequeue (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
iwm_xmit_queue_drain(struct iwm_softc *sc)
{
	struct mbuf *m;
	struct ieee80211_node *ni;

	while ((m = mbufq_dequeue(&sc->sc_snd)) != NULL) {
		ni = (struct ieee80211_node *)m->m_pkthdr.rcvif;
		ieee80211_free_node(ni);
		m_freem(m);
	}
}