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
struct run_softc {int sc_flags; } ;
struct ieee80211com {struct run_softc* ic_softc; } ;

/* Variables and functions */
 int /*<<< orphan*/  RUN_LOCK (struct run_softc*) ; 
 int RUN_RUNNING ; 
 int /*<<< orphan*/  RUN_UNLOCK (struct run_softc*) ; 
 int /*<<< orphan*/  run_update_promisc_locked (struct run_softc*) ; 

__attribute__((used)) static void
run_update_promisc(struct ieee80211com *ic)
{
	struct run_softc *sc = ic->ic_softc;

	if ((sc->sc_flags & RUN_RUNNING) == 0)
		return;

	RUN_LOCK(sc);
	run_update_promisc_locked(sc);
	RUN_UNLOCK(sc);
}