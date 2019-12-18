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
struct mfi_system_pending {int pd_id; } ;
struct mfi_softc {int /*<<< orphan*/  mfi_buffer_dmat; int /*<<< orphan*/  mfi_dev; int /*<<< orphan*/  mfi_syspd_pend_tqh; int /*<<< orphan*/  mfi_io_lock; } ;
struct mfi_pd_info {int dummy; } ;
struct TYPE_4__ {scalar_t__ pad0; scalar_t__ scsi_status; } ;
struct mfi_dcmd_frame {int* mbox; TYPE_2__ header; } ;
struct mfi_command {int cm_flags; int /*<<< orphan*/  cm_dmamap; TYPE_1__* cm_frame; } ;
struct TYPE_3__ {struct mfi_dcmd_frame dcmd; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_DMASYNC_POSTREAD ; 
 int /*<<< orphan*/  MA_OWNED ; 
 int MFI_CMD_DATAIN ; 
 int MFI_CMD_POLLED ; 
 int /*<<< orphan*/  MFI_DCMD_PD_GET_INFO ; 
 int /*<<< orphan*/  M_MFIBUF ; 
 int M_NOWAIT ; 
 int M_ZERO ; 
 int /*<<< orphan*/  TAILQ_INSERT_TAIL (int /*<<< orphan*/ *,struct mfi_system_pending*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_dmamap_sync (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_dmamap_unload (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  free (struct mfi_pd_info*,int /*<<< orphan*/ ) ; 
 struct mfi_system_pending* malloc (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mfi_add_sys_pd_complete (struct mfi_command*) ; 
 int mfi_dcmd_command (struct mfi_softc*,struct mfi_command**,int /*<<< orphan*/ ,void**,int) ; 
 int mfi_mapcmd (struct mfi_softc*,struct mfi_command*) ; 
 int /*<<< orphan*/  mfi_release_command (struct mfi_command*) ; 
 int /*<<< orphan*/  mtx_assert (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pd_link ; 

__attribute__((used)) static int mfi_add_sys_pd(struct mfi_softc *sc, int id)
{
	struct mfi_command *cm;
	struct mfi_dcmd_frame *dcmd = NULL;
	struct mfi_pd_info *pd_info = NULL;
	struct mfi_system_pending *syspd_pend;
	int error;

	mtx_assert(&sc->mfi_io_lock, MA_OWNED);

	syspd_pend = malloc(sizeof(*syspd_pend), M_MFIBUF, M_NOWAIT | M_ZERO);
	if (syspd_pend != NULL) {
		syspd_pend->pd_id = id;
		TAILQ_INSERT_TAIL(&sc->mfi_syspd_pend_tqh, syspd_pend, pd_link);
	}

	error = mfi_dcmd_command(sc, &cm, MFI_DCMD_PD_GET_INFO,
		(void **)&pd_info, sizeof(*pd_info));
	if (error) {
		device_printf(sc->mfi_dev,
		    "Failed to allocated for MFI_DCMD_PD_GET_INFO %d\n",
		    error);
		if (pd_info)
			free(pd_info, M_MFIBUF);
		return (error);
	}
	cm->cm_flags = MFI_CMD_DATAIN | MFI_CMD_POLLED;
	dcmd = &cm->cm_frame->dcmd;
	dcmd->mbox[0]=id;
	dcmd->header.scsi_status = 0;
	dcmd->header.pad0 = 0;
	if ((error = mfi_mapcmd(sc, cm)) != 0) {
		device_printf(sc->mfi_dev,
		    "Failed to get physical drive info %d\n", id);
		free(pd_info, M_MFIBUF);
		mfi_release_command(cm);
		return (error);
	}
	bus_dmamap_sync(sc->mfi_buffer_dmat, cm->cm_dmamap,
	    BUS_DMASYNC_POSTREAD);
	bus_dmamap_unload(sc->mfi_buffer_dmat, cm->cm_dmamap);
	mfi_add_sys_pd_complete(cm);
	return (0);
}