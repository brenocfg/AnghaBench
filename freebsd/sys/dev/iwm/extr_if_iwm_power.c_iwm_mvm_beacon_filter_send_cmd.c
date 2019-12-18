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
struct iwm_softc {int dummy; } ;
struct iwm_beacon_filter_cmd {int /*<<< orphan*/  bf_temp_slow_filter; int /*<<< orphan*/  bf_temp_fast_filter; int /*<<< orphan*/  bf_temp_threshold; int /*<<< orphan*/  bf_roaming_state; int /*<<< orphan*/  bf_roaming_energy_delta; int /*<<< orphan*/  bf_escape_timer; int /*<<< orphan*/  bf_energy_delta; int /*<<< orphan*/  bf_enable_beacon_filter; int /*<<< orphan*/  bf_debug_flag; int /*<<< orphan*/  ba_escape_timer; int /*<<< orphan*/  ba_enable_beacon_abort; } ;

/* Variables and functions */
 int IWM_DEBUG_CMD ; 
 int IWM_DEBUG_PWRSAVE ; 
 int /*<<< orphan*/  IWM_DPRINTF (struct iwm_softc*,int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IWM_REPLY_BEACON_FILTERING_CMD ; 
 int iwm_mvm_send_cmd_pdu (struct iwm_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct iwm_beacon_filter_cmd*) ; 
 int /*<<< orphan*/  le32toh (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
iwm_mvm_beacon_filter_send_cmd(struct iwm_softc *sc,
	struct iwm_beacon_filter_cmd *cmd)
{
	int ret;

	ret = iwm_mvm_send_cmd_pdu(sc, IWM_REPLY_BEACON_FILTERING_CMD,
	    0, sizeof(struct iwm_beacon_filter_cmd), cmd);

	if (!ret) {
		IWM_DPRINTF(sc, IWM_DEBUG_PWRSAVE | IWM_DEBUG_CMD,
		    "ba_enable_beacon_abort is: %d\n",
		    le32toh(cmd->ba_enable_beacon_abort));
		IWM_DPRINTF(sc, IWM_DEBUG_PWRSAVE | IWM_DEBUG_CMD,
		    "ba_escape_timer is: %d\n",
		    le32toh(cmd->ba_escape_timer));
		IWM_DPRINTF(sc, IWM_DEBUG_PWRSAVE | IWM_DEBUG_CMD,
		    "bf_debug_flag is: %d\n",
		    le32toh(cmd->bf_debug_flag));
		IWM_DPRINTF(sc, IWM_DEBUG_PWRSAVE | IWM_DEBUG_CMD,
		    "bf_enable_beacon_filter is: %d\n",
		    le32toh(cmd->bf_enable_beacon_filter));
		IWM_DPRINTF(sc, IWM_DEBUG_PWRSAVE | IWM_DEBUG_CMD,
		    "bf_energy_delta is: %d\n",
		    le32toh(cmd->bf_energy_delta));
		IWM_DPRINTF(sc, IWM_DEBUG_PWRSAVE | IWM_DEBUG_CMD,
		    "bf_escape_timer is: %d\n",
		    le32toh(cmd->bf_escape_timer));
		IWM_DPRINTF(sc, IWM_DEBUG_PWRSAVE | IWM_DEBUG_CMD,
		    "bf_roaming_energy_delta is: %d\n",
		    le32toh(cmd->bf_roaming_energy_delta));
		IWM_DPRINTF(sc, IWM_DEBUG_PWRSAVE | IWM_DEBUG_CMD,
		    "bf_roaming_state is: %d\n",
		    le32toh(cmd->bf_roaming_state));
		IWM_DPRINTF(sc, IWM_DEBUG_PWRSAVE | IWM_DEBUG_CMD,
		    "bf_temp_threshold is: %d\n",
		    le32toh(cmd->bf_temp_threshold));
		IWM_DPRINTF(sc, IWM_DEBUG_PWRSAVE | IWM_DEBUG_CMD,
		    "bf_temp_fast_filter is: %d\n",
		    le32toh(cmd->bf_temp_fast_filter));
		IWM_DPRINTF(sc, IWM_DEBUG_PWRSAVE | IWM_DEBUG_CMD,
		    "bf_temp_slow_filter is: %d\n",
		    le32toh(cmd->bf_temp_slow_filter));
	}
	return ret;
}