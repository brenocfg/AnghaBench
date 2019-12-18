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
struct rum_softc {scalar_t__ sc_detached; } ;
struct ieee80211vap {int dummy; } ;
struct ieee80211com {scalar_t__ ic_nrunning; int /*<<< orphan*/  ic_vaps; struct rum_softc* ic_softc; } ;

/* Variables and functions */
 int /*<<< orphan*/  RUM_LOCK (struct rum_softc*) ; 
 int /*<<< orphan*/  RUM_UNLOCK (struct rum_softc*) ; 
 struct ieee80211vap* TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ieee80211_start_all (struct ieee80211com*) ; 
 int /*<<< orphan*/  ieee80211_stop (struct ieee80211vap*) ; 
 scalar_t__ rum_init (struct rum_softc*) ; 
 int /*<<< orphan*/  rum_stop (struct rum_softc*) ; 

__attribute__((used)) static void
rum_parent(struct ieee80211com *ic)
{
	struct rum_softc *sc = ic->ic_softc;
	struct ieee80211vap *vap = TAILQ_FIRST(&ic->ic_vaps);

	RUM_LOCK(sc);
	if (sc->sc_detached) {
		RUM_UNLOCK(sc);
		return;
	}
	RUM_UNLOCK(sc);

	if (ic->ic_nrunning > 0) {
		if (rum_init(sc) == 0)
			ieee80211_start_all(ic);
		else
			ieee80211_stop(vap);
	} else
		rum_stop(sc);
}