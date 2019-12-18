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
struct ieee80211com {int dummy; } ;
struct iwi_softc {scalar_t__ sc_running; struct ieee80211com sc_ic; } ;

/* Variables and functions */
 int /*<<< orphan*/  IWI_LOCK (struct iwi_softc*) ; 
 int /*<<< orphan*/  IWI_LOCK_DECL ; 
 int /*<<< orphan*/  IWI_UNLOCK (struct iwi_softc*) ; 
 int /*<<< orphan*/  ieee80211_start_all (struct ieee80211com*) ; 
 int /*<<< orphan*/  iwi_init_locked (struct iwi_softc*) ; 

__attribute__((used)) static void
iwi_init(void *priv)
{
	struct iwi_softc *sc = priv;
	struct ieee80211com *ic = &sc->sc_ic;
	IWI_LOCK_DECL;

	IWI_LOCK(sc);
	iwi_init_locked(sc);
	IWI_UNLOCK(sc);

	if (sc->sc_running)
		ieee80211_start_all(ic);
}