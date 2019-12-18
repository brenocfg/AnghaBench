#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zdev ;
struct devdesc {scalar_t__ d_unit; TYPE_1__* d_dev; } ;
struct zfs_devdesc {struct devdesc dd; } ;
struct disk_devdesc {struct devdesc dd; int /*<<< orphan*/  d_partition; int /*<<< orphan*/  d_slice; } ;
struct TYPE_4__ {scalar_t__ (* dv_open ) (int /*<<< orphan*/ *,struct disk_devdesc*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  D_PARTNONE ; 
 int /*<<< orphan*/  D_PARTWILD ; 
 int /*<<< orphan*/  D_SLICENONE ; 
 int /*<<< orphan*/  D_SLICEWILD ; 
 int /*<<< orphan*/  EV_VOLATILE ; 
 int /*<<< orphan*/  bzero (struct zfs_devdesc*,int) ; 
 int /*<<< orphan*/  env_noset ; 
 int /*<<< orphan*/  env_nounset ; 
 int /*<<< orphan*/  env_setenv (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__ host_dev ; 
 int /*<<< orphan*/  init_zfs_bootenv (int /*<<< orphan*/ ) ; 
 scalar_t__ stub1 (int /*<<< orphan*/ *,struct disk_devdesc*) ; 
 TYPE_1__ userboot_disk ; 
 scalar_t__ userboot_disk_maxunit ; 
 int /*<<< orphan*/  userboot_fmtdev (struct devdesc*) ; 
 int /*<<< orphan*/  userboot_setcurrdev ; 
 scalar_t__ userboot_zfs_found ; 
 TYPE_1__ zfs_dev ; 
 int /*<<< orphan*/  zfs_fmtdev (struct zfs_devdesc*) ; 

__attribute__((used)) static void
extract_currdev(void)
{
	struct disk_devdesc dev;
	struct devdesc *dd;
#if defined(USERBOOT_ZFS_SUPPORT)
	struct zfs_devdesc zdev;

	if (userboot_zfs_found) {
	
		/* Leave the pool/root guid's unassigned */
		bzero(&zdev, sizeof(zdev));
		zdev.dd.d_dev = &zfs_dev;
		
		init_zfs_bootenv(zfs_fmtdev(&zdev));
		dd = &zdev.dd;
	} else
#endif

	if (userboot_disk_maxunit > 0) {
		dev.dd.d_dev = &userboot_disk;
		dev.dd.d_unit = 0;
		dev.d_slice = D_SLICEWILD;
		dev.d_partition = D_PARTWILD;
		/*
		 * If we cannot auto-detect the partition type then
		 * access the disk as a raw device.
		 */
		if (dev.dd.d_dev->dv_open(NULL, &dev)) {
			dev.d_slice = D_SLICENONE;
			dev.d_partition = D_PARTNONE;
		}
		dd = &dev.dd;
	} else {
		dev.dd.d_dev = &host_dev;
		dev.dd.d_unit = 0;
		dd = &dev.dd;
	}

	env_setenv("currdev", EV_VOLATILE, userboot_fmtdev(dd),
	    userboot_setcurrdev, env_nounset);
	env_setenv("loaddev", EV_VOLATILE, userboot_fmtdev(dd),
	    env_noset, env_nounset);
}