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
struct ieee80211vap {int iv_flags; scalar_t__ iv_dtim_period; struct ieee80211_node* iv_bss; } ;
struct iwm_vap {int /*<<< orphan*/  color; int /*<<< orphan*/  id; struct ieee80211vap iv_vap; } ;
struct iwm_softc {scalar_t__ sc_ps_disabled; } ;
struct iwm_mac_power_cmd {void* tx_data_timeout; void* rx_data_timeout; int /*<<< orphan*/  flags; int /*<<< orphan*/  keep_alive_seconds; void* id_and_color; } ;
struct ieee80211_node {int ni_intval; } ;
typedef  int /*<<< orphan*/  boolean_t ;
struct TYPE_2__ {scalar_t__ in_assoc; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int IEEE80211_F_PMGTON ; 
 int /*<<< orphan*/  IWM_FW_CMD_ID_AND_COLOR (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IWM_MVM_DEFAULT_PS_RX_DATA_TIMEOUT ; 
 int /*<<< orphan*/  IWM_MVM_DEFAULT_PS_TX_DATA_TIMEOUT ; 
 TYPE_1__* IWM_NODE (struct ieee80211_node*) ; 
 int IWM_POWER_FLAGS_POWER_MANAGEMENT_ENA_MSK ; 
 int IWM_POWER_FLAGS_POWER_SAVE_ENA_MSK ; 
 int IWM_POWER_KEEP_ALIVE_PERIOD_SEC ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  htole16 (int) ; 
 void* htole32 (int /*<<< orphan*/ ) ; 
 int imax (int,int) ; 
 int /*<<< orphan*/  iwm_mvm_power_config_skip_dtim (struct iwm_softc*,struct iwm_mac_power_cmd*) ; 
 int roundup (int,int) ; 

__attribute__((used)) static void
iwm_mvm_power_build_cmd(struct iwm_softc *sc, struct iwm_vap *ivp,
	struct iwm_mac_power_cmd *cmd)
{
	struct ieee80211vap *vap = &ivp->iv_vap;
	struct ieee80211_node *ni = vap->iv_bss;
	int dtimper, dtimper_msec;
	int keep_alive;
	boolean_t bss_conf_ps = FALSE;

	cmd->id_and_color = htole32(IWM_FW_CMD_ID_AND_COLOR(ivp->id,
	    ivp->color));
	dtimper = vap->iv_dtim_period ?: 1;

	/*
	 * Regardless of power management state the driver must set
	 * keep alive period. FW will use it for sending keep alive NDPs
	 * immediately after association. Check that keep alive period
	 * is at least 3 * DTIM
	 */
	dtimper_msec = dtimper * ni->ni_intval;
	keep_alive
	    = imax(3 * dtimper_msec, 1000 * IWM_POWER_KEEP_ALIVE_PERIOD_SEC);
	keep_alive = roundup(keep_alive, 1000) / 1000;
	cmd->keep_alive_seconds = htole16(keep_alive);

	if (sc->sc_ps_disabled)
		return;

	cmd->flags |= htole16(IWM_POWER_FLAGS_POWER_SAVE_ENA_MSK);

	if (IWM_NODE(ni)->in_assoc &&
	    (vap->iv_flags & IEEE80211_F_PMGTON) != 0) {
		bss_conf_ps = TRUE;
	}
	if (!bss_conf_ps)
		return;

	cmd->flags |= htole16(IWM_POWER_FLAGS_POWER_MANAGEMENT_ENA_MSK);

	iwm_mvm_power_config_skip_dtim(sc, cmd);

	cmd->rx_data_timeout =
		htole32(IWM_MVM_DEFAULT_PS_RX_DATA_TIMEOUT);
	cmd->tx_data_timeout =
		htole32(IWM_MVM_DEFAULT_PS_TX_DATA_TIMEOUT);
}