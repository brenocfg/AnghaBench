#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct ieee80211vap {int iv_flags; int iv_flags_ext; scalar_t__ iv_bgscanidle; scalar_t__ iv_bgscanintvl; struct ieee80211com* iv_ic; } ;
struct ieee80211com {int ic_flags; scalar_t__ ic_lastdata; scalar_t__ ic_lastscan; int /*<<< orphan*/  ic_curchan; } ;

/* Variables and functions */
 int IEEE80211_FEXT_SCAN_OFFLOAD ; 
 int IEEE80211_F_BGSCAN ; 
 int IEEE80211_F_CSAPENDING ; 
 int /*<<< orphan*/  IEEE80211_IS_CHAN_DTURBO (int /*<<< orphan*/ ) ; 
 scalar_t__ ieee80211_time_after (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  ticks ; 

__attribute__((used)) static __inline int
startbgscan(struct ieee80211vap *vap)
{
	struct ieee80211com *ic = vap->iv_ic;

	return ((vap->iv_flags & IEEE80211_F_BGSCAN) &&
	    (ic->ic_flags & IEEE80211_F_CSAPENDING) == 0 &&
#ifdef IEEE80211_SUPPORT_SUPERG
	    !IEEE80211_IS_CHAN_DTURBO(ic->ic_curchan) &&
#endif
	    ieee80211_time_after(ticks, ic->ic_lastscan + vap->iv_bgscanintvl) &&
	    ((vap->iv_flags_ext & IEEE80211_FEXT_SCAN_OFFLOAD) ||
	     ieee80211_time_after(ticks, ic->ic_lastdata + vap->iv_bgscanidle)));
}