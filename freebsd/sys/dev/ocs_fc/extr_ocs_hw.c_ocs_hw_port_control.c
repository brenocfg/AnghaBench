#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_15__ {int /*<<< orphan*/  if_type; } ;
struct TYPE_13__ {int /*<<< orphan*/  fw_version_too_low; } ;
struct TYPE_12__ {int /*<<< orphan*/  speed; } ;
struct TYPE_14__ {int /*<<< orphan*/  os; TYPE_4__ sli; TYPE_2__ workaround; TYPE_1__ config; } ;
typedef  TYPE_3__ ocs_hw_t ;
typedef  int /*<<< orphan*/  ocs_hw_rtn_e ;
typedef  int ocs_hw_port_e ;
typedef  int /*<<< orphan*/  ocs_hw_port_control_cb_t ;
typedef  int /*<<< orphan*/  ocs_hw_linkcfg_e ;

/* Variables and functions */
 int /*<<< orphan*/  FC_LINK_SPEED_10G ; 
 int /*<<< orphan*/  OCS_CMD_NOWAIT ; 
 int /*<<< orphan*/  OCS_FW_VER_STR (int /*<<< orphan*/ ) ; 
#define  OCS_HW_PORT_INIT 130 
#define  OCS_HW_PORT_SET_LINK_CONFIG 129 
#define  OCS_HW_PORT_SHUTDOWN 128 
 int /*<<< orphan*/  OCS_HW_RTN_ERROR ; 
 int /*<<< orphan*/  OCS_HW_RTN_NO_MEMORY ; 
 int /*<<< orphan*/  OCS_HW_RTN_SUCCESS ; 
 int /*<<< orphan*/  OCS_MIN_FW_VER_LANCER ; 
 int /*<<< orphan*/  OCS_MIN_FW_VER_SKYHAWK ; 
 int /*<<< orphan*/  OCS_M_NOWAIT ; 
 int /*<<< orphan*/  SLI4_BMBX_SIZE ; 
 int /*<<< orphan*/  SLI4_IF_TYPE_LANCER_FC_ETH ; 
 int /*<<< orphan*/  SLI_LINK_MEDIUM_FC ; 
 int /*<<< orphan*/  ocs_free (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocs_hw_cb_port_control ; 
 int /*<<< orphan*/  ocs_hw_command (TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ocs_hw_set_linkcfg (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  ocs_log_err (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  ocs_log_test (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/ * ocs_malloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sli_cmd_config_link (TYPE_4__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sli_cmd_down_link (TYPE_4__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sli_cmd_init_link (TYPE_4__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ sli_get_fw_name (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sli_get_medium (TYPE_4__*) ; 

ocs_hw_rtn_e
ocs_hw_port_control(ocs_hw_t *hw, ocs_hw_port_e ctrl, uintptr_t value, ocs_hw_port_control_cb_t cb, void *arg)
{
	ocs_hw_rtn_e rc = OCS_HW_RTN_ERROR;

	switch (ctrl) {
	case OCS_HW_PORT_INIT:
	{
		uint8_t	*init_link;
		uint32_t speed = 0;
		uint8_t reset_alpa = 0;

		if (SLI_LINK_MEDIUM_FC == sli_get_medium(&hw->sli)) {
			uint8_t	*cfg_link;

			cfg_link = ocs_malloc(hw->os, SLI4_BMBX_SIZE, OCS_M_NOWAIT);
			if (cfg_link == NULL) {
				ocs_log_err(hw->os, "no buffer for command\n");
				return OCS_HW_RTN_NO_MEMORY;
			}

			if (sli_cmd_config_link(&hw->sli, cfg_link, SLI4_BMBX_SIZE)) {
				rc = ocs_hw_command(hw, cfg_link, OCS_CMD_NOWAIT,
							ocs_hw_cb_port_control, NULL);
			}

			if (rc != OCS_HW_RTN_SUCCESS) {
				ocs_free(hw->os, cfg_link, SLI4_BMBX_SIZE);
				ocs_log_err(hw->os, "CONFIG_LINK failed\n");
				break;
			}
			speed = hw->config.speed;
			reset_alpa = (uint8_t)(value & 0xff);
		} else {
			speed = FC_LINK_SPEED_10G;
		}

		/*
		 * Bring link up, unless FW version is not supported
		 */
		if (hw->workaround.fw_version_too_low) {
			if (SLI4_IF_TYPE_LANCER_FC_ETH == hw->sli.if_type) {
				ocs_log_err(hw->os, "Cannot bring up link.  Please update firmware to %s or later (current version is %s)\n",
					OCS_FW_VER_STR(OCS_MIN_FW_VER_LANCER), (char *) sli_get_fw_name(&hw->sli,0));
			} else {
				ocs_log_err(hw->os, "Cannot bring up link.  Please update firmware to %s or later (current version is %s)\n",
					OCS_FW_VER_STR(OCS_MIN_FW_VER_SKYHAWK), (char *) sli_get_fw_name(&hw->sli, 0));
			}

			return OCS_HW_RTN_ERROR;
		}

		rc = OCS_HW_RTN_ERROR;

		/* Allocate a new buffer for the init_link command */
		init_link = ocs_malloc(hw->os, SLI4_BMBX_SIZE, OCS_M_NOWAIT);
		if (init_link == NULL) {
			ocs_log_err(hw->os, "no buffer for command\n");
			return OCS_HW_RTN_NO_MEMORY;
		}


		if (sli_cmd_init_link(&hw->sli, init_link, SLI4_BMBX_SIZE, speed, reset_alpa)) {
			rc = ocs_hw_command(hw, init_link, OCS_CMD_NOWAIT,
						ocs_hw_cb_port_control, NULL);
		}
		/* Free buffer on error, since no callback is coming */
		if (rc != OCS_HW_RTN_SUCCESS) {
			ocs_free(hw->os, init_link, SLI4_BMBX_SIZE);
			ocs_log_err(hw->os, "INIT_LINK failed\n");
		}
		break;
	}
	case OCS_HW_PORT_SHUTDOWN:
	{
		uint8_t	*down_link;

		down_link = ocs_malloc(hw->os, SLI4_BMBX_SIZE, OCS_M_NOWAIT);
		if (down_link == NULL) {
			ocs_log_err(hw->os, "no buffer for command\n");
			return OCS_HW_RTN_NO_MEMORY;
		}
		if (sli_cmd_down_link(&hw->sli, down_link, SLI4_BMBX_SIZE)) {
			rc = ocs_hw_command(hw, down_link, OCS_CMD_NOWAIT,
						ocs_hw_cb_port_control, NULL);
		}
		/* Free buffer on error, since no callback is coming */
		if (rc != OCS_HW_RTN_SUCCESS) {
			ocs_free(hw->os, down_link, SLI4_BMBX_SIZE);
			ocs_log_err(hw->os, "DOWN_LINK failed\n");
		}
		break;
	}
	case OCS_HW_PORT_SET_LINK_CONFIG:
		rc = ocs_hw_set_linkcfg(hw, (ocs_hw_linkcfg_e)value, OCS_CMD_NOWAIT, cb, arg);
		break;
	default:
		ocs_log_test(hw->os, "unhandled control %#x\n", ctrl);
		break;
	}

	return rc;
}