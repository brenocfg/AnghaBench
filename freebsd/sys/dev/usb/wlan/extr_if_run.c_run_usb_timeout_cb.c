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
struct run_softc {int dummy; } ;
struct ieee80211vap {scalar_t__ iv_state; scalar_t__ iv_opmode; TYPE_1__* iv_ic; } ;
struct TYPE_2__ {struct run_softc* ic_softc; } ;

/* Variables and functions */
 scalar_t__ IEEE80211_M_STA ; 
 scalar_t__ IEEE80211_S_RUN ; 
 scalar_t__ IEEE80211_S_SCAN ; 
 int /*<<< orphan*/  MA_OWNED ; 
 int RUN_DEBUG_STATE ; 
 int RUN_DEBUG_USB ; 
 int /*<<< orphan*/  RUN_DPRINTF (struct run_softc*,int,char*) ; 
 int /*<<< orphan*/  RUN_LOCK_ASSERT (struct run_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_cancel_scan (struct ieee80211vap*) ; 
 int /*<<< orphan*/  run_reset_livelock (struct run_softc*) ; 

__attribute__((used)) static void
run_usb_timeout_cb(void *arg)
{
	struct ieee80211vap *vap = arg;
	struct run_softc *sc = vap->iv_ic->ic_softc;

	RUN_LOCK_ASSERT(sc, MA_OWNED);

	if(vap->iv_state == IEEE80211_S_RUN &&
	    vap->iv_opmode != IEEE80211_M_STA)
		run_reset_livelock(sc);
	else if (vap->iv_state == IEEE80211_S_SCAN) {
		RUN_DPRINTF(sc, RUN_DEBUG_USB | RUN_DEBUG_STATE,
		    "timeout caused by scan\n");
		/* cancel bgscan */
		ieee80211_cancel_scan(vap);
	} else
		RUN_DPRINTF(sc, RUN_DEBUG_USB | RUN_DEBUG_STATE,
		    "timeout by unknown cause\n");
}