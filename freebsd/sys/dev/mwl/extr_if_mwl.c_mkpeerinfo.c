#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct ieee80211vap {int iv_flags_ht; } ;
struct ieee80211_node {int ni_flags; int ni_chw; int /*<<< orphan*/  ni_htstbc; int /*<<< orphan*/  ni_htopmode; int /*<<< orphan*/  ni_ht2ndchan; int /*<<< orphan*/  ni_htctlchan; int /*<<< orphan*/  ni_htrates; int /*<<< orphan*/  ni_htparam; int /*<<< orphan*/  ni_htcap; int /*<<< orphan*/  ni_capinfo; int /*<<< orphan*/  ni_rates; struct ieee80211vap* ni_vap; } ;
struct TYPE_6__ {int /*<<< orphan*/  stbc; int /*<<< orphan*/  OpMode; int /*<<< orphan*/  AddChan; int /*<<< orphan*/  ControlChan; } ;
struct TYPE_7__ {int /*<<< orphan*/  HTCapabilitiesInfo; TYPE_1__ AddHtInfo; int /*<<< orphan*/  HTRateBitMap; int /*<<< orphan*/  MacHTParamInfo; int /*<<< orphan*/  CapInfo; int /*<<< orphan*/  LegacyRateBitMap; } ;
typedef  TYPE_2__ MWL_HAL_PEERINFO ;

/* Variables and functions */
 int IEEE80211_FHT_SHORTGI20 ; 
 int IEEE80211_FHT_SHORTGI40 ; 
 int /*<<< orphan*/  IEEE80211_HTCAP_CHWIDTH40 ; 
 int /*<<< orphan*/  IEEE80211_HTCAP_SHORTGI20 ; 
 int /*<<< orphan*/  IEEE80211_HTCAP_SHORTGI40 ; 
 int IEEE80211_NODE_HT ; 
 int /*<<< orphan*/  get_htrate_bitmap (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_rate_bitmap (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static MWL_HAL_PEERINFO *
mkpeerinfo(MWL_HAL_PEERINFO *pi, const struct ieee80211_node *ni)
{
	const struct ieee80211vap *vap = ni->ni_vap;

	memset(pi, 0, sizeof(*pi));
	pi->LegacyRateBitMap = get_rate_bitmap(&ni->ni_rates);
	pi->CapInfo = ni->ni_capinfo;
	if (ni->ni_flags & IEEE80211_NODE_HT) {
		/* HT capabilities, etc */
		pi->HTCapabilitiesInfo = ni->ni_htcap;
		/* XXX pi.HTCapabilitiesInfo */
	        pi->MacHTParamInfo = ni->ni_htparam;	
		pi->HTRateBitMap = get_htrate_bitmap(&ni->ni_htrates);
		pi->AddHtInfo.ControlChan = ni->ni_htctlchan;
		pi->AddHtInfo.AddChan = ni->ni_ht2ndchan;
		pi->AddHtInfo.OpMode = ni->ni_htopmode;
		pi->AddHtInfo.stbc = ni->ni_htstbc;

		/* constrain according to local configuration */
		if ((vap->iv_flags_ht & IEEE80211_FHT_SHORTGI40) == 0)
			pi->HTCapabilitiesInfo &= ~IEEE80211_HTCAP_SHORTGI40;
		if ((vap->iv_flags_ht & IEEE80211_FHT_SHORTGI20) == 0)
			pi->HTCapabilitiesInfo &= ~IEEE80211_HTCAP_SHORTGI20;
		if (ni->ni_chw != 40)
			pi->HTCapabilitiesInfo &= ~IEEE80211_HTCAP_CHWIDTH40;
	}
	return pi;
}