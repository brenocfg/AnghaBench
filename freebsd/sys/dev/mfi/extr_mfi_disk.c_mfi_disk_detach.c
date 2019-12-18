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
struct mfi_disk {int ld_flags; int /*<<< orphan*/  ld_info; TYPE_1__* ld_controller; TYPE_2__* ld_disk; } ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_4__ {int d_flags; } ;
struct TYPE_3__ {int /*<<< orphan*/  mfi_io_lock; int /*<<< orphan*/  mfi_ld_tqh; scalar_t__ mfi_detaching; scalar_t__ mfi_keep_deleted_volumes; } ;

/* Variables and functions */
 int DISKFLAG_OPEN ; 
 int EBUSY ; 
 int MFI_DISK_FLAGS_OPEN ; 
 int /*<<< orphan*/  M_MFIBUF ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,struct mfi_disk*,int /*<<< orphan*/ ) ; 
 struct mfi_disk* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  disk_destroy (TYPE_2__*) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ld_link ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
mfi_disk_detach(device_t dev)
{
	struct mfi_disk *sc;

	sc = device_get_softc(dev);

	mtx_lock(&sc->ld_controller->mfi_io_lock);
	if (((sc->ld_disk->d_flags & DISKFLAG_OPEN) ||
	    (sc->ld_flags & MFI_DISK_FLAGS_OPEN)) &&
	    (sc->ld_controller->mfi_keep_deleted_volumes ||
	    sc->ld_controller->mfi_detaching)) {
		mtx_unlock(&sc->ld_controller->mfi_io_lock);
		return (EBUSY);
	}
	mtx_unlock(&sc->ld_controller->mfi_io_lock);

	disk_destroy(sc->ld_disk);
	mtx_lock(&sc->ld_controller->mfi_io_lock);
	TAILQ_REMOVE(&sc->ld_controller->mfi_ld_tqh, sc, ld_link);
	mtx_unlock(&sc->ld_controller->mfi_io_lock);
	free(sc->ld_info, M_MFIBUF);
	return (0);
}