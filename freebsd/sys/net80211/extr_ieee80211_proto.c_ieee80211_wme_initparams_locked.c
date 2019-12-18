#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct wmeParams {int dummy; } ;
struct ieee80211vap {TYPE_3__* iv_bss; struct ieee80211com* iv_ic; } ;
struct TYPE_5__ {struct wmeParams* cap_wmeParams; } ;
struct TYPE_4__ {struct wmeParams* cap_wmeParams; scalar_t__ cap_info; } ;
struct ieee80211_wme_state {int wme_hipri_switch_thresh; int /*<<< orphan*/  wme_flags; TYPE_2__ wme_wmeBssChanParams; TYPE_1__ wme_wmeChanParams; } ;
struct ieee80211com {int ic_caps; int ic_nrunning; scalar_t__ ic_bsschan; scalar_t__ ic_opmode; struct ieee80211_wme_state ic_wme; } ;
typedef  int /*<<< orphan*/  paramType ;
typedef  enum ieee80211_phymode { ____Placeholder_ieee80211_phymode } ieee80211_phymode ;
struct TYPE_6__ {int ni_intval; } ;

/* Variables and functions */
 int HIGH_PRI_SWITCH_THRESH ; 
 scalar_t__ IEEE80211_CHAN_ANYC ; 
 int IEEE80211_C_WME ; 
 int /*<<< orphan*/  IEEE80211_LOCK_ASSERT (struct ieee80211com*) ; 
 int IEEE80211_MODE_AUTO ; 
 scalar_t__ IEEE80211_M_HOSTAP ; 
#define  WME_AC_BE 131 
#define  WME_AC_BK 130 
#define  WME_AC_VI 129 
#define  WME_AC_VO 128 
 int /*<<< orphan*/  WME_F_AGGRMODE ; 
 int WME_NUM_AC ; 
 int /*<<< orphan*/ * bssPhyParamForAC_BE ; 
 int /*<<< orphan*/ * bssPhyParamForAC_VI ; 
 int /*<<< orphan*/ * bssPhyParamForAC_VO ; 
 int ieee80211_chan2mode (scalar_t__) ; 
 int /*<<< orphan*/  ieee80211_wme_updateparams (struct ieee80211vap*) ; 
 int /*<<< orphan*/ * phyParamForAC_BE ; 
 int /*<<< orphan*/ * phyParamForAC_BK ; 
 int /*<<< orphan*/ * phyParamForAC_VI ; 
 int /*<<< orphan*/ * phyParamForAC_VO ; 
 int /*<<< orphan*/  setwmeparams (struct ieee80211vap*,char*,int,struct wmeParams*,int /*<<< orphan*/  const*) ; 

__attribute__((used)) static void
ieee80211_wme_initparams_locked(struct ieee80211vap *vap)
{
	struct ieee80211com *ic = vap->iv_ic;
	struct ieee80211_wme_state *wme = &ic->ic_wme;
	const paramType *pPhyParam, *pBssPhyParam;
	struct wmeParams *wmep;
	enum ieee80211_phymode mode;
	int i;

	IEEE80211_LOCK_ASSERT(ic);

	if ((ic->ic_caps & IEEE80211_C_WME) == 0 || ic->ic_nrunning > 1)
		return;

	/*
	 * Clear the wme cap_info field so a qoscount from a previous
	 * vap doesn't confuse later code which only parses the beacon
	 * field and updates hardware when said field changes.
	 * Otherwise the hardware is programmed with defaults, not what
	 * the beacon actually announces.
	 */
	wme->wme_wmeChanParams.cap_info = 0;

	/*
	 * Select mode; we can be called early in which case we
	 * always use auto mode.  We know we'll be called when
	 * entering the RUN state with bsschan setup properly
	 * so state will eventually get set correctly
	 */
	if (ic->ic_bsschan != IEEE80211_CHAN_ANYC)
		mode = ieee80211_chan2mode(ic->ic_bsschan);
	else
		mode = IEEE80211_MODE_AUTO;
	for (i = 0; i < WME_NUM_AC; i++) {
		switch (i) {
		case WME_AC_BK:
			pPhyParam = &phyParamForAC_BK[mode];
			pBssPhyParam = &phyParamForAC_BK[mode];
			break;
		case WME_AC_VI:
			pPhyParam = &phyParamForAC_VI[mode];
			pBssPhyParam = &bssPhyParamForAC_VI[mode];
			break;
		case WME_AC_VO:
			pPhyParam = &phyParamForAC_VO[mode];
			pBssPhyParam = &bssPhyParamForAC_VO[mode];
			break;
		case WME_AC_BE:
		default:
			pPhyParam = &phyParamForAC_BE[mode];
			pBssPhyParam = &bssPhyParamForAC_BE[mode];
			break;
		}
		wmep = &wme->wme_wmeChanParams.cap_wmeParams[i];
		if (ic->ic_opmode == IEEE80211_M_HOSTAP) {
			setwmeparams(vap, "chan", i, wmep, pPhyParam);
		} else {
			setwmeparams(vap, "chan", i, wmep, pBssPhyParam);
		}	
		wmep = &wme->wme_wmeBssChanParams.cap_wmeParams[i];
		setwmeparams(vap, "bss ", i, wmep, pBssPhyParam);
	}
	/* NB: check ic_bss to avoid NULL deref on initial attach */
	if (vap->iv_bss != NULL) {
		/*
		 * Calculate aggressive mode switching threshold based
		 * on beacon interval.  This doesn't need locking since
		 * we're only called before entering the RUN state at
		 * which point we start sending beacon frames.
		 */
		wme->wme_hipri_switch_thresh =
			(HIGH_PRI_SWITCH_THRESH * vap->iv_bss->ni_intval) / 100;
		wme->wme_flags &= ~WME_F_AGGRMODE;
		ieee80211_wme_updateparams(vap);
	}
}