#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  union mfi_frame {int dummy; } mfi_frame ;
typedef  int uint64_t ;
typedef  void* uint32_t ;
struct mfi_softc {int /*<<< orphan*/  mfi_io_lock; int /*<<< orphan*/  mfi_dev; } ;
struct mfi_command {int /*<<< orphan*/  (* cm_complete ) (struct mfi_command*) ;int /*<<< orphan*/  cm_flags; int /*<<< orphan*/ * cm_data; scalar_t__ cm_frame_busaddr; TYPE_3__* cm_frame; } ;
struct TYPE_4__ {scalar_t__ scsi_status; scalar_t__ flags; int /*<<< orphan*/  cmd; } ;
struct mfi_abort_frame {void* abort_mfi_addr_hi; void* abort_mfi_addr_lo; void* abort_context; TYPE_1__ header; } ;
struct TYPE_5__ {void* context; } ;
struct TYPE_6__ {TYPE_2__ header; struct mfi_abort_frame abort; } ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  MFI_CMD_ABORT ; 
 int /*<<< orphan*/  MFI_CMD_POLLED ; 
 int /*<<< orphan*/  bzero (TYPE_3__*,int) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int hz ; 
 struct mfi_command* mfi_dequeue_free (struct mfi_softc*) ; 
 int mfi_mapcmd (struct mfi_softc*,struct mfi_command*) ; 
 int /*<<< orphan*/  mfi_release_command (struct mfi_command*) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct mfi_command*) ; 
 int /*<<< orphan*/  tsleep (struct mfi_command**,int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static int
mfi_abort(struct mfi_softc *sc, struct mfi_command **cm_abort)
{
	struct mfi_command *cm;
	struct mfi_abort_frame *abort;
	int i = 0, error;
	uint32_t context = 0;

	mtx_lock(&sc->mfi_io_lock);
	if ((cm = mfi_dequeue_free(sc)) == NULL) {
		mtx_unlock(&sc->mfi_io_lock);
		return (EBUSY);
	}

	/* Zero out the MFI frame */
	context = cm->cm_frame->header.context;
	bzero(cm->cm_frame, sizeof(union mfi_frame));
	cm->cm_frame->header.context = context;

	abort = &cm->cm_frame->abort;
	abort->header.cmd = MFI_CMD_ABORT;
	abort->header.flags = 0;
	abort->header.scsi_status = 0;
	abort->abort_context = (*cm_abort)->cm_frame->header.context;
	abort->abort_mfi_addr_lo = (uint32_t)(*cm_abort)->cm_frame_busaddr;
	abort->abort_mfi_addr_hi =
		(uint32_t)((uint64_t)(*cm_abort)->cm_frame_busaddr >> 32);
	cm->cm_data = NULL;
	cm->cm_flags = MFI_CMD_POLLED;

	if ((error = mfi_mapcmd(sc, cm)) != 0)
		device_printf(sc->mfi_dev, "failed to abort command\n");
	mfi_release_command(cm);

	mtx_unlock(&sc->mfi_io_lock);
	while (i < 5 && *cm_abort != NULL) {
		tsleep(cm_abort, 0, "mfiabort",
		    5 * hz);
		i++;
	}
	if (*cm_abort != NULL) {
		/* Force a complete if command didn't abort */
		mtx_lock(&sc->mfi_io_lock);
		(*cm_abort)->cm_complete(*cm_abort);
		mtx_unlock(&sc->mfi_io_lock);
	}

	return (error);
}