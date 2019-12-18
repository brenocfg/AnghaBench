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
struct iwi_softc {int dummy; } ;
struct ieee80211vap {scalar_t__ iv_state; } ;
struct ieee80211com {int /*<<< orphan*/  ic_vaps; struct iwi_softc* ic_softc; } ;

/* Variables and functions */
 scalar_t__ IEEE80211_S_RUN ; 
 int /*<<< orphan*/  IWI_LOCK (struct iwi_softc*) ; 
 int /*<<< orphan*/  IWI_LOCK_DECL ; 
 int /*<<< orphan*/  IWI_UNLOCK (struct iwi_softc*) ; 
 struct ieee80211vap* TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iwi_wme_setparams (struct iwi_softc*) ; 

__attribute__((used)) static int
iwi_wme_update(struct ieee80211com *ic)
{
	struct iwi_softc *sc = ic->ic_softc;
	struct ieee80211vap *vap = TAILQ_FIRST(&ic->ic_vaps);
	IWI_LOCK_DECL;

	/*
	 * We may be called to update the WME parameters in
	 * the adapter at various places.  If we're already
	 * associated then initiate the request immediately;
	 * otherwise we assume the params will get sent down
	 * to the adapter as part of the work iwi_auth_and_assoc
	 * does.
	 */
	if (vap->iv_state == IEEE80211_S_RUN) {
		IWI_LOCK(sc);
		iwi_wme_setparams(sc);
		IWI_UNLOCK(sc);
	}
	return (0);
}