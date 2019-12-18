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
struct iwm_softc {int dummy; } ;
struct ifnet {struct ieee80211vap* if_softc; } ;
struct ieee80211vap {struct ieee80211com* iv_ic; } ;
struct ieee80211com {scalar_t__ ic_nrunning; struct iwm_softc* ic_softc; } ;

/* Variables and functions */
 int ENETRESET ; 
 int /*<<< orphan*/  IWM_LOCK (struct iwm_softc*) ; 
 int /*<<< orphan*/  IWM_UNLOCK (struct iwm_softc*) ; 
 int ieee80211_media_change (struct ifnet*) ; 
 int /*<<< orphan*/  iwm_init (struct iwm_softc*) ; 
 int /*<<< orphan*/  iwm_stop (struct iwm_softc*) ; 

__attribute__((used)) static int
iwm_media_change(struct ifnet *ifp)
{
	struct ieee80211vap *vap = ifp->if_softc;
	struct ieee80211com *ic = vap->iv_ic;
	struct iwm_softc *sc = ic->ic_softc;
	int error;

	error = ieee80211_media_change(ifp);
	if (error != ENETRESET)
		return error;

	IWM_LOCK(sc);
	if (ic->ic_nrunning > 0) {
		iwm_stop(sc);
		iwm_init(sc);
	}
	IWM_UNLOCK(sc);
	return error;
}