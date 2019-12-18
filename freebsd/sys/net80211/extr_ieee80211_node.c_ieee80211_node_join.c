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
typedef  int uint16_t ;
struct ieee80211vap {int iv_max_aid; TYPE_1__* iv_auth; int /*<<< orphan*/  iv_sta_assoc; int /*<<< orphan*/ * iv_aid_bitmap; } ;
struct ieee80211com {int ic_flags; int /*<<< orphan*/  (* ic_newassoc ) (struct ieee80211_node*,int) ;int /*<<< orphan*/  ic_bsschan; int /*<<< orphan*/  ic_sta_assoc; } ;
struct ieee80211_node {scalar_t__ ni_associd; int ni_flags; int ni_chw; int /*<<< orphan*/  ni_jointime; struct ieee80211vap* ni_vap; struct ieee80211com* ni_ic; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* ia_node_join ) (struct ieee80211_node*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  IEEE80211_AID_ISSET (struct ieee80211vap*,int) ; 
 int /*<<< orphan*/  IEEE80211_AID_SET (struct ieee80211vap*,int) ; 
 scalar_t__ IEEE80211_ATH_CAP (struct ieee80211vap*,struct ieee80211_node*,int /*<<< orphan*/ ) ; 
 int IEEE80211_FC0_SUBTYPE_ASSOC_RESP ; 
 int IEEE80211_F_SHPREAMBLE ; 
 int IEEE80211_F_SHSLOT ; 
 int IEEE80211_F_USEPROT ; 
 scalar_t__ IEEE80211_IS_CHAN_ANYG (int /*<<< orphan*/ ) ; 
 scalar_t__ IEEE80211_IS_CHAN_FULL (int /*<<< orphan*/ ) ; 
 scalar_t__ IEEE80211_IS_CHAN_HT (int /*<<< orphan*/ ) ; 
 scalar_t__ IEEE80211_IS_CHAN_VHT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IEEE80211_LOCK (struct ieee80211com*) ; 
 int IEEE80211_MSG_ASSOC ; 
 int IEEE80211_MSG_DEBUG ; 
 int /*<<< orphan*/  IEEE80211_NODE_AID (struct ieee80211_node*) ; 
 int IEEE80211_NODE_AMPDU ; 
 int /*<<< orphan*/  IEEE80211_NODE_FF ; 
 int IEEE80211_NODE_HT ; 
 int IEEE80211_NODE_MIMO_PS ; 
 int IEEE80211_NODE_MIMO_RTS ; 
 int IEEE80211_NODE_QOS ; 
 int IEEE80211_NODE_RIFS ; 
 int /*<<< orphan*/  IEEE80211_NODE_TURBOP ; 
 int /*<<< orphan*/  IEEE80211_NOTE (struct ieee80211vap*,int,struct ieee80211_node*,char*,int /*<<< orphan*/ ,char*,char*,char*,char*,char*,char*,char*,char*,char*,char*) ; 
 int /*<<< orphan*/  IEEE80211_SEND_MGMT (struct ieee80211_node*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IEEE80211_STATUS_SUCCESS ; 
 int /*<<< orphan*/  IEEE80211_STATUS_TOOMANY ; 
 int /*<<< orphan*/  IEEE80211_UNLOCK (struct ieee80211com*) ; 
 int /*<<< orphan*/  KASSERT (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ieee80211_ht_node_join (struct ieee80211_node*) ; 
 int /*<<< orphan*/  ieee80211_node_join_11g (struct ieee80211_node*) ; 
 int /*<<< orphan*/  ieee80211_node_leave (struct ieee80211_node*) ; 
 int /*<<< orphan*/  ieee80211_node_setuptxparms (struct ieee80211_node*) ; 
 int /*<<< orphan*/  ieee80211_notify_node_join (struct ieee80211_node*,int) ; 
 int /*<<< orphan*/  ieee80211_ratectl_node_init (struct ieee80211_node*) ; 
 int /*<<< orphan*/  ieee80211_vht_node_join (struct ieee80211_node*) ; 
 int /*<<< orphan*/  stub1 (struct ieee80211_node*,int) ; 
 int /*<<< orphan*/  stub2 (struct ieee80211_node*) ; 
 int /*<<< orphan*/  time_uptime ; 

void
ieee80211_node_join(struct ieee80211_node *ni, int resp)
{
	struct ieee80211com *ic = ni->ni_ic;
	struct ieee80211vap *vap = ni->ni_vap;
	int newassoc;

	if (ni->ni_associd == 0) {
		uint16_t aid;

		KASSERT(vap->iv_aid_bitmap != NULL, ("no aid bitmap"));
		/*
		 * It would be good to search the bitmap
		 * more efficiently, but this will do for now.
		 */
		for (aid = 1; aid < vap->iv_max_aid; aid++) {
			if (!IEEE80211_AID_ISSET(vap, aid))
				break;
		}
		if (aid >= vap->iv_max_aid) {
			IEEE80211_SEND_MGMT(ni, resp, IEEE80211_STATUS_TOOMANY);
			ieee80211_node_leave(ni);
			return;
		}
		ni->ni_associd = aid | 0xc000;
		ni->ni_jointime = time_uptime;
		IEEE80211_LOCK(ic);
		IEEE80211_AID_SET(vap, ni->ni_associd);
		vap->iv_sta_assoc++;
		ic->ic_sta_assoc++;

		if (IEEE80211_IS_CHAN_HT(ic->ic_bsschan))
			ieee80211_ht_node_join(ni);
		if (IEEE80211_IS_CHAN_VHT(ic->ic_bsschan))
			ieee80211_vht_node_join(ni);
		if (IEEE80211_IS_CHAN_ANYG(ic->ic_bsschan) &&
		    IEEE80211_IS_CHAN_FULL(ic->ic_bsschan))
			ieee80211_node_join_11g(ni);
		IEEE80211_UNLOCK(ic);

		newassoc = 1;
	} else
		newassoc = 0;

	/*
	 * XXX VHT - should log VHT channel width, etc
	 */
	IEEE80211_NOTE(vap, IEEE80211_MSG_ASSOC | IEEE80211_MSG_DEBUG, ni,
	    "station associated at aid %d: %s preamble, %s slot time%s%s%s%s%s%s%s%s",
	    IEEE80211_NODE_AID(ni),
	    ic->ic_flags & IEEE80211_F_SHPREAMBLE ? "short" : "long",
	    ic->ic_flags & IEEE80211_F_SHSLOT ? "short" : "long",
	    ic->ic_flags & IEEE80211_F_USEPROT ? ", protection" : "",
	    ni->ni_flags & IEEE80211_NODE_QOS ? ", QoS" : "",
	    /* XXX update for VHT string */
	    ni->ni_flags & IEEE80211_NODE_HT ?
		(ni->ni_chw == 40 ? ", HT40" : ", HT20") : "",
	    ni->ni_flags & IEEE80211_NODE_AMPDU ? " (+AMPDU)" : "",
	    ni->ni_flags & IEEE80211_NODE_MIMO_RTS ? " (+SMPS-DYN)" :
	        ni->ni_flags & IEEE80211_NODE_MIMO_PS ? " (+SMPS)" : "",
	    ni->ni_flags & IEEE80211_NODE_RIFS ? " (+RIFS)" : "",
	    IEEE80211_ATH_CAP(vap, ni, IEEE80211_NODE_FF) ?
		", fast-frames" : "",
	    IEEE80211_ATH_CAP(vap, ni, IEEE80211_NODE_TURBOP) ?
		", turbo" : ""
	);

	ieee80211_node_setuptxparms(ni);
	ieee80211_ratectl_node_init(ni);
	/* give driver a chance to setup state like ni_txrate */
	if (ic->ic_newassoc != NULL)
		ic->ic_newassoc(ni, newassoc);
	IEEE80211_SEND_MGMT(ni, resp, IEEE80211_STATUS_SUCCESS);
	/* tell the authenticator about new station */
	if (vap->iv_auth->ia_node_join != NULL)
		vap->iv_auth->ia_node_join(ni);
	ieee80211_notify_node_join(ni,
	    resp == IEEE80211_FC0_SUBTYPE_ASSOC_RESP);
}