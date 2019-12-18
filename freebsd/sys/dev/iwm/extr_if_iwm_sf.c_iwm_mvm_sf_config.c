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
struct iwm_softc {int sf_state; int /*<<< orphan*/  sc_dev; TYPE_1__* cfg; } ;
struct iwm_sf_cfg_cmd {int /*<<< orphan*/  state; } ;
struct ieee80211_node {int dummy; } ;
typedef  int /*<<< orphan*/  sf_cmd ;
typedef  enum iwm_sf_state { ____Placeholder_iwm_sf_state } iwm_sf_state ;
struct TYPE_2__ {scalar_t__ disable_dummy_notification; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  IWM_CMD_ASYNC ; 
 int /*<<< orphan*/  IWM_REPLY_SF_CFG_CMD ; 
 int IWM_SF_CFG_DUMMY_NOTIF_OFF ; 
#define  IWM_SF_FULL_ON 130 
#define  IWM_SF_INIT_OFF 129 
#define  IWM_SF_UNINIT 128 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  htole32 (int) ; 
 int /*<<< orphan*/  iwm_mvm_fill_sf_command (struct iwm_softc*,struct iwm_sf_cfg_cmd*,struct ieee80211_node*) ; 
 int iwm_mvm_send_cmd_pdu (struct iwm_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct iwm_sf_cfg_cmd*) ; 

__attribute__((used)) static int
iwm_mvm_sf_config(struct iwm_softc *sc, struct ieee80211_node *ni,
	enum iwm_sf_state new_state)
{
	struct iwm_sf_cfg_cmd sf_cmd = {
		.state = htole32(new_state),
	};
	int ret = 0;

#ifdef notyet	/* only relevant for sdio variants */
	if (sc->cfg->disable_dummy_notification)
		sf_cmd.state |= htole32(IWM_SF_CFG_DUMMY_NOTIF_OFF);
#endif

	/*
	 * If an associated AP sta changed its antenna configuration, the state
	 * will remain FULL_ON but SF parameters need to be reconsidered.
	 */
	if (new_state != IWM_SF_FULL_ON && sc->sf_state == new_state)
		return 0;

	switch (new_state) {
	case IWM_SF_UNINIT:
		iwm_mvm_fill_sf_command(sc, &sf_cmd, NULL);
		break;
	case IWM_SF_FULL_ON:
		iwm_mvm_fill_sf_command(sc, &sf_cmd, ni);
		break;
	case IWM_SF_INIT_OFF:
		iwm_mvm_fill_sf_command(sc, &sf_cmd, NULL);
		break;
	default:
		device_printf(sc->sc_dev,
		    "Invalid state: %d. not sending Smart Fifo cmd\n",
		    new_state);
		return EINVAL;
	}

	ret = iwm_mvm_send_cmd_pdu(sc, IWM_REPLY_SF_CFG_CMD, IWM_CMD_ASYNC,
				   sizeof(sf_cmd), &sf_cmd);
	if (!ret)
		sc->sf_state = new_state;

	return ret;
}