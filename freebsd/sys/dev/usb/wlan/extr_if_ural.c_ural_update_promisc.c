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
struct ural_softc {scalar_t__ sc_running; } ;
struct ieee80211com {struct ural_softc* ic_softc; } ;

/* Variables and functions */
 int /*<<< orphan*/  RAL_LOCK (struct ural_softc*) ; 
 int /*<<< orphan*/  RAL_UNLOCK (struct ural_softc*) ; 
 int /*<<< orphan*/  ural_setpromisc (struct ural_softc*) ; 

__attribute__((used)) static void
ural_update_promisc(struct ieee80211com *ic)
{
	struct ural_softc *sc = ic->ic_softc;

	RAL_LOCK(sc);
	if (sc->sc_running)
		ural_setpromisc(sc);
	RAL_UNLOCK(sc);
}