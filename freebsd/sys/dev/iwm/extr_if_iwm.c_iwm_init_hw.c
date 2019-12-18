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
struct ieee80211com {int /*<<< orphan*/ * ic_channels; } ;
struct iwm_softc {int /*<<< orphan*/  sc_dev; TYPE_1__* cfg; int /*<<< orphan*/ * sc_phyctxt; int /*<<< orphan*/  sc_phy_db; int /*<<< orphan*/  sc_ps_disabled; int /*<<< orphan*/  sf_state; struct ieee80211com sc_ic; } ;
struct TYPE_2__ {scalar_t__ device_family; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ IWM_DEVICE_FAMILY_7000 ; 
 int IWM_NUM_PHY_CTX ; 
 int /*<<< orphan*/  IWM_SF_UNINIT ; 
 int /*<<< orphan*/  IWM_STATION_ID ; 
 int /*<<< orphan*/  IWM_UCODE_REGULAR ; 
 int /*<<< orphan*/  IWM_UCODE_TLV_CAPA_UMAC_SCAN ; 
 int WME_NUM_AC ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int iwm_enable_txq (struct iwm_softc*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 scalar_t__ iwm_fw_has_capa (struct iwm_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * iwm_mvm_ac_to_tx_fifo ; 
 int iwm_mvm_add_aux_sta (struct iwm_softc*) ; 
 scalar_t__ iwm_mvm_config_ltr (struct iwm_softc*) ; 
 int iwm_mvm_config_umac_scan (struct iwm_softc*) ; 
 int iwm_mvm_disable_beacon_filter (struct iwm_softc*) ; 
 int /*<<< orphan*/  iwm_mvm_get_valid_tx_ant (struct iwm_softc*) ; 
 int iwm_mvm_load_ucode_wait_alive (struct iwm_softc*,int /*<<< orphan*/ ) ; 
 int iwm_mvm_phy_ctxt_add (struct iwm_softc*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int) ; 
 int iwm_mvm_power_update_device (struct iwm_softc*) ; 
 int iwm_mvm_sf_update (struct iwm_softc*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iwm_mvm_tt_tx_backoff (struct iwm_softc*,int /*<<< orphan*/ ) ; 
 int iwm_run_init_mvm_ucode (struct iwm_softc*,int /*<<< orphan*/ ) ; 
 int iwm_send_bt_init_conf (struct iwm_softc*) ; 
 int iwm_send_phy_cfg_cmd (struct iwm_softc*) ; 
 int iwm_send_phy_db_data (int /*<<< orphan*/ ) ; 
 int iwm_send_tx_ant_cfg (struct iwm_softc*,int /*<<< orphan*/ ) ; 
 int iwm_send_update_mcc_cmd (struct iwm_softc*,char*) ; 
 int iwm_start_hw (struct iwm_softc*) ; 
 int /*<<< orphan*/  iwm_stop_device (struct iwm_softc*) ; 
 int /*<<< orphan*/  printf (char*,int) ; 

__attribute__((used)) static int
iwm_init_hw(struct iwm_softc *sc)
{
	struct ieee80211com *ic = &sc->sc_ic;
	int error, i, ac;

	sc->sf_state = IWM_SF_UNINIT;

	if ((error = iwm_start_hw(sc)) != 0) {
		printf("iwm_start_hw: failed %d\n", error);
		return error;
	}

	if ((error = iwm_run_init_mvm_ucode(sc, 0)) != 0) {
		printf("iwm_run_init_mvm_ucode: failed %d\n", error);
		return error;
	}

	/*
	 * should stop and start HW since that INIT
	 * image just loaded
	 */
	iwm_stop_device(sc);
	sc->sc_ps_disabled = FALSE;
	if ((error = iwm_start_hw(sc)) != 0) {
		device_printf(sc->sc_dev, "could not initialize hardware\n");
		return error;
	}

	/* omstart, this time with the regular firmware */
	error = iwm_mvm_load_ucode_wait_alive(sc, IWM_UCODE_REGULAR);
	if (error) {
		device_printf(sc->sc_dev, "could not load firmware\n");
		goto error;
	}

	error = iwm_mvm_sf_update(sc, NULL, FALSE);
	if (error)
		device_printf(sc->sc_dev, "Failed to initialize Smart Fifo\n");

	if ((error = iwm_send_bt_init_conf(sc)) != 0) {
		device_printf(sc->sc_dev, "bt init conf failed\n");
		goto error;
	}

	error = iwm_send_tx_ant_cfg(sc, iwm_mvm_get_valid_tx_ant(sc));
	if (error != 0) {
		device_printf(sc->sc_dev, "antenna config failed\n");
		goto error;
	}

	/* Send phy db control command and then phy db calibration */
	if ((error = iwm_send_phy_db_data(sc->sc_phy_db)) != 0)
		goto error;

	if ((error = iwm_send_phy_cfg_cmd(sc)) != 0) {
		device_printf(sc->sc_dev, "phy_cfg_cmd failed\n");
		goto error;
	}

	/* Add auxiliary station for scanning */
	if ((error = iwm_mvm_add_aux_sta(sc)) != 0) {
		device_printf(sc->sc_dev, "add_aux_sta failed\n");
		goto error;
	}

	for (i = 0; i < IWM_NUM_PHY_CTX; i++) {
		/*
		 * The channel used here isn't relevant as it's
		 * going to be overwritten in the other flows.
		 * For now use the first channel we have.
		 */
		if ((error = iwm_mvm_phy_ctxt_add(sc,
		    &sc->sc_phyctxt[i], &ic->ic_channels[1], 1, 1)) != 0)
			goto error;
	}

	/* Initialize tx backoffs to the minimum. */
	if (sc->cfg->device_family == IWM_DEVICE_FAMILY_7000)
		iwm_mvm_tt_tx_backoff(sc, 0);

	if (iwm_mvm_config_ltr(sc) != 0)
		device_printf(sc->sc_dev, "PCIe LTR configuration failed\n");

	error = iwm_mvm_power_update_device(sc);
	if (error)
		goto error;

	if ((error = iwm_send_update_mcc_cmd(sc, "ZZ")) != 0)
		goto error;

	if (iwm_fw_has_capa(sc, IWM_UCODE_TLV_CAPA_UMAC_SCAN)) {
		if ((error = iwm_mvm_config_umac_scan(sc)) != 0)
			goto error;
	}

	/* Enable Tx queues. */
	for (ac = 0; ac < WME_NUM_AC; ac++) {
		error = iwm_enable_txq(sc, IWM_STATION_ID, ac,
		    iwm_mvm_ac_to_tx_fifo[ac]);
		if (error)
			goto error;
	}

	if ((error = iwm_mvm_disable_beacon_filter(sc)) != 0) {
		device_printf(sc->sc_dev, "failed to disable beacon filter\n");
		goto error;
	}

	return 0;

 error:
	iwm_stop_device(sc);
	return error;
}