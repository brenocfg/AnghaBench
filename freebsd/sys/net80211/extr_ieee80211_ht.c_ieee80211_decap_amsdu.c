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
struct TYPE_3__ {int len; } ;
struct mbuf {TYPE_1__ m_pkthdr; } ;
struct TYPE_4__ {int /*<<< orphan*/  is_amsdu_split; int /*<<< orphan*/  is_amsdu_tooshort; int /*<<< orphan*/  is_amsdu_decap; } ;
struct ieee80211vap {int /*<<< orphan*/  (* iv_deliver_data ) (struct ieee80211vap*,struct ieee80211_node*,struct mbuf*) ;TYPE_2__ iv_stats; } ;
struct ieee80211_node {int /*<<< orphan*/  ni_macaddr; struct ieee80211vap* ni_vap; } ;
struct ether_header {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IEEE80211_DISCARD_MAC (struct ieee80211vap*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*,char*) ; 
 int /*<<< orphan*/  IEEE80211_MSG_ANY ; 
 int /*<<< orphan*/  M_NOWAIT ; 
 struct mbuf* ieee80211_decap1 (struct mbuf*,int*) ; 
 int /*<<< orphan*/  m_adj (struct mbuf*,int) ; 
 int /*<<< orphan*/  m_freem (struct mbuf*) ; 
 struct mbuf* m_split (struct mbuf*,int,int /*<<< orphan*/ ) ; 
 int roundup2 (int,int) ; 
 int /*<<< orphan*/  stub1 (struct ieee80211vap*,struct ieee80211_node*,struct mbuf*) ; 

struct mbuf *
ieee80211_decap_amsdu(struct ieee80211_node *ni, struct mbuf *m)
{
	struct ieee80211vap *vap = ni->ni_vap;
	int framelen;
	struct mbuf *n;

	/* discard 802.3 header inserted by ieee80211_decap */
	m_adj(m, sizeof(struct ether_header));

	vap->iv_stats.is_amsdu_decap++;

	for (;;) {
		/*
		 * Decap the first frame, bust it apart from the
		 * remainder and deliver.  We leave the last frame
		 * delivery to the caller (for consistency with other
		 * code paths, could also do it here).
		 */
		m = ieee80211_decap1(m, &framelen);
		if (m == NULL) {
			IEEE80211_DISCARD_MAC(vap, IEEE80211_MSG_ANY,
			    ni->ni_macaddr, "a-msdu", "%s", "decap failed");
			vap->iv_stats.is_amsdu_tooshort++;
			return NULL;
		}
		if (m->m_pkthdr.len == framelen)
			break;
		n = m_split(m, framelen, M_NOWAIT);
		if (n == NULL) {
			IEEE80211_DISCARD_MAC(vap, IEEE80211_MSG_ANY,
			    ni->ni_macaddr, "a-msdu",
			    "%s", "unable to split encapsulated frames");
			vap->iv_stats.is_amsdu_split++;
			m_freem(m);			/* NB: must reclaim */
			return NULL;
		}
		vap->iv_deliver_data(vap, ni, m);

		/*
		 * Remove frame contents; each intermediate frame
		 * is required to be aligned to a 4-byte boundary.
		 */
		m = n;
		m_adj(m, roundup2(framelen, 4) - framelen);	/* padding */
	}
	return m;				/* last delivered by caller */
}