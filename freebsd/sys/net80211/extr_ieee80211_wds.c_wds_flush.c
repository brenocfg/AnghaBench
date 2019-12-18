#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct mbuf {struct mbuf* m_nextpkt; } ;
struct ieee80211com {int /*<<< orphan*/  (* ic_node_getsignal ) (struct ieee80211_node*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;int /*<<< orphan*/  ic_stageq; } ;
struct ieee80211_node {int /*<<< orphan*/  ni_vap; int /*<<< orphan*/  ni_macaddr; struct ieee80211com* ni_ic; } ;
typedef  int /*<<< orphan*/  int8_t ;

/* Variables and functions */
 int /*<<< orphan*/  IEEE80211_MSG_WDS ; 
 int /*<<< orphan*/  IEEE80211_NOTE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ieee80211_node*,char*,char*) ; 
 struct mbuf* ieee80211_ageq_remove (int /*<<< orphan*/ *,void*) ; 
 int /*<<< orphan*/  ieee80211_input (struct ieee80211_node*,struct mbuf*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ieee80211_mac_hash (struct ieee80211com*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct ieee80211_node*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
wds_flush(struct ieee80211_node *ni)
{
	struct ieee80211com *ic = ni->ni_ic;
	struct mbuf *m, *next;
	int8_t rssi, nf;

	m = ieee80211_ageq_remove(&ic->ic_stageq,
	    (void *)(uintptr_t) ieee80211_mac_hash(ic, ni->ni_macaddr));
	if (m == NULL)
		return;

	IEEE80211_NOTE(ni->ni_vap, IEEE80211_MSG_WDS, ni,
	    "%s", "flush wds queue");
	ic->ic_node_getsignal(ni, &rssi, &nf);
	for (; m != NULL; m = next) {
		next = m->m_nextpkt;
		m->m_nextpkt = NULL;
		ieee80211_input(ni, m, rssi, nf);
	}
}