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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct iwm_softc {int /*<<< orphan*/  sc_dev; TYPE_1__* cfg; } ;
struct iwm_mvm_add_sta_cmd {scalar_t__ sta_id; int /*<<< orphan*/  addr; int /*<<< orphan*/  tid_disable_tx; void* tfd_queue_msk; int /*<<< orphan*/  station_type; void* mac_id_n_color; } ;
struct iwm_int_sta {scalar_t__ sta_id; int /*<<< orphan*/  tfd_queue_msk; } ;
typedef  int /*<<< orphan*/  cmd ;
struct TYPE_2__ {scalar_t__ mqrx_supported; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  IEEE80211_ADDR_COPY (int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  IWM_ADD_STA ; 
 int IWM_ADD_STA_STATUS_MASK ; 
#define  IWM_ADD_STA_SUCCESS 128 
 scalar_t__ IWM_AUX_STA_ID ; 
 int /*<<< orphan*/  IWM_DEBUG_NODE ; 
 int /*<<< orphan*/  IWM_DPRINTF (struct iwm_softc*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  IWM_FW_CMD_ID_AND_COLOR (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IWM_STA_AUX_ACTIVITY ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  htole16 (int) ; 
 void* htole32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iwm_mvm_add_sta_cmd_size (struct iwm_softc*) ; 
 int iwm_mvm_send_cmd_pdu_status (struct iwm_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct iwm_mvm_add_sta_cmd*,int*) ; 
 int /*<<< orphan*/  memset (struct iwm_mvm_add_sta_cmd*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
iwm_mvm_add_int_sta_common(struct iwm_softc *sc, struct iwm_int_sta *sta,
    const uint8_t *addr, uint16_t mac_id, uint16_t color)
{
	struct iwm_mvm_add_sta_cmd cmd;
	int ret;
	uint32_t status;

	memset(&cmd, 0, sizeof(cmd));
	cmd.sta_id = sta->sta_id;
	cmd.mac_id_n_color = htole32(IWM_FW_CMD_ID_AND_COLOR(mac_id, color));
	if (sta->sta_id == IWM_AUX_STA_ID && sc->cfg->mqrx_supported)
		cmd.station_type = IWM_STA_AUX_ACTIVITY;

	cmd.tfd_queue_msk = htole32(sta->tfd_queue_msk);
	cmd.tid_disable_tx = htole16(0xffff);

	if (addr)
		IEEE80211_ADDR_COPY(cmd.addr, addr);

	ret = iwm_mvm_send_cmd_pdu_status(sc, IWM_ADD_STA,
					  iwm_mvm_add_sta_cmd_size(sc),
					  &cmd, &status);
	if (ret)
		return ret;

	switch (status & IWM_ADD_STA_STATUS_MASK) {
	case IWM_ADD_STA_SUCCESS:
		IWM_DPRINTF(sc, IWM_DEBUG_NODE, "Internal station added.\n");
		return 0;
	default:
		ret = EIO;
		device_printf(sc->sc_dev,
		    "Add internal station failed, status=0x%x\n", status);
		break;
	}
	return ret;
}