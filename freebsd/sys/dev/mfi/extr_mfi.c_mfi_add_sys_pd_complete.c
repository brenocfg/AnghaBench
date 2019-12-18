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
struct mfi_softc {int /*<<< orphan*/  mfi_io_lock; int /*<<< orphan*/  mfi_dev; } ;
struct TYPE_5__ {int /*<<< orphan*/  device_id; } ;
struct TYPE_6__ {TYPE_2__ v; } ;
struct mfi_pd_info {scalar_t__ fw_state; TYPE_3__ ref; } ;
struct mfi_frame_header {scalar_t__ cmd_status; } ;
struct mfi_command {struct mfi_pd_info* cm_private; TYPE_1__* cm_frame; struct mfi_softc* cm_sc; } ;
typedef  int /*<<< orphan*/ * device_t ;
struct TYPE_4__ {struct mfi_frame_header header; } ;

/* Variables and functions */
 int /*<<< orphan*/  Giant ; 
 scalar_t__ MFI_PD_STATE_SYSTEM ; 
 scalar_t__ MFI_STAT_OK ; 
 int /*<<< orphan*/  M_MFIBUF ; 
 int /*<<< orphan*/  bus_generic_attach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * device_add_child (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  device_set_desc (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  device_set_ivars (int /*<<< orphan*/ *,struct mfi_pd_info*) ; 
 int /*<<< orphan*/  free (struct mfi_pd_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mfi_release_command (struct mfi_command*) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
mfi_add_sys_pd_complete(struct mfi_command *cm)
{
	struct mfi_frame_header *hdr;
	struct mfi_pd_info *pd_info;
	struct mfi_softc *sc;
	device_t child;

	sc = cm->cm_sc;
	hdr = &cm->cm_frame->header;
	pd_info = cm->cm_private;

	if (hdr->cmd_status != MFI_STAT_OK) {
		free(pd_info, M_MFIBUF);
		mfi_release_command(cm);
		return;
	}
	if (pd_info->fw_state != MFI_PD_STATE_SYSTEM) {
		device_printf(sc->mfi_dev, "PD=%x is not SYSTEM PD\n",
		    pd_info->ref.v.device_id);
		free(pd_info, M_MFIBUF);
		mfi_release_command(cm);
		return;
	}
	mfi_release_command(cm);

	mtx_unlock(&sc->mfi_io_lock);
	mtx_lock(&Giant);
	if ((child = device_add_child(sc->mfi_dev, "mfisyspd", -1)) == NULL) {
		device_printf(sc->mfi_dev, "Failed to add system pd\n");
		free(pd_info, M_MFIBUF);
		mtx_unlock(&Giant);
		mtx_lock(&sc->mfi_io_lock);
		return;
	}

	device_set_ivars(child, pd_info);
	device_set_desc(child, "MFI System PD");
	bus_generic_attach(sc->mfi_dev);
	mtx_unlock(&Giant);
	mtx_lock(&sc->mfi_io_lock);
}