#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
struct mfi_frame_header {scalar_t__ sg_count; } ;
struct mfi_command {int cm_flags; int cm_extra_frames; scalar_t__ retry_for_fw_reset; scalar_t__ cm_total_frame_size; TYPE_3__* cm_sg; int /*<<< orphan*/ * cm_data; int /*<<< orphan*/ * cm_private; int /*<<< orphan*/ * cm_complete; TYPE_2__* cm_frame; TYPE_4__* cm_sc; } ;
struct TYPE_8__ {int /*<<< orphan*/ * mfi_cmd_pool_tbolt; int /*<<< orphan*/  mfi_io_lock; } ;
struct TYPE_7__ {TYPE_1__* sg32; } ;
struct TYPE_6__ {struct mfi_frame_header header; } ;
struct TYPE_5__ {scalar_t__ addr; scalar_t__ len; } ;

/* Variables and functions */
 int /*<<< orphan*/  MA_OWNED ; 
 int MFI_CMD_TBOLT ; 
 int MFI_ON_MFIQ_BUSY ; 
 int MFI_ON_MFIQ_MASK ; 
 int MFI_ON_MFIQ_READY ; 
 int /*<<< orphan*/  mfi_enqueue_free (struct mfi_command*) ; 
 int /*<<< orphan*/  mfi_remove_busy (struct mfi_command*) ; 
 int /*<<< orphan*/  mfi_remove_ready (struct mfi_command*) ; 
 int /*<<< orphan*/  mfi_tbolt_return_cmd (TYPE_4__*,int /*<<< orphan*/ ,struct mfi_command*) ; 
 int /*<<< orphan*/  mtx_assert (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  panic (char*,struct mfi_command*,int) ; 

void
mfi_release_command(struct mfi_command *cm)
{
	struct mfi_frame_header *hdr;
	uint32_t *hdr_data;

	mtx_assert(&cm->cm_sc->mfi_io_lock, MA_OWNED);

	/*
	 * Zero out the important fields of the frame, but make sure the
	 * context field is preserved.  For efficiency, handle the fields
	 * as 32 bit words.  Clear out the first S/G entry too for safety.
	 */
	hdr = &cm->cm_frame->header;
	if (cm->cm_data != NULL && hdr->sg_count) {
		cm->cm_sg->sg32[0].len = 0;
		cm->cm_sg->sg32[0].addr = 0;
	}

	/*
	 * Command may be on other queues e.g. busy queue depending on the
	 * flow of a previous call to mfi_mapcmd, so ensure its dequeued
	 * properly
	 */
	if ((cm->cm_flags & MFI_ON_MFIQ_BUSY) != 0)
		mfi_remove_busy(cm);
	if ((cm->cm_flags & MFI_ON_MFIQ_READY) != 0)
		mfi_remove_ready(cm);

	/* We're not expecting it to be on any other queue but check */
	if ((cm->cm_flags & MFI_ON_MFIQ_MASK) != 0) {
		panic("Command %p is still on another queue, flags = %#x",
		    cm, cm->cm_flags);
	}

	/* tbolt cleanup */
	if ((cm->cm_flags & MFI_CMD_TBOLT) != 0) {
		mfi_tbolt_return_cmd(cm->cm_sc,
		    cm->cm_sc->mfi_cmd_pool_tbolt[cm->cm_extra_frames - 1],
		    cm);
	}

	hdr_data = (uint32_t *)cm->cm_frame;
	hdr_data[0] = 0;	/* cmd, sense_len, cmd_status, scsi_status */
	hdr_data[1] = 0;	/* target_id, lun_id, cdb_len, sg_count */
	hdr_data[4] = 0;	/* flags, timeout */
	hdr_data[5] = 0;	/* data_len */

	cm->cm_extra_frames = 0;
	cm->cm_flags = 0;
	cm->cm_complete = NULL;
	cm->cm_private = NULL;
	cm->cm_data = NULL;
	cm->cm_sg = 0;
	cm->cm_total_frame_size = 0;
	cm->retry_for_fw_reset = 0;

	mfi_enqueue_free(cm);
}