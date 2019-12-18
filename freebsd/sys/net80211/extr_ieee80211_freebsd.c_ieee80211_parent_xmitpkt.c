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
struct TYPE_3__ {scalar_t__ rcvif; } ;
struct mbuf {TYPE_1__ m_pkthdr; } ;
struct ieee80211com {int (* ic_transmit ) (struct ieee80211com*,struct mbuf*) ;} ;
struct ieee80211_node {TYPE_2__* ni_vap; } ;
struct TYPE_4__ {int /*<<< orphan*/  iv_ifp; } ;

/* Variables and functions */
 int /*<<< orphan*/  IEEE80211_TX_LOCK_ASSERT (struct ieee80211com*) ; 
 int /*<<< orphan*/  IFCOUNTER_OERRORS ; 
 int /*<<< orphan*/  ieee80211_free_mbuf (struct mbuf*) ; 
 int /*<<< orphan*/  ieee80211_free_node (struct ieee80211_node*) ; 
 int /*<<< orphan*/  if_inc_counter (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int stub1 (struct ieee80211com*,struct mbuf*) ; 

int
ieee80211_parent_xmitpkt(struct ieee80211com *ic, struct mbuf *m)
{
	int error;

	/*
	 * Assert the IC TX lock is held - this enforces the
	 * processing -> queuing order is maintained
	 */
	IEEE80211_TX_LOCK_ASSERT(ic);
	error = ic->ic_transmit(ic, m);
	if (error) {
		struct ieee80211_node *ni;

		ni = (struct ieee80211_node *)m->m_pkthdr.rcvif;

		/* XXX number of fragments */
		if_inc_counter(ni->ni_vap->iv_ifp, IFCOUNTER_OERRORS, 1);
		ieee80211_free_node(ni);
		ieee80211_free_mbuf(m);
	}
	return (error);
}