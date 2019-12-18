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
typedef  int uint8_t ;
typedef  int uint16_t ;
struct TYPE_4__ {int /*<<< orphan*/  is_rx_bad_auth; int /*<<< orphan*/  is_rx_auth_fail; } ;
struct ieee80211vap {scalar_t__ iv_state; int iv_flags; TYPE_2__ iv_stats; struct ieee80211_node* iv_bss; TYPE_1__* iv_acl; } ;
struct ieee80211_node {int ni_authmode; int ni_flags; int ni_noise; int /*<<< orphan*/  ni_macaddr; int /*<<< orphan*/ * ni_challenge; int /*<<< orphan*/  ni_avgrssi; struct ieee80211vap* ni_vap; } ;
struct ieee80211_frame {int /*<<< orphan*/  i_addr2; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* iac_getpolicy ) (struct ieee80211vap*) ;} ;

/* Variables and functions */
 int IEEE80211_AUTH_AUTO ; 
 int IEEE80211_AUTH_SHARED ; 
#define  IEEE80211_AUTH_SHARED_CHALLENGE 130 
#define  IEEE80211_AUTH_SHARED_REQUEST 129 
#define  IEEE80211_AUTH_SHARED_RESPONSE 128 
 int IEEE80211_CHALLENGE_LEN ; 
 int /*<<< orphan*/  IEEE80211_DISCARD_MAC (struct ieee80211vap*,int,int /*<<< orphan*/ ,char*,char*,...) ; 
 int IEEE80211_ELEMID_CHALLENGE ; 
 int /*<<< orphan*/  IEEE80211_FC0_SUBTYPE_AUTH ; 
 int IEEE80211_F_PRIVACY ; 
 int /*<<< orphan*/  IEEE80211_MACCMD_POLICY_RADIUS ; 
 int IEEE80211_MSG_ACL ; 
 int IEEE80211_MSG_AUTH ; 
 int IEEE80211_MSG_DEBUG ; 
 int IEEE80211_NODE_AREF ; 
 int IEEE80211_NODE_ASSOCID ; 
 int /*<<< orphan*/  IEEE80211_NOTE (struct ieee80211vap*,int,struct ieee80211_node*,char*,char*) ; 
 int /*<<< orphan*/  IEEE80211_NOTE_MAC (struct ieee80211vap*,int,int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  IEEE80211_RSSI_LPF (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  IEEE80211_SEND_MGMT (struct ieee80211_node*,int /*<<< orphan*/ ,int) ; 
 int IEEE80211_STATUS_ALG ; 
 int IEEE80211_STATUS_CHALLENGE ; 
 int IEEE80211_STATUS_SEQUENCE ; 
 scalar_t__ IEEE80211_S_RUN ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  get_random_bytes (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ieee80211_alloc_challenge (struct ieee80211_node*) ; 
 struct ieee80211_node* ieee80211_dup_bss (struct ieee80211vap*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_node_authorize (struct ieee80211_node*) ; 
 int /*<<< orphan*/  ieee80211_notify_node_auth (struct ieee80211_node*) ; 
 int /*<<< orphan*/  ieee80211_ref_node (struct ieee80211_node*) ; 
 int /*<<< orphan*/  ieee80211_send_error (struct ieee80211_node*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memcmp (int /*<<< orphan*/ *,int*,int) ; 
 int /*<<< orphan*/  stub1 (struct ieee80211vap*) ; 

__attribute__((used)) static void
hostap_auth_shared(struct ieee80211_node *ni, struct ieee80211_frame *wh,
    uint8_t *frm, uint8_t *efrm, int rssi, int nf,
    uint16_t seq, uint16_t status)
{
	struct ieee80211vap *vap = ni->ni_vap;
	uint8_t *challenge;
	int allocbs, estatus;

	KASSERT(vap->iv_state == IEEE80211_S_RUN, ("state %d", vap->iv_state));

	/*
	 * NB: this can happen as we allow pre-shared key
	 * authentication to be enabled w/o wep being turned
	 * on so that configuration of these can be done
	 * in any order.  It may be better to enforce the
	 * ordering in which case this check would just be
	 * for sanity/consistency.
	 */
	if ((vap->iv_flags & IEEE80211_F_PRIVACY) == 0) {
		IEEE80211_DISCARD_MAC(vap, IEEE80211_MSG_AUTH,
		    ni->ni_macaddr, "shared key auth",
		    "%s", " PRIVACY is disabled");
		estatus = IEEE80211_STATUS_ALG;
		goto bad;
	}
	/*
	 * Pre-shared key authentication is evil; accept
	 * it only if explicitly configured (it is supported
	 * mainly for compatibility with clients like Mac OS X).
	 */
	if (ni->ni_authmode != IEEE80211_AUTH_AUTO &&
	    ni->ni_authmode != IEEE80211_AUTH_SHARED) {
		IEEE80211_DISCARD_MAC(vap, IEEE80211_MSG_AUTH,
		    ni->ni_macaddr, "shared key auth",
		    "bad sta auth mode %u", ni->ni_authmode);
		vap->iv_stats.is_rx_bad_auth++;	/* XXX maybe a unique error? */
		estatus = IEEE80211_STATUS_ALG;
		goto bad;
	}

	challenge = NULL;
	if (frm + 1 < efrm) {
		if ((frm[1] + 2) > (efrm - frm)) {
			IEEE80211_DISCARD_MAC(vap, IEEE80211_MSG_AUTH,
			    ni->ni_macaddr, "shared key auth",
			    "ie %d/%d too long",
			    frm[0], (frm[1] + 2) - (efrm - frm));
			vap->iv_stats.is_rx_bad_auth++;
			estatus = IEEE80211_STATUS_CHALLENGE;
			goto bad;
		}
		if (*frm == IEEE80211_ELEMID_CHALLENGE)
			challenge = frm;
		frm += frm[1] + 2;
	}
	switch (seq) {
	case IEEE80211_AUTH_SHARED_CHALLENGE:
	case IEEE80211_AUTH_SHARED_RESPONSE:
		if (challenge == NULL) {
			IEEE80211_DISCARD_MAC(vap, IEEE80211_MSG_AUTH,
			    ni->ni_macaddr, "shared key auth",
			    "%s", "no challenge");
			vap->iv_stats.is_rx_bad_auth++;
			estatus = IEEE80211_STATUS_CHALLENGE;
			goto bad;
		}
		if (challenge[1] != IEEE80211_CHALLENGE_LEN) {
			IEEE80211_DISCARD_MAC(vap, IEEE80211_MSG_AUTH,
			    ni->ni_macaddr, "shared key auth",
			    "bad challenge len %d", challenge[1]);
			vap->iv_stats.is_rx_bad_auth++;
			estatus = IEEE80211_STATUS_CHALLENGE;
			goto bad;
		}
	default:
		break;
	}
	switch (seq) {
	case IEEE80211_AUTH_SHARED_REQUEST:
		if (ni == vap->iv_bss) {
			ni = ieee80211_dup_bss(vap, wh->i_addr2);
			if (ni == NULL) {
				/* NB: no way to return an error */
				return;
			}
			allocbs = 1;
		} else {
			if ((ni->ni_flags & IEEE80211_NODE_AREF) == 0)
				(void) ieee80211_ref_node(ni);
			allocbs = 0;
		}
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
		IEEE80211_RSSI_LPF(ni->ni_avgrssi, rssi);
		ni->ni_noise = nf;
		if (!ieee80211_alloc_challenge(ni)) {
			/* NB: don't return error so they rexmit */
			return;
		}
		get_random_bytes(ni->ni_challenge,
			IEEE80211_CHALLENGE_LEN);
		IEEE80211_NOTE(vap, IEEE80211_MSG_DEBUG | IEEE80211_MSG_AUTH,
		    ni, "shared key %sauth request", allocbs ? "" : "re");
		/*
		 * When the ACL policy is set to RADIUS we defer the
		 * authorization to a user agent.  Dispatch an event,
		 * a subsequent MLME call will decide the fate of the
		 * station.  If the user agent is not present then the
		 * node will be reclaimed due to inactivity.
		 */
		if (vap->iv_acl != NULL &&
		    vap->iv_acl->iac_getpolicy(vap) == IEEE80211_MACCMD_POLICY_RADIUS) {
			IEEE80211_NOTE_MAC(vap,
			    IEEE80211_MSG_AUTH | IEEE80211_MSG_ACL,
			    ni->ni_macaddr,
			    "%s", "station authentication defered (radius acl)");
			ieee80211_notify_node_auth(ni);
			return;
		}
		break;
	case IEEE80211_AUTH_SHARED_RESPONSE:
		if (ni == vap->iv_bss) {
			IEEE80211_DISCARD_MAC(vap, IEEE80211_MSG_AUTH,
			    ni->ni_macaddr, "shared key response",
			    "%s", "unknown station");
			/* NB: don't send a response */
			return;
		}
		if (ni->ni_challenge == NULL) {
			IEEE80211_DISCARD_MAC(vap, IEEE80211_MSG_AUTH,
			    ni->ni_macaddr, "shared key response",
			    "%s", "no challenge recorded");
			vap->iv_stats.is_rx_bad_auth++;
			estatus = IEEE80211_STATUS_CHALLENGE;
			goto bad;
		}
		if (memcmp(ni->ni_challenge, &challenge[2],
			   challenge[1]) != 0) {
			IEEE80211_DISCARD_MAC(vap, IEEE80211_MSG_AUTH,
			    ni->ni_macaddr, "shared key response",
			    "%s", "challenge mismatch");
			vap->iv_stats.is_rx_auth_fail++;
			estatus = IEEE80211_STATUS_CHALLENGE;
			goto bad;
		}
		IEEE80211_NOTE(vap, IEEE80211_MSG_DEBUG | IEEE80211_MSG_AUTH,
		    ni, "%s", "station authenticated (shared key)");
		ieee80211_node_authorize(ni);
		break;
	default:
		IEEE80211_DISCARD_MAC(vap, IEEE80211_MSG_AUTH,
		    ni->ni_macaddr, "shared key auth",
		    "bad seq %d", seq);
		vap->iv_stats.is_rx_bad_auth++;
		estatus = IEEE80211_STATUS_SEQUENCE;
		goto bad;
	}
	IEEE80211_SEND_MGMT(ni, IEEE80211_FC0_SUBTYPE_AUTH, seq + 1);
	return;
bad:
	/*
	 * Send an error response; but only when operating as an AP.
	 */
	/* XXX hack to workaround calling convention */
	ieee80211_send_error(ni, wh->i_addr2,
	    IEEE80211_FC0_SUBTYPE_AUTH,
	    (seq + 1) | (estatus<<16));
}