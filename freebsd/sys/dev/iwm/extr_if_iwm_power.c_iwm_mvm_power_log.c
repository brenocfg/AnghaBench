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
struct iwm_mac_power_cmd {int flags; int keep_alive_seconds; int /*<<< orphan*/  skip_dtim_periods; int /*<<< orphan*/  tx_data_timeout; int /*<<< orphan*/  rx_data_timeout; int /*<<< orphan*/  id_and_color; } ;

/* Variables and functions */
 int IWM_DEBUG_CMD ; 
 int IWM_DEBUG_PWRSAVE ; 
 int /*<<< orphan*/  IWM_DPRINTF (struct iwm_softc*,int,char*,...) ; 
 int /*<<< orphan*/  IWM_POWER_FLAGS_POWER_MANAGEMENT_ENA_MSK ; 
 int /*<<< orphan*/  IWM_POWER_FLAGS_SKIP_OVER_DTIM_MSK ; 
 int htole16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iwm_power_scheme ; 
 int /*<<< orphan*/  le16toh (int) ; 
 int /*<<< orphan*/  le32toh (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
iwm_mvm_power_log(struct iwm_softc *sc, struct iwm_mac_power_cmd *cmd)
{
	IWM_DPRINTF(sc, IWM_DEBUG_PWRSAVE | IWM_DEBUG_CMD,
	    "Sending power table command on mac id 0x%X for "
	    "power level %d, flags = 0x%X\n",
	    cmd->id_and_color, iwm_power_scheme, le16toh(cmd->flags));
	IWM_DPRINTF(sc, IWM_DEBUG_PWRSAVE | IWM_DEBUG_CMD,
	    "Keep alive = %u sec\n", le16toh(cmd->keep_alive_seconds));

	if (!(cmd->flags & htole16(IWM_POWER_FLAGS_POWER_MANAGEMENT_ENA_MSK))) {
		IWM_DPRINTF(sc, IWM_DEBUG_PWRSAVE | IWM_DEBUG_CMD,
		    "Disable power management\n");
		return;
	}

	IWM_DPRINTF(sc, IWM_DEBUG_PWRSAVE | IWM_DEBUG_CMD,
	    "Rx timeout = %u usec\n", le32toh(cmd->rx_data_timeout));
	IWM_DPRINTF(sc, IWM_DEBUG_PWRSAVE | IWM_DEBUG_CMD,
	    "Tx timeout = %u usec\n", le32toh(cmd->tx_data_timeout));
	if (cmd->flags & htole16(IWM_POWER_FLAGS_SKIP_OVER_DTIM_MSK))
		IWM_DPRINTF(sc, IWM_DEBUG_PWRSAVE | IWM_DEBUG_CMD,
		    "DTIM periods to skip = %u\n", cmd->skip_dtim_periods);
}