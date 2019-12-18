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
struct mfi_softc {int /*<<< orphan*/  mfi_dev; int /*<<< orphan*/  mfi_ld_pend_tqh; int /*<<< orphan*/  mfi_io_lock; } ;
struct TYPE_5__ {int isSSCD; } ;
struct TYPE_6__ {TYPE_2__ params; } ;
struct mfi_ld_info {TYPE_3__ ld_config; } ;
struct mfi_disk_pending {int ld_id; } ;
struct mfi_dcmd_frame {int* mbox; } ;
struct mfi_command {TYPE_1__* cm_frame; int /*<<< orphan*/  cm_flags; } ;
struct TYPE_4__ {struct mfi_dcmd_frame dcmd; } ;

/* Variables and functions */
 int /*<<< orphan*/  MA_OWNED ; 
 int /*<<< orphan*/  MFI_CMD_DATAIN ; 
 int /*<<< orphan*/  MFI_DCMD_LD_GET_INFO ; 
 int /*<<< orphan*/  M_MFIBUF ; 
 int M_NOWAIT ; 
 int M_ZERO ; 
 int /*<<< orphan*/  TAILQ_INSERT_TAIL (int /*<<< orphan*/ *,struct mfi_disk_pending*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  free (struct mfi_ld_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ld_link ; 
 struct mfi_disk_pending* malloc (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mfi_add_ld_complete (struct mfi_command*) ; 
 int mfi_dcmd_command (struct mfi_softc*,struct mfi_command**,int /*<<< orphan*/ ,void**,int) ; 
 int /*<<< orphan*/  mfi_release_command (struct mfi_command*) ; 
 scalar_t__ mfi_wait_command (struct mfi_softc*,struct mfi_command*) ; 
 int /*<<< orphan*/  mtx_assert (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
mfi_add_ld(struct mfi_softc *sc, int id)
{
	struct mfi_command *cm;
	struct mfi_dcmd_frame *dcmd = NULL;
	struct mfi_ld_info *ld_info = NULL;
	struct mfi_disk_pending *ld_pend;
	int error;

	mtx_assert(&sc->mfi_io_lock, MA_OWNED);

	ld_pend = malloc(sizeof(*ld_pend), M_MFIBUF, M_NOWAIT | M_ZERO);
	if (ld_pend != NULL) {
		ld_pend->ld_id = id;
		TAILQ_INSERT_TAIL(&sc->mfi_ld_pend_tqh, ld_pend, ld_link);
	}

	error = mfi_dcmd_command(sc, &cm, MFI_DCMD_LD_GET_INFO,
	    (void **)&ld_info, sizeof(*ld_info));
	if (error) {
		device_printf(sc->mfi_dev,
		    "Failed to allocate for MFI_DCMD_LD_GET_INFO %d\n", error);
		if (ld_info)
			free(ld_info, M_MFIBUF);
		return (error);
	}
	cm->cm_flags = MFI_CMD_DATAIN;
	dcmd = &cm->cm_frame->dcmd;
	dcmd->mbox[0] = id;
	if (mfi_wait_command(sc, cm) != 0) {
		device_printf(sc->mfi_dev,
		    "Failed to get logical drive: %d\n", id);
		free(ld_info, M_MFIBUF);
		return (0);
	}
	if (ld_info->ld_config.params.isSSCD != 1)
		mfi_add_ld_complete(cm);
	else {
		mfi_release_command(cm);
		if (ld_info)		/* SSCD drives ld_info free here */
			free(ld_info, M_MFIBUF);
	}
	return (0);
}