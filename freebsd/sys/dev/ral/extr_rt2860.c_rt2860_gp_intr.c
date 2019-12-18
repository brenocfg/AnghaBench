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
struct ieee80211com {int /*<<< orphan*/  ic_vaps; } ;
struct rt2860_softc {struct ieee80211com sc_ic; } ;
struct ieee80211vap {scalar_t__ iv_state; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTFN (int,char*) ; 
 scalar_t__ IEEE80211_S_RUN ; 
 struct ieee80211vap* TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rt2860_updatestats (struct rt2860_softc*) ; 

__attribute__((used)) static void
rt2860_gp_intr(struct rt2860_softc *sc)
{
	struct ieee80211com *ic = &sc->sc_ic;
	struct ieee80211vap *vap = TAILQ_FIRST(&ic->ic_vaps);

	DPRINTFN(2, ("GP timeout state=%d\n", vap->iv_state));

	if (vap->iv_state == IEEE80211_S_RUN)
		rt2860_updatestats(sc);
}