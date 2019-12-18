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
typedef  int /*<<< orphan*/  driver_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_ADD_CHILD (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,unsigned int) ; 
 int /*<<< orphan*/  MTX_DEF ; 
 int /*<<< orphan*/  gxemul_disk_controller_mutex ; 
 scalar_t__ gxemul_disk_read (unsigned int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
gxemul_disk_identify(driver_t *drv, device_t parent)
{
	unsigned diskid;

	mtx_init(&gxemul_disk_controller_mutex, "GXemul disk controller", NULL, MTX_DEF);

	mtx_lock(&gxemul_disk_controller_mutex);
	for (diskid = 0; diskid < 0x100; diskid++) {
		/*
		 * If we can read at offset 0, this disk id must be
		 * present enough.  If we get an error, stop looking.
		 * Disks in GXemul are allocated linearly from 0.
		 */
		if (gxemul_disk_read(diskid, NULL, 0) != 0)
			break;
		BUS_ADD_CHILD(parent, 0, "gxemul_disk", diskid);
	}
	mtx_unlock(&gxemul_disk_controller_mutex);
}