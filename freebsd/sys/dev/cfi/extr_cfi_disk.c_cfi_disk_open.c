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
struct disk {struct cfi_disk_softc* d_drv1; } ;
struct cfi_disk_softc {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  CFI_DISK_OPEN ; 

__attribute__((used)) static int
cfi_disk_open(struct disk *dp)
{
	struct cfi_disk_softc *sc = dp->d_drv1;

	/* XXX no interlock with /dev/cfi */
	sc->flags |= CFI_DISK_OPEN;
	return 0;
}