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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  tx_ant_cmd ;
struct iwm_tx_ant_cfg_cmd {int /*<<< orphan*/  valid; } ;
struct iwm_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IWM_CMD_SYNC ; 
 int /*<<< orphan*/  IWM_TX_ANT_CONFIGURATION_CMD ; 
 int /*<<< orphan*/  htole32 (int /*<<< orphan*/ ) ; 
 int iwm_mvm_send_cmd_pdu (struct iwm_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct iwm_tx_ant_cfg_cmd*) ; 

__attribute__((used)) static int
iwm_send_tx_ant_cfg(struct iwm_softc *sc, uint8_t valid_tx_ant)
{
	struct iwm_tx_ant_cfg_cmd tx_ant_cmd = {
		.valid = htole32(valid_tx_ant),
	};

	return iwm_mvm_send_cmd_pdu(sc, IWM_TX_ANT_CONFIGURATION_CMD,
	    IWM_CMD_SYNC, sizeof(tx_ant_cmd), &tx_ant_cmd);
}