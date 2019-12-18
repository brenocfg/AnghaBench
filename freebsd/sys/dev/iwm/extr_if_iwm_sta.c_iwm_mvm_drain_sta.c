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
typedef  int uint32_t ;
struct iwm_vap {int /*<<< orphan*/  color; int /*<<< orphan*/  id; } ;
struct iwm_softc {int /*<<< orphan*/  sc_dev; } ;
struct iwm_mvm_add_sta_cmd {void* station_flags_msk; void* station_flags; int /*<<< orphan*/  add_modify; int /*<<< orphan*/  sta_id; void* mac_id_n_color; } ;
typedef  scalar_t__ boolean_t ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  IWM_ADD_STA ; 
 int IWM_ADD_STA_STATUS_MASK ; 
#define  IWM_ADD_STA_SUCCESS 128 
 int /*<<< orphan*/  IWM_DEBUG_NODE ; 
 int /*<<< orphan*/  IWM_DPRINTF (struct iwm_softc*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IWM_FW_CMD_ID_AND_COLOR (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IWM_STATION_ID ; 
 int /*<<< orphan*/  IWM_STA_FLG_DRAIN_FLOW ; 
 int /*<<< orphan*/  IWM_STA_MODE_MODIFY ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 void* htole32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iwm_mvm_add_sta_cmd_size (struct iwm_softc*) ; 
 int iwm_mvm_send_cmd_pdu_status (struct iwm_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct iwm_mvm_add_sta_cmd*,int*) ; 

int
iwm_mvm_drain_sta(struct iwm_softc *sc, struct iwm_vap *ivp, boolean_t drain)
{
	struct iwm_mvm_add_sta_cmd cmd = {};
	int ret;
	uint32_t status;

	cmd.mac_id_n_color =
	    htole32(IWM_FW_CMD_ID_AND_COLOR(ivp->id, ivp->color));
	cmd.sta_id = IWM_STATION_ID;
	cmd.add_modify = IWM_STA_MODE_MODIFY;
	cmd.station_flags = drain ? htole32(IWM_STA_FLG_DRAIN_FLOW) : 0;
	cmd.station_flags_msk = htole32(IWM_STA_FLG_DRAIN_FLOW);

	status = IWM_ADD_STA_SUCCESS;
	ret = iwm_mvm_send_cmd_pdu_status(sc, IWM_ADD_STA,
					  iwm_mvm_add_sta_cmd_size(sc),
					  &cmd, &status);
	if (ret)
		return ret;

	switch (status & IWM_ADD_STA_STATUS_MASK) {
	case IWM_ADD_STA_SUCCESS:
		IWM_DPRINTF(sc, IWM_DEBUG_NODE,
		    "Frames for staid %d will drained in fw\n", IWM_STATION_ID);
		break;
	default:
		ret = EIO;
		device_printf(sc->sc_dev,
		    "Couldn't drain frames for staid %d\n", IWM_STATION_ID);
		break;
	}

	return ret;
}