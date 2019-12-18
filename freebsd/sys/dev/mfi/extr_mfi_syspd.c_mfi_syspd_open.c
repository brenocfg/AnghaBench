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
struct mfi_system_pd {int pd_flags; TYPE_1__* pd_controller; } ;
struct disk {struct mfi_system_pd* d_drv1; } ;
struct TYPE_2__ {int /*<<< orphan*/  mfi_io_lock; } ;

/* Variables and functions */
 int ENXIO ; 
 int MFI_DISK_FLAGS_DISABLED ; 
 int MFI_DISK_FLAGS_OPEN ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
mfi_syspd_open(struct disk *dp)
{
	struct mfi_system_pd *sc;
	int error;

	sc = dp->d_drv1;
	mtx_lock(&sc->pd_controller->mfi_io_lock);
	if (sc->pd_flags & MFI_DISK_FLAGS_DISABLED)
		error = ENXIO;
	else {
		sc->pd_flags |= MFI_DISK_FLAGS_OPEN;
		error = 0;
	}
	mtx_unlock(&sc->pd_controller->mfi_io_lock);
	return (error);
}