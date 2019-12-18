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
struct TYPE_2__ {int /*<<< orphan*/  is_addba_reject; } ;
struct ieee80211vap {int iv_flags_ht; TYPE_1__ iv_stats; } ;
struct ieee80211com {int /*<<< orphan*/  (* ic_send_action ) (struct ieee80211_node*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ;int /*<<< orphan*/  (* ic_ampdu_rx_start ) (struct ieee80211_node*,struct ieee80211_rx_ampdu*,int,int,int) ;} ;
struct ieee80211_rx_ampdu {int rxa_wnd; } ;
struct ieee80211_node {int ni_flags; struct ieee80211_rx_ampdu* ni_rx_ampdu; struct ieee80211vap* ni_vap; struct ieee80211com* ni_ic; } ;
struct ieee80211_frame {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IEEE80211_ACTION_BA_ADDBA_RESPONSE ; 
 int /*<<< orphan*/  IEEE80211_ACTION_CAT_BA ; 
 int /*<<< orphan*/  IEEE80211_BAPS_BUFSIZ ; 
 int IEEE80211_BAPS_POLICY_IMMEDIATE ; 
 int /*<<< orphan*/  IEEE80211_BAPS_TID ; 
 int /*<<< orphan*/  IEEE80211_BASEQ_FRAG ; 
 int /*<<< orphan*/  IEEE80211_BASEQ_START ; 
 int IEEE80211_FHT_AMPDU_RX ; 
 int IEEE80211_MSG_11N ; 
 int IEEE80211_MSG_ACTION ; 
 int IEEE80211_NODE_AMPDU_RX ; 
 int /*<<< orphan*/  IEEE80211_NOTE (struct ieee80211vap*,int,struct ieee80211_node*,char*,...) ; 
 int IEEE80211_STATUS_SUCCESS ; 
 int IEEE80211_STATUS_UNSPECIFIED ; 
 int MS (int,int /*<<< orphan*/ ) ; 
 int SM (int,int /*<<< orphan*/ ) ; 
 int le16dec (int const*) ; 
 int /*<<< orphan*/  stub1 (struct ieee80211_node*,struct ieee80211_rx_ampdu*,int,int,int) ; 
 int /*<<< orphan*/  stub2 (struct ieee80211_node*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static int
ht_recv_action_ba_addba_request(struct ieee80211_node *ni,
	const struct ieee80211_frame *wh,
	const uint8_t *frm, const uint8_t *efrm)
{
	struct ieee80211com *ic = ni->ni_ic;
	struct ieee80211vap *vap = ni->ni_vap;
	struct ieee80211_rx_ampdu *rap;
	uint8_t dialogtoken;
	uint16_t baparamset, batimeout, baseqctl;
	uint16_t args[5];
	int tid;

	dialogtoken = frm[2];
	baparamset = le16dec(frm+3);
	batimeout = le16dec(frm+5);
	baseqctl = le16dec(frm+7);

	tid = MS(baparamset, IEEE80211_BAPS_TID);

	IEEE80211_NOTE(vap, IEEE80211_MSG_ACTION | IEEE80211_MSG_11N, ni,
	    "recv ADDBA request: dialogtoken %u baparamset 0x%x "
	    "(tid %d bufsiz %d) batimeout %d baseqctl %d:%d",
	    dialogtoken, baparamset,
	    tid, MS(baparamset, IEEE80211_BAPS_BUFSIZ),
	    batimeout,
	    MS(baseqctl, IEEE80211_BASEQ_START),
	    MS(baseqctl, IEEE80211_BASEQ_FRAG));

	rap = &ni->ni_rx_ampdu[tid];

	/* Send ADDBA response */
	args[0] = dialogtoken;
	/*
	 * NB: We ack only if the sta associated with HT and
	 * the ap is configured to do AMPDU rx (the latter
	 * violates the 11n spec and is mostly for testing).
	 */
	if ((ni->ni_flags & IEEE80211_NODE_AMPDU_RX) &&
	    (vap->iv_flags_ht & IEEE80211_FHT_AMPDU_RX)) {
		/* XXX handle ampdu_rx_start failure */
		ic->ic_ampdu_rx_start(ni, rap,
		    baparamset, batimeout, baseqctl);

		args[1] = IEEE80211_STATUS_SUCCESS;
	} else {
		IEEE80211_NOTE(vap, IEEE80211_MSG_ACTION | IEEE80211_MSG_11N,
		    ni, "reject ADDBA request: %s",
		    ni->ni_flags & IEEE80211_NODE_AMPDU_RX ?
		       "administratively disabled" :
		       "not negotiated for station");
		vap->iv_stats.is_addba_reject++;
		args[1] = IEEE80211_STATUS_UNSPECIFIED;
	}
	/* XXX honor rap flags? */
	args[2] = IEEE80211_BAPS_POLICY_IMMEDIATE
		| SM(tid, IEEE80211_BAPS_TID)
		| SM(rap->rxa_wnd, IEEE80211_BAPS_BUFSIZ)
		;
	args[3] = 0;
	args[4] = 0;
	ic->ic_send_action(ni, IEEE80211_ACTION_CAT_BA,
		IEEE80211_ACTION_BA_ADDBA_RESPONSE, args);
	return 0;
}