#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  ic_vaps; } ;
struct iwm_softc {TYPE_1__ sc_ic; } ;
struct ieee80211vap {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IWM_VAP (struct ieee80211vap*) ; 
 struct ieee80211vap* TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int iwm_mvm_power_set_ba (struct iwm_softc*,int /*<<< orphan*/ ) ; 
 int iwm_mvm_power_set_ps (struct iwm_softc*) ; 

int
iwm_mvm_power_update_ps(struct iwm_softc *sc)
{
	struct ieee80211vap *vap = TAILQ_FIRST(&sc->sc_ic.ic_vaps);
	int ret;

	ret = iwm_mvm_power_set_ps(sc);
	if (ret)
		return ret;

	if (vap != NULL)
		return iwm_mvm_power_set_ba(sc, IWM_VAP(vap));

	return 0;
}