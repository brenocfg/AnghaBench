#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  vm_offset_t ;
struct mfi_softc {int dummy; } ;
struct mfi_disk {int /*<<< orphan*/  ld_id; struct mfi_softc* ld_controller; } ;
struct disk {struct mfi_disk* d_drv1; } ;
typedef  int off_t ;

/* Variables and functions */
 int MFI_SECTOR_LEN ; 
 int mfi_dump_blocks (struct mfi_softc*,int /*<<< orphan*/ ,int,void*,size_t) ; 

__attribute__((used)) static int
mfi_disk_dump(void *arg, void *virt, vm_offset_t phys, off_t offset, size_t len)
{
	struct mfi_disk *sc;
	struct mfi_softc *parent_sc;
	struct disk *dp;
	int error;

	dp = arg;
	sc = dp->d_drv1;
	parent_sc = sc->ld_controller;

	if (len > 0) {
		if ((error = mfi_dump_blocks(parent_sc, sc->ld_id, offset /
		    MFI_SECTOR_LEN, virt, len)) != 0)
			return (error);
	} else {
		/* mfi_sync_cache(parent_sc, sc->ld_id); */
	}

	return (0);
}