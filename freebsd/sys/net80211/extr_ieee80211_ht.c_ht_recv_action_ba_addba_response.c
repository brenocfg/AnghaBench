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
typedef  int /*<<< orphan*/  uint16_t ;
struct TYPE_2__ {int /*<<< orphan*/  is_addba_badbawinsize; int /*<<< orphan*/  is_addba_badpolicy; int /*<<< orphan*/  is_addba_badtoken; int /*<<< orphan*/  is_addba_norequest; } ;
struct ieee80211vap {TYPE_1__ iv_stats; } ;
struct ieee80211com {int /*<<< orphan*/  (* ic_addba_response ) (struct ieee80211_node*,struct ieee80211_tx_ampdu*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
struct ieee80211_tx_ampdu {int txa_flags; int txa_token; } ;
struct ieee80211_node {int /*<<< orphan*/  ni_macaddr; struct ieee80211_tx_ampdu* ni_tx_ampdu; struct ieee80211vap* ni_vap; struct ieee80211com* ni_ic; } ;
struct ieee80211_frame {int dummy; } ;

/* Variables and functions */
 int IEEE80211_AGGR_BAWMAX ; 
 int IEEE80211_AGGR_IMMEDIATE ; 
 int IEEE80211_AGGR_XCHGPEND ; 
 int /*<<< orphan*/  IEEE80211_BAPS_BUFSIZ ; 
 int /*<<< orphan*/  IEEE80211_BAPS_POLICY ; 
 int /*<<< orphan*/  IEEE80211_BAPS_TID ; 
 int /*<<< orphan*/  IEEE80211_DISCARD_MAC (struct ieee80211vap*,int,int /*<<< orphan*/ ,char*,char*,int,int,int,...) ; 
 int IEEE80211_MSG_11N ; 
 int IEEE80211_MSG_ACTION ; 
 int /*<<< orphan*/  IEEE80211_NOTE (struct ieee80211vap*,int,struct ieee80211_node*,char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 int MS (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le16dec (int const*) ; 
 int /*<<< orphan*/  stub1 (struct ieee80211_node*,struct ieee80211_tx_ampdu*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ht_recv_action_ba_addba_response(struct ieee80211_node *ni,
	const struct ieee80211_frame *wh,
	const uint8_t *frm, const uint8_t *efrm)
{
	struct ieee80211com *ic = ni->ni_ic;
	struct ieee80211vap *vap = ni->ni_vap;
	struct ieee80211_tx_ampdu *tap;
	uint8_t dialogtoken, policy;
	uint16_t baparamset, batimeout, code;
	int tid, bufsiz;

	dialogtoken = frm[2];
	code = le16dec(frm+3);
	baparamset = le16dec(frm+5);
	tid = MS(baparamset, IEEE80211_BAPS_TID);
	bufsiz = MS(baparamset, IEEE80211_BAPS_BUFSIZ);
	policy = MS(baparamset, IEEE80211_BAPS_POLICY);
	batimeout = le16dec(frm+7);

	tap = &ni->ni_tx_ampdu[tid];
	if ((tap->txa_flags & IEEE80211_AGGR_XCHGPEND) == 0) {
		IEEE80211_DISCARD_MAC(vap,
		    IEEE80211_MSG_ACTION | IEEE80211_MSG_11N,
		    ni->ni_macaddr, "ADDBA response",
		    "no pending ADDBA, tid %d dialogtoken %u "
		    "code %d", tid, dialogtoken, code);
		vap->iv_stats.is_addba_norequest++;
		return 0;
	}
	if (dialogtoken != tap->txa_token) {
		IEEE80211_DISCARD_MAC(vap,
		    IEEE80211_MSG_ACTION | IEEE80211_MSG_11N,
		    ni->ni_macaddr, "ADDBA response",
		    "dialogtoken mismatch: waiting for %d, "
		    "received %d, tid %d code %d",
		    tap->txa_token, dialogtoken, tid, code);
		vap->iv_stats.is_addba_badtoken++;
		return 0;
	}
	/* NB: assumes IEEE80211_AGGR_IMMEDIATE is 1 */
	if (policy != (tap->txa_flags & IEEE80211_AGGR_IMMEDIATE)) {
		IEEE80211_DISCARD_MAC(vap,
		    IEEE80211_MSG_ACTION | IEEE80211_MSG_11N,
		    ni->ni_macaddr, "ADDBA response",
		    "policy mismatch: expecting %s, "
		    "received %s, tid %d code %d",
		    tap->txa_flags & IEEE80211_AGGR_IMMEDIATE,
		    policy, tid, code);
		vap->iv_stats.is_addba_badpolicy++;
		return 0;
	}
#if 0
	/* XXX we take MIN in ieee80211_addba_response */
	if (bufsiz > IEEE80211_AGGR_BAWMAX) {
		IEEE80211_DISCARD_MAC(vap,
		    IEEE80211_MSG_ACTION | IEEE80211_MSG_11N,
		    ni->ni_macaddr, "ADDBA response",
		    "BA window too large: max %d, "
		    "received %d, tid %d code %d",
		    bufsiz, IEEE80211_AGGR_BAWMAX, tid, code);
		vap->iv_stats.is_addba_badbawinsize++;
		return 0;
	}
#endif
	IEEE80211_NOTE(vap, IEEE80211_MSG_ACTION | IEEE80211_MSG_11N, ni,
	    "recv ADDBA response: dialogtoken %u code %d "
	    "baparamset 0x%x (tid %d bufsiz %d) batimeout %d",
	    dialogtoken, code, baparamset, tid, bufsiz,
	    batimeout);
	ic->ic_addba_response(ni, tap, code, baparamset, batimeout);
	return 0;
}