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
struct malo_softc {scalar_t__ malo_running; struct ieee80211com malo_ic; } ;

/* Variables and functions */
 int /*<<< orphan*/  MALO_LOCK (struct malo_softc*) ; 
 int /*<<< orphan*/  MALO_UNLOCK (struct malo_softc*) ; 
 int /*<<< orphan*/  ieee80211_start_all (struct ieee80211com*) ; 
 int /*<<< orphan*/  malo_init_locked (struct malo_softc*) ; 

__attribute__((used)) static void
malo_init(void *arg)
{
	struct malo_softc *sc = (struct malo_softc *) arg;
	struct ieee80211com *ic = &sc->malo_ic;
	
	MALO_LOCK(sc);
	malo_init_locked(sc);
	MALO_UNLOCK(sc);

	if (sc->malo_running)
		ieee80211_start_all(ic);	/* start all vap's */
}