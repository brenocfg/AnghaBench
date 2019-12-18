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
typedef  int uint32_t ;
struct iwm_vap {int /*<<< orphan*/  color; int /*<<< orphan*/  id; } ;
struct iwm_softc {int /*<<< orphan*/  sc_dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  ni_bssid; int /*<<< orphan*/  ni_vap; } ;
struct iwm_node {TYPE_1__ in_ni; } ;
struct iwm_mvm_add_sta_cmd {int add_modify; int /*<<< orphan*/  station_flags; int /*<<< orphan*/  addr; int /*<<< orphan*/  tfd_queue_msk; int /*<<< orphan*/  tid_disable_tx; int /*<<< orphan*/  station_flags_msk; int /*<<< orphan*/  mac_id_n_color; int /*<<< orphan*/  sta_id; } ;
typedef  scalar_t__ boolean_t ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  IEEE80211_ADDR_COPY (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IWM_ADD_STA ; 
 int IWM_ADD_STA_STATUS_MASK ; 
#define  IWM_ADD_STA_SUCCESS 128 
 int /*<<< orphan*/  IWM_DEBUG_NODE ; 
 int /*<<< orphan*/  IWM_DPRINTF (struct iwm_softc*,int /*<<< orphan*/ ,char*) ; 
 int IWM_FW_CMD_ID_AND_COLOR (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IWM_STATION_ID ; 
 int IWM_STA_FLG_AGG_MPDU_DENS_SHIFT ; 
 int IWM_STA_FLG_FAT_EN_MSK ; 
 int IWM_STA_FLG_MAX_AGG_SIZE_SHIFT ; 
 int IWM_STA_FLG_MIMO_EN_MSK ; 
 struct iwm_vap* IWM_VAP (int /*<<< orphan*/ ) ; 
 int WME_NUM_AC ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  htole16 (int) ; 
 int /*<<< orphan*/  htole32 (int) ; 
 int* iwm_mvm_ac_to_tx_fifo ; 
 int /*<<< orphan*/  iwm_mvm_add_sta_cmd_size (struct iwm_softc*) ; 
 int iwm_mvm_send_cmd_pdu_status (struct iwm_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct iwm_mvm_add_sta_cmd*,int*) ; 

int
iwm_mvm_sta_send_to_fw(struct iwm_softc *sc, struct iwm_node *in,
	boolean_t update)
{
	struct iwm_vap *ivp = IWM_VAP(in->in_ni.ni_vap);
	struct iwm_mvm_add_sta_cmd add_sta_cmd = {
		.sta_id = IWM_STATION_ID,
		.mac_id_n_color =
		    htole32(IWM_FW_CMD_ID_AND_COLOR(ivp->id, ivp->color)),
		.add_modify = update ? 1 : 0,
		.station_flags_msk = htole32(IWM_STA_FLG_FAT_EN_MSK |
					     IWM_STA_FLG_MIMO_EN_MSK),
		.tid_disable_tx = htole16(0xffff),
	};
	int ret;
	uint32_t status;
	uint32_t agg_size = 0, mpdu_dens = 0;

	if (!update) {
		int ac;
		for (ac = 0; ac < WME_NUM_AC; ac++) {
			add_sta_cmd.tfd_queue_msk |=
			    htole32(1 << iwm_mvm_ac_to_tx_fifo[ac]);
		}
		IEEE80211_ADDR_COPY(&add_sta_cmd.addr, in->in_ni.ni_bssid);
	}

	add_sta_cmd.station_flags |=
		htole32(agg_size << IWM_STA_FLG_MAX_AGG_SIZE_SHIFT);
	add_sta_cmd.station_flags |=
		htole32(mpdu_dens << IWM_STA_FLG_AGG_MPDU_DENS_SHIFT);

	status = IWM_ADD_STA_SUCCESS;
	ret = iwm_mvm_send_cmd_pdu_status(sc, IWM_ADD_STA,
					  iwm_mvm_add_sta_cmd_size(sc),
					  &add_sta_cmd, &status);
	if (ret)
		return ret;

	switch (status & IWM_ADD_STA_STATUS_MASK) {
	case IWM_ADD_STA_SUCCESS:
		IWM_DPRINTF(sc, IWM_DEBUG_NODE, "IWM_ADD_STA PASSED\n");
		break;
	default:
		ret = EIO;
		device_printf(sc->sc_dev, "IWM_ADD_STA failed\n");
		break;
	}

	return ret;
}