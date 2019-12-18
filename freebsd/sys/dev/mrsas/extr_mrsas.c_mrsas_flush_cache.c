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
struct mrsas_softc {scalar_t__ adprecovery; int /*<<< orphan*/  mrsas_dev; } ;
struct mrsas_mfi_cmd {TYPE_1__* frame; } ;
struct TYPE_4__ {int* b; } ;
struct mrsas_dcmd_frame {int cmd_status; TYPE_2__ mbox; int /*<<< orphan*/  opcode; scalar_t__ data_xfer_len; scalar_t__ pad_0; scalar_t__ timeout; int /*<<< orphan*/  flags; scalar_t__ sge_count; int /*<<< orphan*/  cmd; } ;
struct TYPE_3__ {struct mrsas_dcmd_frame dcmd; } ;

/* Variables and functions */
 int /*<<< orphan*/  MFI_CMD_DCMD ; 
 int /*<<< orphan*/  MFI_FRAME_DIR_NONE ; 
 int /*<<< orphan*/  MFI_MBOX_SIZE ; 
 scalar_t__ MRSAS_HW_CRITICAL_ERROR ; 
 int /*<<< orphan*/  MR_DCMD_CTRL_CACHE_FLUSH ; 
 int MR_FLUSH_CTRL_CACHE ; 
 int MR_FLUSH_DISK_CACHE ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct mrsas_mfi_cmd* mrsas_get_mfi_cmd (struct mrsas_softc*) ; 
 int /*<<< orphan*/  mrsas_issue_blocked_cmd (struct mrsas_softc*,struct mrsas_mfi_cmd*) ; 
 int /*<<< orphan*/  mrsas_release_mfi_cmd (struct mrsas_mfi_cmd*) ; 

__attribute__((used)) static void
mrsas_flush_cache(struct mrsas_softc *sc)
{
	struct mrsas_mfi_cmd *cmd;
	struct mrsas_dcmd_frame *dcmd;

	if (sc->adprecovery == MRSAS_HW_CRITICAL_ERROR)
		return;

	cmd = mrsas_get_mfi_cmd(sc);
	if (!cmd) {
		device_printf(sc->mrsas_dev, "Cannot allocate for flush cache cmd.\n");
		return;
	}
	dcmd = &cmd->frame->dcmd;
	memset(dcmd->mbox.b, 0, MFI_MBOX_SIZE);

	dcmd->cmd = MFI_CMD_DCMD;
	dcmd->cmd_status = 0x0;
	dcmd->sge_count = 0;
	dcmd->flags = MFI_FRAME_DIR_NONE;
	dcmd->timeout = 0;
	dcmd->pad_0 = 0;
	dcmd->data_xfer_len = 0;
	dcmd->opcode = MR_DCMD_CTRL_CACHE_FLUSH;
	dcmd->mbox.b[0] = MR_FLUSH_CTRL_CACHE | MR_FLUSH_DISK_CACHE;

	mrsas_issue_blocked_cmd(sc, cmd);
	mrsas_release_mfi_cmd(cmd);

	return;
}