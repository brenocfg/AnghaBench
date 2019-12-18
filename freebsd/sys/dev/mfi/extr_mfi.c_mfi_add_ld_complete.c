#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct mfi_softc {int /*<<< orphan*/  mfi_io_lock; int /*<<< orphan*/  mfi_dev; int /*<<< orphan*/  mfi_map_sync_cm; scalar_t__ cm_map_abort; } ;
struct mfi_ld_info {int dummy; } ;
struct mfi_frame_header {scalar_t__ cmd_status; } ;
struct mfi_command {struct mfi_ld_info* cm_private; TYPE_1__* cm_frame; struct mfi_softc* cm_sc; } ;
typedef  int /*<<< orphan*/ * device_t ;
struct TYPE_2__ {struct mfi_frame_header header; } ;

/* Variables and functions */
 int /*<<< orphan*/  Giant ; 
 scalar_t__ MFI_STAT_OK ; 
 int /*<<< orphan*/  M_MFIBUF ; 
 int /*<<< orphan*/  bus_generic_attach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * device_add_child (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  device_set_desc (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  device_set_ivars (int /*<<< orphan*/ *,struct mfi_ld_info*) ; 
 int /*<<< orphan*/  free (struct mfi_ld_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mfi_release_command (struct mfi_command*) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wakeup (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
mfi_add_ld_complete(struct mfi_command *cm)
{
	struct mfi_frame_header *hdr;
	struct mfi_ld_info *ld_info;
	struct mfi_softc *sc;
	device_t child;

	sc = cm->cm_sc;
	hdr = &cm->cm_frame->header;
	ld_info = cm->cm_private;

	if (sc->cm_map_abort || hdr->cmd_status != MFI_STAT_OK) {
		free(ld_info, M_MFIBUF);
		wakeup(&sc->mfi_map_sync_cm);
		mfi_release_command(cm);
		return;
	}
	wakeup(&sc->mfi_map_sync_cm);
	mfi_release_command(cm);

	mtx_unlock(&sc->mfi_io_lock);
	mtx_lock(&Giant);
	if ((child = device_add_child(sc->mfi_dev, "mfid", -1)) == NULL) {
		device_printf(sc->mfi_dev, "Failed to add logical disk\n");
		free(ld_info, M_MFIBUF);
		mtx_unlock(&Giant);
		mtx_lock(&sc->mfi_io_lock);
		return;
	}

	device_set_ivars(child, ld_info);
	device_set_desc(child, "MFI Logical Disk");
	bus_generic_attach(sc->mfi_dev);
	mtx_unlock(&Giant);
	mtx_lock(&sc->mfi_io_lock);
}