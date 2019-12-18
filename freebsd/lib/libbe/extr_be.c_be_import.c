#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zfs_handle_t ;
struct TYPE_7__ {int nomount; } ;
typedef  TYPE_1__ recvflags_t ;
typedef  int /*<<< orphan*/  nvlist_t ;
struct TYPE_8__ {int /*<<< orphan*/  lzh; } ;
typedef  TYPE_2__ libbe_handle_t ;

/* Variables and functions */
 int /*<<< orphan*/  BE_ERR_IO ; 
 int /*<<< orphan*/  BE_ERR_NOENT ; 
 int /*<<< orphan*/  BE_ERR_NOORIGIN ; 
 int /*<<< orphan*/  BE_ERR_UNKNOWN ; 
 int /*<<< orphan*/  BE_ERR_ZFSOPEN ; 
 int BE_MAXPATHLEN ; 
#define  EINVAL 130 
#define  EIO 129 
#define  ENOENT 128 
 int /*<<< orphan*/  KM_SLEEP ; 
 int /*<<< orphan*/  NV_UNIQUE_NAME ; 
 int /*<<< orphan*/  ZFS_TYPE_FILESYSTEM ; 
 int /*<<< orphan*/  be_root_concat (TYPE_2__*,char const*,char*) ; 
 int /*<<< orphan*/  nvlist_add_string (int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/  nvlist_alloc (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvlist_free (int /*<<< orphan*/ *) ; 
 int set_error (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfs_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * zfs_open (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int zfs_prop_set_list (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int zfs_receive (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,TYPE_1__*,int,int /*<<< orphan*/ *) ; 

int
be_import(libbe_handle_t *lbh, const char *bootenv, int fd)
{
	char buf[BE_MAXPATHLEN];
	nvlist_t *props;
	zfs_handle_t *zfs;
	recvflags_t flags = { .nomount = 1 };
	int err;

	be_root_concat(lbh, bootenv, buf);

	if ((err = zfs_receive(lbh->lzh, buf, NULL, &flags, fd, NULL)) != 0) {
		switch (err) {
		case EINVAL:
			return (set_error(lbh, BE_ERR_NOORIGIN));
		case ENOENT:
			return (set_error(lbh, BE_ERR_NOENT));
		case EIO:
			return (set_error(lbh, BE_ERR_IO));
		default:
			return (set_error(lbh, BE_ERR_UNKNOWN));
		}
	}

	if ((zfs = zfs_open(lbh->lzh, buf, ZFS_TYPE_FILESYSTEM)) == NULL)
		return (set_error(lbh, BE_ERR_ZFSOPEN));

	nvlist_alloc(&props, NV_UNIQUE_NAME, KM_SLEEP);
	nvlist_add_string(props, "canmount", "noauto");
	nvlist_add_string(props, "mountpoint", "none");

	err = zfs_prop_set_list(zfs, props);
	nvlist_free(props);

	zfs_close(zfs);

	if (err != 0)
		return (set_error(lbh, BE_ERR_UNKNOWN));

	return (0);
}