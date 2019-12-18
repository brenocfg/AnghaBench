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
struct scan_state {int ss_iflags; scalar_t__ ss_scanend; } ;
struct ieee80211vap {int iv_flags_ext; int /*<<< orphan*/  (* iv_sta_ps ) (struct ieee80211vap*,int /*<<< orphan*/ ) ;} ;
struct ieee80211com {int /*<<< orphan*/  ic_flags_ext; int /*<<< orphan*/  ic_flags; } ;
struct ieee80211_scan_state {scalar_t__ ss_next; scalar_t__ ss_last; int ss_flags; struct ieee80211vap* ss_vap; struct ieee80211com* ss_ic; } ;

/* Variables and functions */
 int /*<<< orphan*/  IEEE80211_FEXT_BGSCAN ; 
 int IEEE80211_FEXT_SCAN_OFFLOAD ; 
 int /*<<< orphan*/  IEEE80211_F_SCAN ; 
 int /*<<< orphan*/  IEEE80211_LOCK_ASSERT (struct ieee80211com*) ; 
 int IEEE80211_SCAN_ONCE ; 
 int IEEE80211_SCAN_PICK1ST ; 
 int /*<<< orphan*/  IEEE80211_UNLOCK (struct ieee80211com*) ; 
 int ISCAN_ABORT ; 
 int ISCAN_INTERRUPT ; 
 int ISCAN_PAUSE ; 
 struct scan_state* SCAN_PRIVATE (struct ieee80211_scan_state*) ; 
 int /*<<< orphan*/  ieee80211_notify_scan_done (struct ieee80211vap*) ; 
 int /*<<< orphan*/  stub1 (struct ieee80211vap*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
scan_done(struct ieee80211_scan_state *ss, int scandone)
{
	struct scan_state *ss_priv = SCAN_PRIVATE(ss);
	struct ieee80211com *ic = ss->ss_ic;
	struct ieee80211vap *vap = ss->ss_vap;

	IEEE80211_LOCK_ASSERT(ic);

	/*
	 * Clear the SCAN bit first in case frames are
	 * pending on the station power save queue.  If
	 * we defer this then the dispatch of the frames
	 * may generate a request to cancel scanning.
	 */
	ic->ic_flags &= ~IEEE80211_F_SCAN;

	/*
	 * Drop out of power save mode when a scan has
	 * completed.  If this scan was prematurely terminated
	 * because it is a background scan then don't notify
	 * the ap; we'll either return to scanning after we
	 * receive the beacon frame or we'll drop out of power
	 * save mode because the beacon indicates we have frames
	 * waiting for us.
	 */
	if (scandone) {
		/*
		 * If we're not a scan offload device, come back out of
		 * station powersave.  Offload devices handle this themselves.
		 */
		if ((vap->iv_flags_ext & IEEE80211_FEXT_SCAN_OFFLOAD) == 0)
			vap->iv_sta_ps(vap, 0);
		if (ss->ss_next >= ss->ss_last)
			ic->ic_flags_ext &= ~IEEE80211_FEXT_BGSCAN;

		/* send 'scan done' event if not interrupted due to traffic. */
		if (!(ss_priv->ss_iflags & ISCAN_INTERRUPT))
			ieee80211_notify_scan_done(vap);
	}
	ss_priv->ss_iflags &= ~(ISCAN_PAUSE | ISCAN_ABORT);
	ss_priv->ss_scanend = 0;
	ss->ss_flags &= ~(IEEE80211_SCAN_ONCE | IEEE80211_SCAN_PICK1ST);
	IEEE80211_UNLOCK(ic);
#undef ISCAN_REP
}