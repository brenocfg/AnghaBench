#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zfs_handle_t ;
struct TYPE_3__ {int /*<<< orphan*/  lzh; } ;
typedef  TYPE_1__ libbe_handle_t ;

/* Variables and functions */
 int /*<<< orphan*/  ZFS_TYPE_DATASET ; 
 int /*<<< orphan*/  zfs_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * zfs_open (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 
 scalar_t__ zfs_prop_set (int /*<<< orphan*/ *,char*,char*) ; 

__attribute__((used)) static int
be_deactivate(libbe_handle_t *lbh, const char *ds)
{
	zfs_handle_t *zfs;

	if ((zfs = zfs_open(lbh->lzh, ds, ZFS_TYPE_DATASET)) == NULL)
		return (1);
	if (zfs_prop_set(zfs, "canmount", "noauto") != 0)
		return (1);
	zfs_close(zfs);
	return (0);
}