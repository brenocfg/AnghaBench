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
struct ipw_softc {int flags; } ;
struct ieee80211com {scalar_t__ ic_nrunning; struct ipw_softc* ic_softc; } ;

/* Variables and functions */
 int IPW_FLAG_RUNNING ; 
 int /*<<< orphan*/  IPW_LOCK (struct ipw_softc*) ; 
 int /*<<< orphan*/  IPW_UNLOCK (struct ipw_softc*) ; 
 int /*<<< orphan*/  ieee80211_start_all (struct ieee80211com*) ; 
 int /*<<< orphan*/  ipw_init_locked (struct ipw_softc*) ; 
 int /*<<< orphan*/  ipw_stop_locked (struct ipw_softc*) ; 

__attribute__((used)) static void
ipw_parent(struct ieee80211com *ic)
{
	struct ipw_softc *sc = ic->ic_softc;
	int startall = 0;

	IPW_LOCK(sc);
	if (ic->ic_nrunning > 0) {
		if (!(sc->flags & IPW_FLAG_RUNNING)) {
			ipw_init_locked(sc);
			startall = 1;
		}
	} else if (sc->flags & IPW_FLAG_RUNNING)
		ipw_stop_locked(sc);
	IPW_UNLOCK(sc);
	if (startall)
		ieee80211_start_all(ic);
}