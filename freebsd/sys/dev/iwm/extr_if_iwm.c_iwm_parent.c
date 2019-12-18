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
struct iwm_softc {int sc_flags; } ;
struct ieee80211com {scalar_t__ ic_nrunning; struct iwm_softc* ic_softc; } ;

/* Variables and functions */
 int IWM_FLAG_HW_INITED ; 
 int /*<<< orphan*/  IWM_LOCK (struct iwm_softc*) ; 
 int /*<<< orphan*/  IWM_UNLOCK (struct iwm_softc*) ; 
 int /*<<< orphan*/  ieee80211_start_all (struct ieee80211com*) ; 
 int /*<<< orphan*/  iwm_init (struct iwm_softc*) ; 
 int /*<<< orphan*/  iwm_stop (struct iwm_softc*) ; 

__attribute__((used)) static void
iwm_parent(struct ieee80211com *ic)
{
	struct iwm_softc *sc = ic->ic_softc;
	int startall = 0;

	IWM_LOCK(sc);
	if (ic->ic_nrunning > 0) {
		if (!(sc->sc_flags & IWM_FLAG_HW_INITED)) {
			iwm_init(sc);
			startall = 1;
		}
	} else if (sc->sc_flags & IWM_FLAG_HW_INITED)
		iwm_stop(sc);
	IWM_UNLOCK(sc);
	if (startall)
		ieee80211_start_all(ic);
}