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
struct mbuf {struct mbuf* m_nextpkt; TYPE_1__ m_pkthdr; } ;
struct ifqueue {struct mbuf* ifq_tail; struct mbuf* ifq_head; int /*<<< orphan*/  ifq_len; } ;
struct ieee80211vap {int dummy; } ;
struct ieee80211_node {struct ieee80211vap* ni_vap; } ;

/* Variables and functions */
 int /*<<< orphan*/  IF_LOCK (struct ifqueue*) ; 
 int /*<<< orphan*/  IF_UNLOCK (struct ifqueue*) ; 
 int /*<<< orphan*/  ieee80211_free_node (struct ieee80211_node*) ; 
 int /*<<< orphan*/  m_freem (struct mbuf*) ; 

void
ieee80211_flush_ifq(struct ifqueue *ifq, struct ieee80211vap *vap)
{
	struct ieee80211_node *ni;
	struct mbuf *m, **mprev;

	IF_LOCK(ifq);
	mprev = &ifq->ifq_head;
	while ((m = *mprev) != NULL) {
		ni = (struct ieee80211_node *)m->m_pkthdr.rcvif;
		if (ni != NULL && ni->ni_vap == vap) {
			*mprev = m->m_nextpkt;		/* remove from list */
			ifq->ifq_len--;

			m_freem(m);
			ieee80211_free_node(ni);	/* reclaim ref */
		} else
			mprev = &m->m_nextpkt;
	}
	/* recalculate tail ptr */
	m = ifq->ifq_head;
	for (; m != NULL && m->m_nextpkt != NULL; m = m->m_nextpkt)
		;
	ifq->ifq_tail = m;
	IF_UNLOCK(ifq);
}