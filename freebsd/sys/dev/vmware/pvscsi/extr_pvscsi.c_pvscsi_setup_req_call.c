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
struct pvscsi_softc {int dummy; } ;
struct pvscsi_cmd_desc_setup_req_call {int enable; } ;
typedef  int /*<<< orphan*/  cmd ;

/* Variables and functions */
 int /*<<< orphan*/  PVSCSI_CMD_SETUP_REQCALLTHRESHOLD ; 
 int /*<<< orphan*/  PVSCSI_REG_OFFSET_COMMAND ; 
 int /*<<< orphan*/  PVSCSI_REG_OFFSET_COMMAND_STATUS ; 
 int /*<<< orphan*/  bzero (struct pvscsi_cmd_desc_setup_req_call*,int) ; 
 int /*<<< orphan*/  pvscsi_get_tunable (struct pvscsi_softc*,char*,int /*<<< orphan*/ ) ; 
 int pvscsi_reg_read (struct pvscsi_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pvscsi_reg_write (struct pvscsi_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pvscsi_use_req_call_threshold ; 
 int /*<<< orphan*/  pvscsi_write_cmd (struct pvscsi_softc*,int /*<<< orphan*/ ,struct pvscsi_cmd_desc_setup_req_call*,int) ; 

__attribute__((used)) static int pvscsi_setup_req_call(struct pvscsi_softc *sc, uint32_t enable)
{
	uint32_t status;
	struct pvscsi_cmd_desc_setup_req_call cmd;

	if (!pvscsi_get_tunable(sc, "pvscsi_use_req_call_threshold",
	    pvscsi_use_req_call_threshold)) {
		return (0);
	}

	pvscsi_reg_write(sc, PVSCSI_REG_OFFSET_COMMAND,
	    PVSCSI_CMD_SETUP_REQCALLTHRESHOLD);
	status = pvscsi_reg_read(sc, PVSCSI_REG_OFFSET_COMMAND_STATUS);

	if (status != -1) {
		bzero(&cmd, sizeof(cmd));
		cmd.enable = enable;
		pvscsi_write_cmd(sc, PVSCSI_CMD_SETUP_REQCALLTHRESHOLD,
		    &cmd, sizeof(cmd));
		status = pvscsi_reg_read(sc, PVSCSI_REG_OFFSET_COMMAND_STATUS);

		return (status != 0);
	} else {
		return (0);
	}
}