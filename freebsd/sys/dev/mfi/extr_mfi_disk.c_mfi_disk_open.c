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
struct mfi_disk {int ld_flags; TYPE_1__* ld_controller; } ;
struct disk {struct mfi_disk* d_drv1; } ;
struct TYPE_2__ {int /*<<< orphan*/  mfi_io_lock; } ;

/* Variables and functions */
 int ENXIO ; 
 int MFI_DISK_FLAGS_DISABLED ; 
 int MFI_DISK_FLAGS_OPEN ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
mfi_disk_open(struct disk *dp)
{
	struct mfi_disk *sc;
	int error;

	sc = dp->d_drv1;
	mtx_lock(&sc->ld_controller->mfi_io_lock);
	if (sc->ld_flags & MFI_DISK_FLAGS_DISABLED)
		error = ENXIO;
	else {
		sc->ld_flags |= MFI_DISK_FLAGS_OPEN;
		error = 0;
	}
	mtx_unlock(&sc->ld_controller->mfi_io_lock);

	return (error);
}