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
struct ndis_vap {int dummy; } ;
struct ndis_softc {int /*<<< orphan*/  ndis_scan_callout; } ;
struct ieee80211vap {struct ieee80211com* iv_ic; } ;
struct ieee80211com {struct ndis_softc* ic_softc; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_80211_VAP ; 
 struct ndis_vap* NDIS_VAP (struct ieee80211vap*) ; 
 int /*<<< orphan*/  callout_drain (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (struct ndis_vap*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_vap_detach (struct ieee80211vap*) ; 
 int /*<<< orphan*/  ndis_stop (struct ndis_softc*) ; 

__attribute__((used)) static void
ndis_vap_delete(struct ieee80211vap *vap)
{
	struct ndis_vap *nvp = NDIS_VAP(vap);
	struct ieee80211com *ic = vap->iv_ic;
	struct ndis_softc *sc = ic->ic_softc;

	ndis_stop(sc);
	callout_drain(&sc->ndis_scan_callout);
	ieee80211_vap_detach(vap);
	free(nvp, M_80211_VAP);
}