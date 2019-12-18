#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_9__ ;
typedef  struct TYPE_17__   TYPE_8__ ;
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int u_int8_t ;
struct mrsas_softc {int /*<<< orphan*/  mask_interrupts; int /*<<< orphan*/  do_timedout_reset; TYPE_9__* ctrl_info; int /*<<< orphan*/  disableOnlineCtrlReset; int /*<<< orphan*/  support_morethan256jbod; int /*<<< orphan*/  use_seqnum_jbod_fp; int /*<<< orphan*/  ctlr_info_mem; int /*<<< orphan*/  ctlr_info_phys_addr; int /*<<< orphan*/  mrsas_dev; } ;
struct mrsas_mfi_cmd {TYPE_1__* frame; } ;
struct TYPE_13__ {TYPE_3__* sge32; } ;
struct TYPE_11__ {int /*<<< orphan*/  b; } ;
struct mrsas_dcmd_frame {int cmd_status; int sge_count; int data_xfer_len; TYPE_4__ sgl; int /*<<< orphan*/  opcode; scalar_t__ pad_0; scalar_t__ timeout; int /*<<< orphan*/  flags; int /*<<< orphan*/  cmd; TYPE_2__ mbox; } ;
struct mrsas_ctrl_info {int dummy; } ;
struct TYPE_16__ {int /*<<< orphan*/  disableOnlineCtrlReset; } ;
struct TYPE_17__ {TYPE_7__ OnOffProperties; } ;
struct TYPE_15__ {int /*<<< orphan*/  supportPdMapTargetId; } ;
struct TYPE_14__ {int /*<<< orphan*/  useSeqNumJbodFP; } ;
struct TYPE_18__ {TYPE_8__ properties; TYPE_6__ adapterOperations4; TYPE_5__ adapterOperations3; } ;
struct TYPE_12__ {int length; int /*<<< orphan*/  phys_addr; } ;
struct TYPE_10__ {struct mrsas_dcmd_frame dcmd; } ;

/* Variables and functions */
 int ENOMEM ; 
 int ETIMEDOUT ; 
 int /*<<< orphan*/  MFI_CMD_DCMD ; 
 int /*<<< orphan*/  MFI_DCMD_TIMEOUT_OCR ; 
 int /*<<< orphan*/  MFI_FRAME_DIR_READ ; 
 int /*<<< orphan*/  MFI_MBOX_SIZE ; 
 int /*<<< orphan*/  MR_DCMD_CTRL_GET_INFO ; 
 scalar_t__ SUCCESS ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  memcpy (TYPE_9__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ mrsas_alloc_ctlr_info_cmd (struct mrsas_softc*) ; 
 int /*<<< orphan*/  mrsas_free_ctlr_info_cmd (struct mrsas_softc*) ; 
 struct mrsas_mfi_cmd* mrsas_get_mfi_cmd (struct mrsas_softc*) ; 
 int mrsas_issue_blocked_cmd (struct mrsas_softc*,struct mrsas_mfi_cmd*) ; 
 int mrsas_issue_polled (struct mrsas_softc*,struct mrsas_mfi_cmd*) ; 
 int /*<<< orphan*/  mrsas_release_mfi_cmd (struct mrsas_mfi_cmd*) ; 
 int /*<<< orphan*/  mrsas_update_ext_vd_details (struct mrsas_softc*) ; 

__attribute__((used)) static int
mrsas_get_ctrl_info(struct mrsas_softc *sc)
{
	int retcode = 0;
	u_int8_t do_ocr = 1;
	struct mrsas_mfi_cmd *cmd;
	struct mrsas_dcmd_frame *dcmd;

	cmd = mrsas_get_mfi_cmd(sc);

	if (!cmd) {
		device_printf(sc->mrsas_dev, "Failed to get a free cmd\n");
		return -ENOMEM;
	}
	dcmd = &cmd->frame->dcmd;

	if (mrsas_alloc_ctlr_info_cmd(sc) != SUCCESS) {
		device_printf(sc->mrsas_dev, "Cannot allocate get ctlr info cmd\n");
		mrsas_release_mfi_cmd(cmd);
		return -ENOMEM;
	}
	memset(dcmd->mbox.b, 0, MFI_MBOX_SIZE);

	dcmd->cmd = MFI_CMD_DCMD;
	dcmd->cmd_status = 0xFF;
	dcmd->sge_count = 1;
	dcmd->flags = MFI_FRAME_DIR_READ;
	dcmd->timeout = 0;
	dcmd->pad_0 = 0;
	dcmd->data_xfer_len = sizeof(struct mrsas_ctrl_info);
	dcmd->opcode = MR_DCMD_CTRL_GET_INFO;
	dcmd->sgl.sge32[0].phys_addr = sc->ctlr_info_phys_addr;
	dcmd->sgl.sge32[0].length = sizeof(struct mrsas_ctrl_info);

	if (!sc->mask_interrupts)
		retcode = mrsas_issue_blocked_cmd(sc, cmd);
	else
		retcode = mrsas_issue_polled(sc, cmd);

	if (retcode == ETIMEDOUT)
		goto dcmd_timeout;
	else
		memcpy(sc->ctrl_info, sc->ctlr_info_mem, sizeof(struct mrsas_ctrl_info));

	do_ocr = 0;
	mrsas_update_ext_vd_details(sc);

	sc->use_seqnum_jbod_fp =
	    sc->ctrl_info->adapterOperations3.useSeqNumJbodFP;
	sc->support_morethan256jbod =
		sc->ctrl_info->adapterOperations4.supportPdMapTargetId;

	sc->disableOnlineCtrlReset =
	    sc->ctrl_info->properties.OnOffProperties.disableOnlineCtrlReset;

dcmd_timeout:
	mrsas_free_ctlr_info_cmd(sc);

	if (do_ocr)
		sc->do_timedout_reset = MFI_DCMD_TIMEOUT_OCR;

	if (!sc->mask_interrupts)
		mrsas_release_mfi_cmd(cmd);

	return (retcode);
}