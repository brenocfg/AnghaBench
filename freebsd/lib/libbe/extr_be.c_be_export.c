#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zfs_handle_t ;
struct TYPE_8__ {int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ sendflags_t ;
struct TYPE_9__ {int /*<<< orphan*/  lzh; } ;
typedef  TYPE_2__ libbe_handle_t ;

/* Variables and functions */
 int /*<<< orphan*/  BE_ERR_ZFSOPEN ; 
 int BE_MAXPATHLEN ; 
 int /*<<< orphan*/  ZFS_TYPE_DATASET ; 
 int /*<<< orphan*/  be_root_concat (TYPE_2__*,char*,char*) ; 
 int be_snapshot (TYPE_2__*,char const*,int /*<<< orphan*/ *,int,char*) ; 
 int set_error (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfs_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * zfs_open (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int zfs_send_one (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,TYPE_1__) ; 

int
be_export(libbe_handle_t *lbh, const char *bootenv, int fd)
{
	char snap_name[BE_MAXPATHLEN];
	char buf[BE_MAXPATHLEN];
	zfs_handle_t *zfs;
	sendflags_t flags = { 0 };
	int err;

	if ((err = be_snapshot(lbh, bootenv, NULL, true, snap_name)) != 0)
		/* Use the error set by be_snapshot */
		return (err);

	be_root_concat(lbh, snap_name, buf);

	if ((zfs = zfs_open(lbh->lzh, buf, ZFS_TYPE_DATASET)) == NULL)
		return (set_error(lbh, BE_ERR_ZFSOPEN));

	err = zfs_send_one(zfs, NULL, fd, flags);
	zfs_close(zfs);

	return (err);
}