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
struct mbuf {int dummy; } ;
struct ifnet {int dummy; } ;
struct ieee80211vap {int /*<<< orphan*/  iv_ic; struct ifnet* iv_ifp; } ;
struct ieee80211_node {int dummy; } ;
struct ieee80211_mesh_route {int /*<<< orphan*/  rt_dest; } ;

/* Variables and functions */
 int /*<<< orphan*/  IEEE80211_TX_UNLOCK_ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IFCOUNTER_OERRORS ; 
 struct ieee80211_node* ieee80211_mesh_find_txnode (struct ieee80211vap*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_vap_pkt_send_dest (struct ieee80211vap*,struct mbuf*,struct ieee80211_node*) ; 
 int /*<<< orphan*/  if_inc_counter (struct ifnet*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  m_freem (struct mbuf*) ; 

__attribute__((used)) static void
mesh_transmit_to_gate(struct ieee80211vap *vap, struct mbuf *m,
    struct ieee80211_mesh_route *rt_gate)
{
	struct ifnet *ifp = vap->iv_ifp;
	struct ieee80211_node *ni;

	IEEE80211_TX_UNLOCK_ASSERT(vap->iv_ic);

	ni = ieee80211_mesh_find_txnode(vap, rt_gate->rt_dest);
	if (ni == NULL) {
		if_inc_counter(ifp, IFCOUNTER_OERRORS, 1);
		m_freem(m);
		return;
	}

	/*
	 * Send through the VAP packet transmit path.
	 * This consumes the node ref grabbed above and
	 * the mbuf, regardless of whether there's a problem
	 * or not.
	 */
	(void) ieee80211_vap_pkt_send_dest(vap, m, ni);
}