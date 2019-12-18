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
struct bwi_softc {int sc_flags; struct ieee80211com sc_ic; } ;

/* Variables and functions */
 int BWI_F_RUNNING ; 
 int /*<<< orphan*/  BWI_LOCK (struct bwi_softc*) ; 
 int /*<<< orphan*/  BWI_UNLOCK (struct bwi_softc*) ; 
 int /*<<< orphan*/  bwi_init_statechg (struct bwi_softc*,int) ; 
 int /*<<< orphan*/  ieee80211_start_all (struct ieee80211com*) ; 

__attribute__((used)) static void
bwi_init(struct bwi_softc *sc)
{
	struct ieee80211com *ic = &sc->sc_ic;

	BWI_LOCK(sc);
	bwi_init_statechg(sc, 1);
	BWI_UNLOCK(sc);

	if (sc->sc_flags & BWI_F_RUNNING)
		ieee80211_start_all(ic);		/* start all vap's */
}