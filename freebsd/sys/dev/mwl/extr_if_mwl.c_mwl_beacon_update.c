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
struct mwl_hal_vap {int dummy; } ;
struct ieee80211vap {struct ieee80211com* iv_ic; } ;
struct ieee80211com {int /*<<< orphan*/  ic_curhtprotmode; } ;
struct TYPE_2__ {struct mwl_hal_vap* mv_hvap; } ;

/* Variables and functions */
#define  IEEE80211_BEACON_APPIE 134 
#define  IEEE80211_BEACON_CAPS 133 
#define  IEEE80211_BEACON_CSA 132 
#define  IEEE80211_BEACON_ERP 131 
#define  IEEE80211_BEACON_HTINFO 130 
#define  IEEE80211_BEACON_TIM 129 
#define  IEEE80211_BEACON_WME 128 
 int /*<<< orphan*/  IEEE80211_HTINFO_OPMODE ; 
 int /*<<< orphan*/  KASSERT (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  MS (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* MWL_VAP (struct ieee80211vap*) ; 
 int /*<<< orphan*/  mwl_beacon_setup (struct ieee80211vap*) ; 
 int /*<<< orphan*/  mwl_hal_setnprotmode (struct mwl_hal_vap*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mwl_updateslot (struct ieee80211com*) ; 

__attribute__((used)) static void
mwl_beacon_update(struct ieee80211vap *vap, int item)
{
	struct mwl_hal_vap *hvap = MWL_VAP(vap)->mv_hvap;
	struct ieee80211com *ic = vap->iv_ic;

	KASSERT(hvap != NULL, ("no beacon"));
	switch (item) {
	case IEEE80211_BEACON_ERP:
		mwl_updateslot(ic);
		break;
	case IEEE80211_BEACON_HTINFO:
		mwl_hal_setnprotmode(hvap,
		    MS(ic->ic_curhtprotmode, IEEE80211_HTINFO_OPMODE));
		break;
	case IEEE80211_BEACON_CAPS:
	case IEEE80211_BEACON_WME:
	case IEEE80211_BEACON_APPIE:
	case IEEE80211_BEACON_CSA:
		break;
	case IEEE80211_BEACON_TIM:
		/* NB: firmware always forms TIM */
		return;
	}
	/* XXX retain beacon frame and update */
	mwl_beacon_setup(vap);
}