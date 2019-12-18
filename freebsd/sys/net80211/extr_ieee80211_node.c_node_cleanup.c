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
struct ieee80211vap {scalar_t__ iv_opmode; int /*<<< orphan*/  (* iv_set_tim ) (struct ieee80211_node*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  iv_ps_sta; } ;
struct ieee80211com {int /*<<< orphan*/  ic_stageq; } ;
struct ieee80211_node {int ni_flags; int /*<<< orphan*/ ** ni_rxfrag; int /*<<< orphan*/ * ni_challenge; scalar_t__ ni_associd; struct ieee80211com* ni_ic; struct ieee80211vap* ni_vap; } ;

/* Variables and functions */
 int /*<<< orphan*/  IEEE80211_FREE (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IEEE80211_MSG_POWER ; 
 scalar_t__ IEEE80211_M_MBSS ; 
 scalar_t__ IEEE80211_M_STA ; 
 int IEEE80211_NODE_AREF ; 
 int IEEE80211_NODE_ASSOCID ; 
 int IEEE80211_NODE_HT ; 
 int IEEE80211_NODE_PWR_MGT ; 
 int IEEE80211_NODE_VHT ; 
 int /*<<< orphan*/  IEEE80211_NOTE (struct ieee80211vap*,int /*<<< orphan*/ ,struct ieee80211_node*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  M_80211_NODE ; 
 int /*<<< orphan*/  ieee80211_ageq_drain_node (int /*<<< orphan*/ *,struct ieee80211_node*) ; 
 int /*<<< orphan*/  ieee80211_ff_node_cleanup (struct ieee80211_node*) ; 
 int /*<<< orphan*/  ieee80211_ht_node_cleanup (struct ieee80211_node*) ; 
 int /*<<< orphan*/  ieee80211_mesh_node_cleanup (struct ieee80211_node*) ; 
 int /*<<< orphan*/  ieee80211_node_delucastkey (struct ieee80211_node*) ; 
 scalar_t__ ieee80211_node_psq_drain (struct ieee80211_node*) ; 
 int /*<<< orphan*/  ieee80211_vht_node_cleanup (struct ieee80211_node*) ; 
 int /*<<< orphan*/  m_freem (int /*<<< orphan*/ *) ; 
 int nitems (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  stub1 (struct ieee80211_node*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
node_cleanup(struct ieee80211_node *ni)
{
	struct ieee80211vap *vap = ni->ni_vap;
	struct ieee80211com *ic = ni->ni_ic;
	int i;

	/* NB: preserve ni_table */
	if (ni->ni_flags & IEEE80211_NODE_PWR_MGT) {
		if (vap->iv_opmode != IEEE80211_M_STA)
			vap->iv_ps_sta--;
		ni->ni_flags &= ~IEEE80211_NODE_PWR_MGT;
		IEEE80211_NOTE(vap, IEEE80211_MSG_POWER, ni,
		    "power save mode off, %u sta's in ps mode", vap->iv_ps_sta);
	}
	/*
	 * Cleanup any VHT and HT-related state.
	 */
	if (ni->ni_flags & IEEE80211_NODE_VHT)
		ieee80211_vht_node_cleanup(ni);
	if (ni->ni_flags & IEEE80211_NODE_HT)
		ieee80211_ht_node_cleanup(ni);
#ifdef IEEE80211_SUPPORT_SUPERG
	/* Always do FF node cleanup; for A-MSDU */
	ieee80211_ff_node_cleanup(ni);
#endif
#ifdef IEEE80211_SUPPORT_MESH
	/*
	 * Cleanup any mesh-related state.
	 */
	if (vap->iv_opmode == IEEE80211_M_MBSS)
		ieee80211_mesh_node_cleanup(ni);
#endif
	/*
	 * Clear any staging queue entries.
	 */
	ieee80211_ageq_drain_node(&ic->ic_stageq, ni);

	/*
	 * Clear AREF flag that marks the authorization refcnt bump
	 * has happened.  This is probably not needed as the node
	 * should always be removed from the table so not found but
	 * do it just in case.
	 * Likewise clear the ASSOCID flag as these flags are intended
	 * to be managed in tandem.
	 */
	ni->ni_flags &= ~(IEEE80211_NODE_AREF | IEEE80211_NODE_ASSOCID);

	/*
	 * Drain power save queue and, if needed, clear TIM.
	 */
	if (ieee80211_node_psq_drain(ni) != 0 && vap->iv_set_tim != NULL)
		vap->iv_set_tim(ni, 0);

	ni->ni_associd = 0;
	if (ni->ni_challenge != NULL) {
		IEEE80211_FREE(ni->ni_challenge, M_80211_NODE);
		ni->ni_challenge = NULL;
	}
	/*
	 * Preserve SSID, WPA, and WME ie's so the bss node is
	 * reusable during a re-auth/re-assoc state transition.
	 * If we remove these data they will not be recreated
	 * because they come from a probe-response or beacon frame
	 * which cannot be expected prior to the association-response.
	 * This should not be an issue when operating in other modes
	 * as stations leaving always go through a full state transition
	 * which will rebuild this state.
	 *
	 * XXX does this leave us open to inheriting old state?
	 */
	for (i = 0; i < nitems(ni->ni_rxfrag); i++)
		if (ni->ni_rxfrag[i] != NULL) {
			m_freem(ni->ni_rxfrag[i]);
			ni->ni_rxfrag[i] = NULL;
		}
	/*
	 * Must be careful here to remove any key map entry w/o a LOR.
	 */
	ieee80211_node_delucastkey(ni);
}