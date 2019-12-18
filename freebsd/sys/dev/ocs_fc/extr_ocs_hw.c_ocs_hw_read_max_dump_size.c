#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint8_t ;
struct TYPE_8__ {int /*<<< orphan*/  buffer_length; } ;
typedef  TYPE_2__ sli4_res_common_set_dump_location_t ;
struct TYPE_7__ {scalar_t__ disable_dump_loc; } ;
struct TYPE_9__ {int /*<<< orphan*/  os; int /*<<< orphan*/  dump_size; int /*<<< orphan*/  sli; TYPE_1__ workaround; } ;
typedef  TYPE_3__ ocs_hw_t ;
typedef  int ocs_hw_rtn_e ;
struct TYPE_10__ {int /*<<< orphan*/  embed; } ;

/* Variables and functions */
 int /*<<< orphan*/  OCS_CMD_POLL ; 
 int OCS_HW_RTN_ERROR ; 
 int OCS_HW_RTN_SUCCESS ; 
 int SLI4_BMBX_SIZE ; 
 scalar_t__ SLI4_IF_TYPE_LANCER_FC_ETH ; 
 int /*<<< orphan*/  ocs_get_bus_dev_func (int /*<<< orphan*/ ,scalar_t__*,scalar_t__*,scalar_t__*) ; 
 int ocs_hw_command (TYPE_3__*,scalar_t__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ocs_log_debug (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  ocs_log_test (int /*<<< orphan*/ ,char*) ; 
 int offsetof (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_4__ payload ; 
 int /*<<< orphan*/  sli4_cmd_sli_config_t ; 
 scalar_t__ sli_cmd_common_set_dump_location (int /*<<< orphan*/ *,scalar_t__*,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ sli_get_if_type (int /*<<< orphan*/ *) ; 

__attribute__((used)) static ocs_hw_rtn_e
ocs_hw_read_max_dump_size(ocs_hw_t *hw)
{
	uint8_t	buf[SLI4_BMBX_SIZE];
	uint8_t bus, dev, func;
	int 	rc;

	/* lancer only */
	if (SLI4_IF_TYPE_LANCER_FC_ETH != sli_get_if_type(&hw->sli)) {
		ocs_log_debug(hw->os, "Function only supported for I/F type 2\n");
		return OCS_HW_RTN_ERROR;
	}

	/*
	 * Make sure the FW is new enough to support this command. If the FW
	 * is too old, the FW will UE.
	 */
	if (hw->workaround.disable_dump_loc) {
		ocs_log_test(hw->os, "FW version is too old for this feature\n");
		return OCS_HW_RTN_ERROR;
	}

	/* attempt to detemine the dump size for function 0 only. */
	ocs_get_bus_dev_func(hw->os, &bus, &dev, &func);
	if (func == 0) {
		if (sli_cmd_common_set_dump_location(&hw->sli, buf,
							SLI4_BMBX_SIZE, 1, 0, NULL, 0)) {
			sli4_res_common_set_dump_location_t *rsp =
				(sli4_res_common_set_dump_location_t *)
				(buf + offsetof(sli4_cmd_sli_config_t,
						payload.embed));

			rc = ocs_hw_command(hw, buf, OCS_CMD_POLL, NULL, NULL);
			if (rc != OCS_HW_RTN_SUCCESS) {
				ocs_log_test(hw->os, "set dump location command failed\n");
				return rc;
			} else {
				hw->dump_size = rsp->buffer_length;
				ocs_log_debug(hw->os, "Dump size %x\n", rsp->buffer_length);
			}
		}
	}
	return OCS_HW_RTN_SUCCESS;
}