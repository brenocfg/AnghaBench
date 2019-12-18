#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct stainforeq {size_t space; struct ieee80211req_sta_info* si; } ;
struct ieee80211vap {scalar_t__ iv_opmode; int iv_inact_run; int iv_flags_ext; int iv_inact_auth; int iv_inact_init; TYPE_2__* iv_ic; } ;
struct ieee80211req_sta_info {size_t isi_len; int isi_ie_off; size_t isi_ie_len; int isi_state; int isi_nrates; int isi_txrate; int isi_txmbps; scalar_t__ isi_associd; int isi_inact; int /*<<< orphan*/  isi_peerstate; int /*<<< orphan*/  isi_peerid; int /*<<< orphan*/  isi_localid; int /*<<< orphan*/ * isi_rxseqs; int /*<<< orphan*/ * isi_txseqs; int /*<<< orphan*/  isi_vlan; int /*<<< orphan*/  isi_txpower; int /*<<< orphan*/ * isi_rates; int /*<<< orphan*/  isi_macaddr; int /*<<< orphan*/  isi_erp; int /*<<< orphan*/  isi_capinfo; int /*<<< orphan*/  isi_mimo; int /*<<< orphan*/  isi_noise; int /*<<< orphan*/  isi_rssi; int /*<<< orphan*/  isi_authmode; int /*<<< orphan*/  isi_flags; int /*<<< orphan*/  isi_freq; } ;
struct TYPE_6__ {int /*<<< orphan*/ * data; } ;
struct TYPE_8__ {int rs_nrates; int /*<<< orphan*/ * rs_rates; } ;
struct ieee80211_node {scalar_t__ ni_associd; int ni_flags; int ni_txrate; int ni_inact; TYPE_1__ ni_ies; int /*<<< orphan*/  ni_mlstate; int /*<<< orphan*/  ni_mlpid; int /*<<< orphan*/  ni_mllid; int /*<<< orphan*/ * ni_rxseqs; int /*<<< orphan*/ * ni_txseqs; int /*<<< orphan*/  ni_vlan; int /*<<< orphan*/  ni_txpower; TYPE_4__* ni_chan; TYPE_3__ ni_rates; int /*<<< orphan*/  ni_macaddr; int /*<<< orphan*/  ni_erp; int /*<<< orphan*/  ni_capinfo; int /*<<< orphan*/  ni_authmode; struct ieee80211vap* ni_vap; } ;
struct ieee80211_mcs_rates {int ht40_rate_800ns; int ht40_rate_400ns; int ht20_rate_800ns; int ht20_rate_400ns; } ;
struct TYPE_9__ {int /*<<< orphan*/  ic_flags; int /*<<< orphan*/  ic_freq; } ;
struct TYPE_7__ {int /*<<< orphan*/  (* ic_node_getmimoinfo ) (struct ieee80211_node*,int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* ic_node_getsignal ) (struct ieee80211_node*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  IEEE80211_ADDR_COPY (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_4__* IEEE80211_CHAN_ANYC ; 
 int IEEE80211_FEXT_WDSLEGACY ; 
 int IEEE80211_INACT_WAIT ; 
 scalar_t__ IEEE80211_IS_CHAN_HT40 (TYPE_4__*) ; 
 scalar_t__ IEEE80211_M_HOSTAP ; 
 scalar_t__ IEEE80211_M_WDS ; 
 int IEEE80211_NODE_QOS ; 
 int IEEE80211_NODE_SGI20 ; 
 int IEEE80211_NODE_SGI40 ; 
 size_t IEEE80211_NONQOS_TID ; 
 int IEEE80211_RATE_MCS ; 
 struct ieee80211_mcs_rates* ieee80211_htrates ; 
 scalar_t__ ieee80211_node_is_authorized (struct ieee80211_node*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t) ; 
 size_t sta_space (struct ieee80211_node*,size_t*) ; 
 int /*<<< orphan*/  stub1 (struct ieee80211_node*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub2 (struct ieee80211_node*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
get_sta_info(void *arg, struct ieee80211_node *ni)
{
	struct stainforeq *req = arg;
	struct ieee80211vap *vap = ni->ni_vap;
	struct ieee80211req_sta_info *si;
	size_t ielen, len;
	uint8_t *cp;

	if (vap->iv_opmode == IEEE80211_M_HOSTAP &&
	    ni->ni_associd == 0)	/* only associated stations */
		return;
	if (ni->ni_chan == IEEE80211_CHAN_ANYC)	/* XXX bogus entry */
		return;
	len = sta_space(ni, &ielen);
	if (len > req->space)
		return;
	si = req->si;
	si->isi_len = len;
	si->isi_ie_off = sizeof(struct ieee80211req_sta_info);
	si->isi_ie_len = ielen;
	si->isi_freq = ni->ni_chan->ic_freq;
	si->isi_flags = ni->ni_chan->ic_flags;
	si->isi_state = ni->ni_flags;
	si->isi_authmode = ni->ni_authmode;
	vap->iv_ic->ic_node_getsignal(ni, &si->isi_rssi, &si->isi_noise);
	vap->iv_ic->ic_node_getmimoinfo(ni, &si->isi_mimo);
	si->isi_capinfo = ni->ni_capinfo;
	si->isi_erp = ni->ni_erp;
	IEEE80211_ADDR_COPY(si->isi_macaddr, ni->ni_macaddr);
	si->isi_nrates = ni->ni_rates.rs_nrates;
	if (si->isi_nrates > 15)
		si->isi_nrates = 15;
	memcpy(si->isi_rates, ni->ni_rates.rs_rates, si->isi_nrates);
	si->isi_txrate = ni->ni_txrate;
	if (si->isi_txrate & IEEE80211_RATE_MCS) {
		const struct ieee80211_mcs_rates *mcs =
		    &ieee80211_htrates[ni->ni_txrate &~ IEEE80211_RATE_MCS];
		if (IEEE80211_IS_CHAN_HT40(ni->ni_chan)) {
			if (ni->ni_flags & IEEE80211_NODE_SGI40)
				si->isi_txmbps = mcs->ht40_rate_800ns;
			else
				si->isi_txmbps = mcs->ht40_rate_400ns;
		} else {
			if (ni->ni_flags & IEEE80211_NODE_SGI20)
				si->isi_txmbps = mcs->ht20_rate_800ns;
			else
				si->isi_txmbps = mcs->ht20_rate_400ns;
		}
	} else
		si->isi_txmbps = si->isi_txrate;
	si->isi_associd = ni->ni_associd;
	si->isi_txpower = ni->ni_txpower;
	si->isi_vlan = ni->ni_vlan;
	if (ni->ni_flags & IEEE80211_NODE_QOS) {
		memcpy(si->isi_txseqs, ni->ni_txseqs, sizeof(ni->ni_txseqs));
		memcpy(si->isi_rxseqs, ni->ni_rxseqs, sizeof(ni->ni_rxseqs));
	} else {
		si->isi_txseqs[0] = ni->ni_txseqs[IEEE80211_NONQOS_TID];
		si->isi_rxseqs[0] = ni->ni_rxseqs[IEEE80211_NONQOS_TID];
	}
	/* NB: leave all cases in case we relax ni_associd == 0 check */
	if (ieee80211_node_is_authorized(ni))
		si->isi_inact = vap->iv_inact_run;
	else if (ni->ni_associd != 0 ||
	    (vap->iv_opmode == IEEE80211_M_WDS &&
	     (vap->iv_flags_ext & IEEE80211_FEXT_WDSLEGACY)))
		si->isi_inact = vap->iv_inact_auth;
	else
		si->isi_inact = vap->iv_inact_init;
	si->isi_inact = (si->isi_inact - ni->ni_inact) * IEEE80211_INACT_WAIT;
	si->isi_localid = ni->ni_mllid;
	si->isi_peerid = ni->ni_mlpid;
	si->isi_peerstate = ni->ni_mlstate;

	if (ielen) {
		cp = ((uint8_t *)si) + si->isi_ie_off;
		memcpy(cp, ni->ni_ies.data, ielen);
	}

	req->si = (struct ieee80211req_sta_info *)(((uint8_t *)si) + len);
	req->space -= len;
}