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
struct iwn_softc {int /*<<< orphan*/  sc_rftoggle_task; int /*<<< orphan*/  sc_tq; } ;
struct ieee80211vap {int dummy; } ;
struct ieee80211com {scalar_t__ ic_nrunning; int /*<<< orphan*/  ic_vaps; struct iwn_softc* ic_softc; } ;

/* Variables and functions */
 struct ieee80211vap* TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ieee80211_start_all (struct ieee80211com*) ; 
 int /*<<< orphan*/  ieee80211_stop (struct ieee80211vap*) ; 
 int iwn_init (struct iwn_softc*) ; 
 int /*<<< orphan*/  iwn_stop (struct iwn_softc*) ; 
 int /*<<< orphan*/  taskqueue_enqueue (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
iwn_parent(struct ieee80211com *ic)
{
	struct iwn_softc *sc = ic->ic_softc;
	struct ieee80211vap *vap;
	int error;

	if (ic->ic_nrunning > 0) {
		error = iwn_init(sc);

		switch (error) {
		case 0:
			ieee80211_start_all(ic);
			break;
		case 1:
			/* radio is disabled via RFkill switch */
			taskqueue_enqueue(sc->sc_tq, &sc->sc_rftoggle_task);
			break;
		default:
			vap = TAILQ_FIRST(&ic->ic_vaps);
			if (vap != NULL)
				ieee80211_stop(vap);
			break;
		}
	} else
		iwn_stop(sc);
}