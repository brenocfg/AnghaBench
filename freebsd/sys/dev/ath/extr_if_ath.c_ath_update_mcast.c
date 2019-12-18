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
struct ieee80211com {struct ath_softc* ic_softc; } ;
struct ath_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATH_LOCK (struct ath_softc*) ; 
 int /*<<< orphan*/  ATH_UNLOCK (struct ath_softc*) ; 
 int /*<<< orphan*/  HAL_PM_AWAKE ; 
 int /*<<< orphan*/  ath_power_restore_power_state (struct ath_softc*) ; 
 int /*<<< orphan*/  ath_power_set_power_state (struct ath_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ath_update_mcast_hw (struct ath_softc*) ; 

__attribute__((used)) static void
ath_update_mcast(struct ieee80211com *ic)
{
	struct ath_softc *sc = ic->ic_softc;

	ATH_LOCK(sc);
	ath_power_set_power_state(sc, HAL_PM_AWAKE);
	ATH_UNLOCK(sc);

	ath_update_mcast_hw(sc);

	ATH_LOCK(sc);
	ath_power_restore_power_state(sc);
	ATH_UNLOCK(sc);
}