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
struct mfi_system_pd {int pd_flags; int /*<<< orphan*/  pd_info; TYPE_1__* pd_controller; TYPE_2__* pd_disk; } ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_4__ {int d_flags; } ;
struct TYPE_3__ {int /*<<< orphan*/  mfi_io_lock; int /*<<< orphan*/  mfi_syspd_tqh; scalar_t__ mfi_detaching; scalar_t__ mfi_keep_deleted_volumes; } ;

/* Variables and functions */
 int DISKFLAG_OPEN ; 
 int EBUSY ; 
 int MFI_DISK_FLAGS_OPEN ; 
 int /*<<< orphan*/  M_MFIBUF ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,struct mfi_system_pd*,int /*<<< orphan*/ ) ; 
 struct mfi_system_pd* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  disk_destroy (TYPE_2__*) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pd_link ; 

__attribute__((used)) static int
mfi_syspd_detach(device_t dev)
{
	struct mfi_system_pd *sc;

	sc = device_get_softc(dev);
	device_printf(dev, "Detaching syspd\n");
	mtx_lock(&sc->pd_controller->mfi_io_lock);
	if (((sc->pd_disk->d_flags & DISKFLAG_OPEN) ||
	    (sc->pd_flags & MFI_DISK_FLAGS_OPEN)) &&
	    (sc->pd_controller->mfi_keep_deleted_volumes ||
	    sc->pd_controller->mfi_detaching)) {
		mtx_unlock(&sc->pd_controller->mfi_io_lock);
		device_printf(dev, "Cant detach syspd\n");
		return (EBUSY);
	}
	mtx_unlock(&sc->pd_controller->mfi_io_lock);

	disk_destroy(sc->pd_disk);
	mtx_lock(&sc->pd_controller->mfi_io_lock);
	TAILQ_REMOVE(&sc->pd_controller->mfi_syspd_tqh, sc, pd_link);
	mtx_unlock(&sc->pd_controller->mfi_io_lock);
	free(sc->pd_info, M_MFIBUF);
	return (0);
}