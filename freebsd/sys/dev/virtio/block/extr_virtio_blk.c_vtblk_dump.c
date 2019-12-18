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
struct vtblk_softc {int dummy; } ;
struct disk {struct vtblk_softc* d_drv1; } ;
typedef  scalar_t__ off_t ;

/* Variables and functions */
 int ENXIO ; 
 int /*<<< orphan*/  VTBLK_LOCK (struct vtblk_softc*) ; 
 int /*<<< orphan*/  VTBLK_UNLOCK (struct vtblk_softc*) ; 
 int /*<<< orphan*/  vtblk_dump_complete (struct vtblk_softc*) ; 
 int /*<<< orphan*/  vtblk_dump_quiesce (struct vtblk_softc*) ; 
 int vtblk_dump_write (struct vtblk_softc*,void*,scalar_t__,size_t) ; 

__attribute__((used)) static int
vtblk_dump(void *arg, void *virtual, vm_offset_t physical, off_t offset,
    size_t length)
{
	struct disk *dp;
	struct vtblk_softc *sc;
	int error;

	dp = arg;
	error = 0;

	if ((sc = dp->d_drv1) == NULL)
		return (ENXIO);

	VTBLK_LOCK(sc);

	vtblk_dump_quiesce(sc);

	if (length > 0)
		error = vtblk_dump_write(sc, virtual, offset, length);
	if (error || (virtual == NULL && offset == 0))
		vtblk_dump_complete(sc);

	VTBLK_UNLOCK(sc);

	return (error);
}