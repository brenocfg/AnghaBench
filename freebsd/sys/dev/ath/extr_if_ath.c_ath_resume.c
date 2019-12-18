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
struct ieee80211com {int /*<<< orphan*/ * ic_curchan; } ;
struct ath_softc {int sc_rx_stopped; int sc_rx_resetted; scalar_t__ sc_resume_up; struct ath_hal* sc_ah; scalar_t__ sc_tdma; scalar_t__ sc_hasenforcetxop; int /*<<< orphan*/ * sc_curchan; int /*<<< orphan*/  sc_opmode; int /*<<< orphan*/  sc_cur_rxchainmask; int /*<<< orphan*/  sc_cur_txchainmask; struct ieee80211com sc_ic; } ;
struct ath_hal {int dummy; } ;
typedef  int /*<<< orphan*/  HAL_STATUS ;

/* Variables and functions */
 int /*<<< orphan*/  AH_FALSE ; 
 int /*<<< orphan*/  ATH_LOCK (struct ath_softc*) ; 
 int /*<<< orphan*/  ATH_RX_LOCK (struct ath_softc*) ; 
 int /*<<< orphan*/  ATH_RX_UNLOCK (struct ath_softc*) ; 
 int /*<<< orphan*/  ATH_UNLOCK (struct ath_softc*) ; 
 int /*<<< orphan*/  HAL_LED_INIT ; 
 int /*<<< orphan*/  HAL_PM_AWAKE ; 
 int /*<<< orphan*/  HAL_RESET_NORMAL ; 
 int /*<<< orphan*/  ath_btcoex_enable (struct ath_softc*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ath_dfs_radar_enable (struct ath_softc*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ath_hal_enablepcie (struct ath_hal*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ath_hal_reset (struct ath_hal*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ath_hal_setchainmasks (struct ath_hal*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ath_hal_setenforcetxop (struct ath_hal*,int) ; 
 int /*<<< orphan*/  ath_hal_setledstate (struct ath_hal*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ath_led_config (struct ath_softc*) ; 
 int /*<<< orphan*/  ath_power_restore_power_state (struct ath_softc*) ; 
 int /*<<< orphan*/  ath_power_set_power_state (struct ath_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ath_power_setpower (struct ath_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ath_power_setselfgen (struct ath_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ath_reset_keycache (struct ath_softc*) ; 
 int /*<<< orphan*/  ath_spectral_enable (struct ath_softc*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ath_update_chainmasks (struct ath_softc*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ieee80211_resume_all (struct ieee80211com*) ; 

void
ath_resume(struct ath_softc *sc)
{
	struct ieee80211com *ic = &sc->sc_ic;
	struct ath_hal *ah = sc->sc_ah;
	HAL_STATUS status;

	ath_hal_enablepcie(ah, 0, 0);

	/*
	 * Must reset the chip before we reload the
	 * keycache as we were powered down on suspend.
	 */
	ath_update_chainmasks(sc,
	    sc->sc_curchan != NULL ? sc->sc_curchan : ic->ic_curchan);
	ath_hal_setchainmasks(sc->sc_ah, sc->sc_cur_txchainmask,
	    sc->sc_cur_rxchainmask);

	/* Ensure we set the current power state to on */
	ATH_LOCK(sc);
	ath_power_setselfgen(sc, HAL_PM_AWAKE);
	ath_power_set_power_state(sc, HAL_PM_AWAKE);
	ath_power_setpower(sc, HAL_PM_AWAKE, 1);
	ATH_UNLOCK(sc);

	ath_hal_reset(ah, sc->sc_opmode,
	    sc->sc_curchan != NULL ? sc->sc_curchan : ic->ic_curchan,
	    AH_FALSE, HAL_RESET_NORMAL, &status);
	ath_reset_keycache(sc);

	ATH_RX_LOCK(sc);
	sc->sc_rx_stopped = 1;
	sc->sc_rx_resetted = 1;
	ATH_RX_UNLOCK(sc);

	/* Let DFS at it in case it's a DFS channel */
	ath_dfs_radar_enable(sc, ic->ic_curchan);

	/* Let spectral at in case spectral is enabled */
	ath_spectral_enable(sc, ic->ic_curchan);

	/*
	 * Let bluetooth coexistence at in case it's needed for this channel
	 */
	ath_btcoex_enable(sc, ic->ic_curchan);

	/*
	 * If we're doing TDMA, enforce the TXOP limitation for chips that
	 * support it.
	 */
	if (sc->sc_hasenforcetxop && sc->sc_tdma)
		ath_hal_setenforcetxop(sc->sc_ah, 1);
	else
		ath_hal_setenforcetxop(sc->sc_ah, 0);

	/* Restore the LED configuration */
	ath_led_config(sc);
	ath_hal_setledstate(ah, HAL_LED_INIT);

	if (sc->sc_resume_up)
		ieee80211_resume_all(ic);

	ATH_LOCK(sc);
	ath_power_restore_power_state(sc);
	ATH_UNLOCK(sc);

	/* XXX beacons ? */
}