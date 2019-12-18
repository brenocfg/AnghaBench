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
typedef  int uint16_t ;
struct TYPE_3__ {int /*<<< orphan*/  is_rx_bad_auth; } ;
struct ieee80211vap {scalar_t__ iv_state; TYPE_2__* iv_acl; struct ieee80211_node* iv_bss; TYPE_1__ iv_stats; } ;
struct ieee80211_node {scalar_t__ ni_authmode; int ni_flags; int /*<<< orphan*/  ni_macaddr; int /*<<< orphan*/ * ni_challenge; struct ieee80211vap* ni_vap; } ;
struct ieee80211_frame {int /*<<< orphan*/  i_addr2; } ;
struct TYPE_4__ {scalar_t__ (* iac_getpolicy ) (struct ieee80211vap*) ;} ;

/* Variables and functions */
 scalar_t__ IEEE80211_AUTH_8021X ; 
 int IEEE80211_AUTH_OPEN_REQUEST ; 
 scalar_t__ IEEE80211_AUTH_SHARED ; 
 int /*<<< orphan*/  IEEE80211_DISCARD_MAC (struct ieee80211vap*,int,int /*<<< orphan*/ ,char*,char*,scalar_t__) ; 
 int /*<<< orphan*/  IEEE80211_FC0_SUBTYPE_AUTH ; 
 int /*<<< orphan*/  IEEE80211_FREE (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ IEEE80211_MACCMD_POLICY_RADIUS ; 
 int IEEE80211_MSG_ACL ; 
 int IEEE80211_MSG_AUTH ; 
 int IEEE80211_MSG_DEBUG ; 
 int IEEE80211_NODE_AREF ; 
 int IEEE80211_NODE_ASSOCID ; 
 int /*<<< orphan*/  IEEE80211_NOTE_MAC (struct ieee80211vap*,int,int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  IEEE80211_SEND_MGMT (struct ieee80211_node*,int /*<<< orphan*/ ,int) ; 
 int IEEE80211_STATUS_ALG ; 
 scalar_t__ IEEE80211_S_RUN ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  M_80211_NODE ; 
 struct ieee80211_node* ieee80211_dup_bss (struct ieee80211vap*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_node_authorize (struct ieee80211_node*) ; 
 int /*<<< orphan*/  ieee80211_notify_node_auth (struct ieee80211_node*) ; 
 int /*<<< orphan*/  ieee80211_ref_node (struct ieee80211_node*) ; 
 int /*<<< orphan*/  ieee80211_send_error (struct ieee80211_node*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ stub1 (struct ieee80211vap*) ; 

__attribute__((used)) static void
hostap_auth_open(struct ieee80211_node *ni, struct ieee80211_frame *wh,
    int rssi, int nf, uint16_t seq, uint16_t status)
{
	struct ieee80211vap *vap = ni->ni_vap;

	KASSERT(vap->iv_state == IEEE80211_S_RUN, ("state %d", vap->iv_state));

	if (ni->ni_authmode == IEEE80211_AUTH_SHARED) {
		IEEE80211_DISCARD_MAC(vap, IEEE80211_MSG_AUTH,
		    ni->ni_macaddr, "open auth",
		    "bad sta auth mode %u", ni->ni_authmode);
		vap->iv_stats.is_rx_bad_auth++;	/* XXX */
		/*
		 * Clear any challenge text that may be there if
		 * a previous shared key auth failed and then an
		 * open auth is attempted.
		 */
		if (ni->ni_challenge != NULL) {
			IEEE80211_FREE(ni->ni_challenge, M_80211_NODE);
			ni->ni_challenge = NULL;
		}
		/* XXX hack to workaround calling convention */
		ieee80211_send_error(ni, wh->i_addr2, 
		    IEEE80211_FC0_SUBTYPE_AUTH,
		    (seq + 1) | (IEEE80211_STATUS_ALG<<16));
		return;
	}
	if (seq != IEEE80211_AUTH_OPEN_REQUEST) {
		vap->iv_stats.is_rx_bad_auth++;
		return;
	}
	/* always accept open authentication requests */
	if (ni == vap->iv_bss) {
		ni = ieee80211_dup_bss(vap, wh->i_addr2);
		if (ni == NULL)
			return;
	} else if ((ni->ni_flags & IEEE80211_NODE_AREF) == 0)
		(void) ieee80211_ref_node(ni);
	/*
	 * Mark the node as referenced to reflect that it's
	 * reference count has been bumped to insure it remains
	 * after the transaction completes.
	 */
	ni->ni_flags |= IEEE80211_NODE_AREF;
	/*
	 * Mark the node as requiring a valid association id
	 * before outbound traffic is permitted.
	 */
	ni->ni_flags |= IEEE80211_NODE_ASSOCID;

	if (vap->iv_acl != NULL &&
	    vap->iv_acl->iac_getpolicy(vap) == IEEE80211_MACCMD_POLICY_RADIUS) {
		/*
		 * When the ACL policy is set to RADIUS we defer the
		 * authorization to a user agent.  Dispatch an event,
		 * a subsequent MLME call will decide the fate of the
		 * station.  If the user agent is not present then the
		 * node will be reclaimed due to inactivity.
		 */
		IEEE80211_NOTE_MAC(vap,
		    IEEE80211_MSG_AUTH | IEEE80211_MSG_ACL, ni->ni_macaddr,
		    "%s", "station authentication defered (radius acl)");
		ieee80211_notify_node_auth(ni);
	} else {
		IEEE80211_SEND_MGMT(ni, IEEE80211_FC0_SUBTYPE_AUTH, seq + 1);
		IEEE80211_NOTE_MAC(vap,
		    IEEE80211_MSG_DEBUG | IEEE80211_MSG_AUTH, ni->ni_macaddr,
		    "%s", "station authenticated (open)");
		/*
		 * When 802.1x is not in use mark the port
		 * authorized at this point so traffic can flow.
		 */
		if (ni->ni_authmode != IEEE80211_AUTH_8021X)
			ieee80211_node_authorize(ni);
	}
}