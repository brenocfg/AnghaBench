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
typedef  int /*<<< orphan*/  uint32_t ;
struct iwm_softc {TYPE_1__* cfg; } ;
struct iwm_nvm_data {int /*<<< orphan*/  valid_rx_ant; int /*<<< orphan*/  valid_tx_ant; int /*<<< orphan*/  radio_cfg_pnum; int /*<<< orphan*/  radio_cfg_dash; int /*<<< orphan*/  radio_cfg_step; int /*<<< orphan*/  radio_cfg_type; } ;
struct TYPE_2__ {scalar_t__ device_family; } ;

/* Variables and functions */
 scalar_t__ IWM_DEVICE_FAMILY_8000 ; 
 int /*<<< orphan*/  IWM_NVM_RF_CFG_DASH_MSK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IWM_NVM_RF_CFG_DASH_MSK_8000 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IWM_NVM_RF_CFG_FLAVOR_MSK_8000 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IWM_NVM_RF_CFG_PNUM_MSK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IWM_NVM_RF_CFG_RX_ANT_MSK_8000 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IWM_NVM_RF_CFG_STEP_MSK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IWM_NVM_RF_CFG_STEP_MSK_8000 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IWM_NVM_RF_CFG_TX_ANT_MSK_8000 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IWM_NVM_RF_CFG_TYPE_MSK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IWM_NVM_RF_CFG_TYPE_MSK_8000 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
iwm_set_radio_cfg(const struct iwm_softc *sc, struct iwm_nvm_data *data,
		  uint32_t radio_cfg)
{
	if (sc->cfg->device_family < IWM_DEVICE_FAMILY_8000) {
		data->radio_cfg_type = IWM_NVM_RF_CFG_TYPE_MSK(radio_cfg);
		data->radio_cfg_step = IWM_NVM_RF_CFG_STEP_MSK(radio_cfg);
		data->radio_cfg_dash = IWM_NVM_RF_CFG_DASH_MSK(radio_cfg);
		data->radio_cfg_pnum = IWM_NVM_RF_CFG_PNUM_MSK(radio_cfg);
		return;
	}

	/* set the radio configuration for family 8000 */
	data->radio_cfg_type = IWM_NVM_RF_CFG_TYPE_MSK_8000(radio_cfg);
	data->radio_cfg_step = IWM_NVM_RF_CFG_STEP_MSK_8000(radio_cfg);
	data->radio_cfg_dash = IWM_NVM_RF_CFG_DASH_MSK_8000(radio_cfg);
	data->radio_cfg_pnum = IWM_NVM_RF_CFG_FLAVOR_MSK_8000(radio_cfg);
	data->valid_tx_ant = IWM_NVM_RF_CFG_TX_ANT_MSK_8000(radio_cfg);
	data->valid_rx_ant = IWM_NVM_RF_CFG_RX_ANT_MSK_8000(radio_cfg);
}