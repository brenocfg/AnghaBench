#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_int32_t ;
struct mrsas_softc {scalar_t__ adprecovery; int /*<<< orphan*/  mrsas_dev; scalar_t__ jbod_seq_cmd; scalar_t__ map_update_cmd; scalar_t__ aen_cmd; } ;
struct mrsas_mfi_cmd {TYPE_1__* frame; } ;
struct TYPE_4__ {int /*<<< orphan*/  b; } ;
struct mrsas_dcmd_frame {int cmd_status; int /*<<< orphan*/  opcode; scalar_t__ data_xfer_len; scalar_t__ pad_0; scalar_t__ timeout; int /*<<< orphan*/  flags; scalar_t__ sge_count; int /*<<< orphan*/  cmd; TYPE_2__ mbox; } ;
struct TYPE_3__ {struct mrsas_dcmd_frame dcmd; } ;

/* Variables and functions */
 int /*<<< orphan*/  MFI_CMD_DCMD ; 
 int /*<<< orphan*/  MFI_FRAME_DIR_NONE ; 
 int /*<<< orphan*/  MFI_MBOX_SIZE ; 
 scalar_t__ MRSAS_HW_CRITICAL_ERROR ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct mrsas_mfi_cmd* mrsas_get_mfi_cmd (struct mrsas_softc*) ; 
 int /*<<< orphan*/  mrsas_issue_blocked_abort_cmd (struct mrsas_softc*,scalar_t__) ; 
 int /*<<< orphan*/  mrsas_issue_blocked_cmd (struct mrsas_softc*,struct mrsas_mfi_cmd*) ; 
 int /*<<< orphan*/  mrsas_release_mfi_cmd (struct mrsas_mfi_cmd*) ; 

__attribute__((used)) static void
mrsas_shutdown_ctlr(struct mrsas_softc *sc, u_int32_t opcode)
{
	struct mrsas_mfi_cmd *cmd;
	struct mrsas_dcmd_frame *dcmd;

	if (sc->adprecovery == MRSAS_HW_CRITICAL_ERROR)
		return;

	cmd = mrsas_get_mfi_cmd(sc);
	if (!cmd) {
		device_printf(sc->mrsas_dev, "Cannot allocate for shutdown cmd.\n");
		return;
	}
	if (sc->aen_cmd)
		mrsas_issue_blocked_abort_cmd(sc, sc->aen_cmd);
	if (sc->map_update_cmd)
		mrsas_issue_blocked_abort_cmd(sc, sc->map_update_cmd);
	if (sc->jbod_seq_cmd)
		mrsas_issue_blocked_abort_cmd(sc, sc->jbod_seq_cmd);

	dcmd = &cmd->frame->dcmd;
	memset(dcmd->mbox.b, 0, MFI_MBOX_SIZE);

	dcmd->cmd = MFI_CMD_DCMD;
	dcmd->cmd_status = 0x0;
	dcmd->sge_count = 0;
	dcmd->flags = MFI_FRAME_DIR_NONE;
	dcmd->timeout = 0;
	dcmd->pad_0 = 0;
	dcmd->data_xfer_len = 0;
	dcmd->opcode = opcode;

	device_printf(sc->mrsas_dev, "Preparing to shut down controller.\n");

	mrsas_issue_blocked_cmd(sc, cmd);
	mrsas_release_mfi_cmd(cmd);

	return;
}