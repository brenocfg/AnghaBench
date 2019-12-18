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
typedef  int uint8_t ;
typedef  int uint16_t ;
struct TYPE_2__ {int is_rx_authfail_code; int /*<<< orphan*/  is_rx_bad_auth; int /*<<< orphan*/  is_rx_auth_fail; } ;
struct ieee80211vap {int iv_flags; scalar_t__ iv_state; TYPE_1__ iv_stats; } ;
struct ieee80211_node {int ni_authmode; int /*<<< orphan*/ * ni_challenge; int /*<<< orphan*/  ni_macaddr; struct ieee80211vap* ni_vap; } ;
struct ieee80211_frame {int dummy; } ;

/* Variables and functions */
 int IEEE80211_AUTH_AUTO ; 
 int IEEE80211_AUTH_SHARED ; 
#define  IEEE80211_AUTH_SHARED_CHALLENGE 130 
#define  IEEE80211_AUTH_SHARED_PASS 129 
#define  IEEE80211_AUTH_SHARED_RESPONSE 128 
 int IEEE80211_CHALLENGE_LEN ; 
 int /*<<< orphan*/  IEEE80211_DISCARD (struct ieee80211vap*,int,struct ieee80211_frame*,char*,char*,int) ; 
 int /*<<< orphan*/  IEEE80211_DISCARD_MAC (struct ieee80211vap*,int,int /*<<< orphan*/ ,char*,char*,...) ; 
 int IEEE80211_ELEMID_CHALLENGE ; 
 int /*<<< orphan*/  IEEE80211_FC0_SUBTYPE_AUTH ; 
 int /*<<< orphan*/  IEEE80211_FREE (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int IEEE80211_F_PRIVACY ; 
 int IEEE80211_MSG_AUTH ; 
 int IEEE80211_MSG_DEBUG ; 
 int /*<<< orphan*/  IEEE80211_NOTE_FRAME (struct ieee80211vap*,int,struct ieee80211_frame*,char*,int) ; 
 int /*<<< orphan*/  IEEE80211_SCAN_FAIL_STATUS ; 
 int /*<<< orphan*/  IEEE80211_SEND_MGMT (struct ieee80211_node*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  IEEE80211_S_ASSOC ; 
 scalar_t__ IEEE80211_S_AUTH ; 
 int /*<<< orphan*/  IEEE80211_S_SCAN ; 
 int /*<<< orphan*/  M_80211_NODE ; 
 int /*<<< orphan*/  ieee80211_alloc_challenge (struct ieee80211_node*) ; 
 int /*<<< orphan*/  ieee80211_new_state (struct ieee80211vap*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int*,int) ; 

__attribute__((used)) static void
sta_auth_shared(struct ieee80211_node *ni, struct ieee80211_frame *wh,
    uint8_t *frm, uint8_t *efrm, int rssi, int nf,
    uint16_t seq, uint16_t status)
{
	struct ieee80211vap *vap = ni->ni_vap;
	uint8_t *challenge;

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
		goto bad;
	}
	/*
	 * Pre-shared key authentication is evil; accept
	 * it only if explicitly configured (it is supported
	 * mainly for compatibility with clients like OS X).
	 */
	if (ni->ni_authmode != IEEE80211_AUTH_AUTO &&
	    ni->ni_authmode != IEEE80211_AUTH_SHARED) {
		IEEE80211_DISCARD_MAC(vap, IEEE80211_MSG_AUTH,
		    ni->ni_macaddr, "shared key auth",
		    "bad sta auth mode %u", ni->ni_authmode);
		vap->iv_stats.is_rx_bad_auth++;	/* XXX maybe a unique error? */
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
			goto bad;
		}
		if (challenge[1] != IEEE80211_CHALLENGE_LEN) {
			IEEE80211_DISCARD_MAC(vap, IEEE80211_MSG_AUTH,
			    ni->ni_macaddr, "shared key auth",
			    "bad challenge len %d", challenge[1]);
			vap->iv_stats.is_rx_bad_auth++;
			goto bad;
		}
	default:
		break;
	}
	if (vap->iv_state != IEEE80211_S_AUTH)
		return;
	switch (seq) {
	case IEEE80211_AUTH_SHARED_PASS:
		if (ni->ni_challenge != NULL) {
			IEEE80211_FREE(ni->ni_challenge, M_80211_NODE);
			ni->ni_challenge = NULL;
		}
		if (status != 0) {
			IEEE80211_NOTE_FRAME(vap,
			    IEEE80211_MSG_DEBUG | IEEE80211_MSG_AUTH, wh,
			    "shared key auth failed (reason %d)", status);
			vap->iv_stats.is_rx_auth_fail++;
			vap->iv_stats.is_rx_authfail_code = status;
			return;
		}
		ieee80211_new_state(vap, IEEE80211_S_ASSOC, 0);
		break;
	case IEEE80211_AUTH_SHARED_CHALLENGE:
		if (!ieee80211_alloc_challenge(ni))
			return;
		/* XXX could optimize by passing recvd challenge */
		memcpy(ni->ni_challenge, &challenge[2], challenge[1]);
		IEEE80211_SEND_MGMT(ni,
			IEEE80211_FC0_SUBTYPE_AUTH, seq + 1);
		break;
	default:
		IEEE80211_DISCARD(vap, IEEE80211_MSG_AUTH,
		    wh, "shared key auth", "bad seq %d", seq);
		vap->iv_stats.is_rx_bad_auth++;
		return;
	}
	return;
bad:
	/*
	 * Kick the state machine.  This short-circuits
	 * using the mgt frame timeout to trigger the
	 * state transition.
	 */
	if (vap->iv_state == IEEE80211_S_AUTH)
		ieee80211_new_state(vap, IEEE80211_S_SCAN,
		    IEEE80211_SCAN_FAIL_STATUS);
}