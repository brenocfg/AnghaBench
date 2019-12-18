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
struct iwi_softc {scalar_t__ sc_running; } ;
struct ieee80211com {scalar_t__ ic_nrunning; struct iwi_softc* ic_softc; } ;

/* Variables and functions */
 int /*<<< orphan*/  IWI_LOCK (struct iwi_softc*) ; 
 int /*<<< orphan*/  IWI_LOCK_DECL ; 
 int /*<<< orphan*/  IWI_UNLOCK (struct iwi_softc*) ; 
 int /*<<< orphan*/  ieee80211_start_all (struct ieee80211com*) ; 
 int /*<<< orphan*/  iwi_init_locked (struct iwi_softc*) ; 
 int /*<<< orphan*/  iwi_stop_locked (struct iwi_softc*) ; 

__attribute__((used)) static void
iwi_parent(struct ieee80211com *ic)
{
	struct iwi_softc *sc = ic->ic_softc;
	int startall = 0;
	IWI_LOCK_DECL;

	IWI_LOCK(sc);
	if (ic->ic_nrunning > 0) {
		if (!sc->sc_running) {
			iwi_init_locked(sc);
			startall = 1;
		}
	} else if (sc->sc_running)
		iwi_stop_locked(sc);
	IWI_UNLOCK(sc);
	if (startall)
		ieee80211_start_all(ic);
}