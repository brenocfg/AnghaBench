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
typedef  int /*<<< orphan*/  uint32_t ;
struct mfi_softc {int /*<<< orphan*/  mfi_io_lock; int /*<<< orphan*/  mfi_dev; } ;
struct mfi_dcmd_frame {int /*<<< orphan*/  sgl; int /*<<< orphan*/  opcode; } ;
struct mfi_ioc_passthru {int buf_size; int /*<<< orphan*/  buf; struct mfi_dcmd_frame ioc_frame; } ;
struct mfi_command {int cm_len; int cm_flags; TYPE_2__* cm_frame; void* cm_data; int /*<<< orphan*/  cm_total_frame_size; int /*<<< orphan*/ * cm_sg; } ;
struct TYPE_3__ {int /*<<< orphan*/  context; } ;
struct TYPE_4__ {TYPE_1__ header; struct mfi_dcmd_frame dcmd; } ;

/* Variables and functions */
 int ENOMEM ; 
 int MFI_CMD_DATAIN ; 
 int MFI_CMD_DATAOUT ; 
 int /*<<< orphan*/  MFI_DCMD_FRAME_SIZE ; 
 int /*<<< orphan*/  M_MFIBUF ; 
 int /*<<< orphan*/  M_WAITOK ; 
 int /*<<< orphan*/  bcopy (struct mfi_dcmd_frame*,struct mfi_dcmd_frame*,int) ; 
 int copyin (int /*<<< orphan*/ ,void*,int) ; 
 int copyout (void*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  free (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hz ; 
 void* malloc (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mfi_check_command_post (struct mfi_softc*,struct mfi_command*) ; 
 int mfi_check_command_pre (struct mfi_softc*,struct mfi_command*) ; 
 int mfi_config_lock (struct mfi_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mfi_config_unlock (struct mfi_softc*,int) ; 
 struct mfi_command* mfi_dequeue_free (struct mfi_softc*) ; 
 int /*<<< orphan*/  mfi_release_command (struct mfi_command*) ; 
 int mfi_wait_command (struct mfi_softc*,struct mfi_command*) ; 
 int /*<<< orphan*/  msleep (int (*) (struct mfi_softc*,struct mfi_ioc_passthru*),int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
mfi_user_command(struct mfi_softc *sc, struct mfi_ioc_passthru *ioc)
{
	struct mfi_command *cm;
	struct mfi_dcmd_frame *dcmd;
	void *ioc_buf = NULL;
	uint32_t context;
	int error = 0, locked;


	if (ioc->buf_size > 0) {
		if (ioc->buf_size > 1024 * 1024)
			return (ENOMEM);
		ioc_buf = malloc(ioc->buf_size, M_MFIBUF, M_WAITOK);
		error = copyin(ioc->buf, ioc_buf, ioc->buf_size);
		if (error) {
			device_printf(sc->mfi_dev, "failed to copyin\n");
			free(ioc_buf, M_MFIBUF);
			return (error);
		}
	}

	locked = mfi_config_lock(sc, ioc->ioc_frame.opcode);

	mtx_lock(&sc->mfi_io_lock);
	while ((cm = mfi_dequeue_free(sc)) == NULL)
		msleep(mfi_user_command, &sc->mfi_io_lock, 0, "mfiioc", hz);

	/* Save context for later */
	context = cm->cm_frame->header.context;

	dcmd = &cm->cm_frame->dcmd;
	bcopy(&ioc->ioc_frame, dcmd, sizeof(struct mfi_dcmd_frame));

	cm->cm_sg = &dcmd->sgl;
	cm->cm_total_frame_size = MFI_DCMD_FRAME_SIZE;
	cm->cm_data = ioc_buf;
	cm->cm_len = ioc->buf_size;

	/* restore context */
	cm->cm_frame->header.context = context;

	/* Cheat since we don't know if we're writing or reading */
	cm->cm_flags = MFI_CMD_DATAIN | MFI_CMD_DATAOUT;

	error = mfi_check_command_pre(sc, cm);
	if (error)
		goto out;

	error = mfi_wait_command(sc, cm);
	if (error) {
		device_printf(sc->mfi_dev, "ioctl failed %d\n", error);
		goto out;
	}
	bcopy(dcmd, &ioc->ioc_frame, sizeof(struct mfi_dcmd_frame));
	mfi_check_command_post(sc, cm);
out:
	mfi_release_command(cm);
	mtx_unlock(&sc->mfi_io_lock);
	mfi_config_unlock(sc, locked);
	if (ioc->buf_size > 0)
		error = copyout(ioc_buf, ioc->buf, ioc->buf_size);
	if (ioc_buf)
		free(ioc_buf, M_MFIBUF);
	return (error);
}