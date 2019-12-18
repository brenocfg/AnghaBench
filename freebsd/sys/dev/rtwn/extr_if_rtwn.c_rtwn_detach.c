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
struct ieee80211com {struct rtwn_softc* ic_softc; } ;
struct rtwn_softc {int sc_detached; int /*<<< orphan*/  cmdq_task; struct ieee80211com sc_ic; } ;

/* Variables and functions */
 int /*<<< orphan*/  RTWN_CMDQ_LOCK (struct rtwn_softc*) ; 
 int /*<<< orphan*/  RTWN_CMDQ_UNLOCK (struct rtwn_softc*) ; 
 int /*<<< orphan*/  RTWN_NT_LOCK_DESTROY (struct rtwn_softc*) ; 
 scalar_t__ RTWN_NT_LOCK_INITIALIZED (struct rtwn_softc*) ; 
 int /*<<< orphan*/  ieee80211_draintask (struct ieee80211com*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ieee80211_ifdetach (struct ieee80211com*) ; 
 int /*<<< orphan*/  rtwn_cmdq_destroy (struct rtwn_softc*) ; 

void
rtwn_detach(struct rtwn_softc *sc)
{
	struct ieee80211com *ic = &sc->sc_ic;

	if (ic->ic_softc == sc) {
		/* Stop command queue. */
		RTWN_CMDQ_LOCK(sc);
		sc->sc_detached = 1;
		RTWN_CMDQ_UNLOCK(sc);

		ieee80211_draintask(ic, &sc->cmdq_task);
		ieee80211_ifdetach(ic);
	}

	rtwn_cmdq_destroy(sc);
	if (RTWN_NT_LOCK_INITIALIZED(sc))
		RTWN_NT_LOCK_DESTROY(sc);
}