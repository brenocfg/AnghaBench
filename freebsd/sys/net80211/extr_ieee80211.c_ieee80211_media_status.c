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
struct ifnet {struct ieee80211vap* if_softc; } ;
struct ifmediareq {int ifm_status; int /*<<< orphan*/  ifm_active; int /*<<< orphan*/  ifm_current; } ;
struct ieee80211vap {scalar_t__ iv_state; scalar_t__ iv_opmode; TYPE_2__* iv_bss; TYPE_1__* iv_txparms; struct ieee80211com* iv_ic; } ;
struct ieee80211com {int /*<<< orphan*/  ic_curchan; } ;
typedef  enum ieee80211_phymode { ____Placeholder_ieee80211_phymode } ieee80211_phymode ;
struct TYPE_4__ {scalar_t__ ni_txrate; } ;
struct TYPE_3__ {scalar_t__ ucastrate; } ;

/* Variables and functions */
 scalar_t__ IEEE80211_FIXED_RATE_NONE ; 
 int IEEE80211_MODE_AUTO ; 
 scalar_t__ IEEE80211_M_STA ; 
 scalar_t__ IEEE80211_S_RUN ; 
 scalar_t__ IEEE80211_S_SLEEP ; 
 int IFM_ACTIVE ; 
 int /*<<< orphan*/  IFM_AUTO ; 
 int IFM_AVALID ; 
 int ieee80211_chan2mode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_rate2media (struct ieee80211com*,scalar_t__,int) ; 
 int /*<<< orphan*/  media_status (scalar_t__,int /*<<< orphan*/ ) ; 

void
ieee80211_media_status(struct ifnet *ifp, struct ifmediareq *imr)
{
	struct ieee80211vap *vap = ifp->if_softc;
	struct ieee80211com *ic = vap->iv_ic;
	enum ieee80211_phymode mode;

	imr->ifm_status = IFM_AVALID;
	/*
	 * NB: use the current channel's mode to lock down a xmit
	 * rate only when running; otherwise we may have a mismatch
	 * in which case the rate will not be convertible.
	 */
	if (vap->iv_state == IEEE80211_S_RUN ||
	    vap->iv_state == IEEE80211_S_SLEEP) {
		imr->ifm_status |= IFM_ACTIVE;
		mode = ieee80211_chan2mode(ic->ic_curchan);
	} else
		mode = IEEE80211_MODE_AUTO;
	imr->ifm_active = media_status(vap->iv_opmode, ic->ic_curchan);
	/*
	 * Calculate a current rate if possible.
	 */
	if (vap->iv_txparms[mode].ucastrate != IEEE80211_FIXED_RATE_NONE) {
		/*
		 * A fixed rate is set, report that.
		 */
		imr->ifm_active |= ieee80211_rate2media(ic,
			vap->iv_txparms[mode].ucastrate, mode);
	} else if (vap->iv_opmode == IEEE80211_M_STA) {
		/*
		 * In station mode report the current transmit rate.
		 */
		imr->ifm_active |= ieee80211_rate2media(ic,
			vap->iv_bss->ni_txrate, mode);
	} else
		imr->ifm_active |= IFM_AUTO;
	if (imr->ifm_status & IFM_ACTIVE)
		imr->ifm_current = imr->ifm_active;
}