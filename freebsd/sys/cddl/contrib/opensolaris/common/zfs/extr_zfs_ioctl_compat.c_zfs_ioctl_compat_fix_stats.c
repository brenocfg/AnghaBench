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
struct TYPE_4__ {int /*<<< orphan*/  zc_iflags; int /*<<< orphan*/  zc_nvlist_dst_size; int /*<<< orphan*/  zc_nvlist_dst; } ;
typedef  TYPE_1__ zfs_cmd_t ;
typedef  int /*<<< orphan*/  nvpair_t ;
typedef  int /*<<< orphan*/  nvlist_t ;

/* Variables and functions */
 int /*<<< orphan*/  nvlist_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * nvlist_next_nvpair (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ nvpair_value_nvlist (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  zfs_ioctl_compat_fix_stats_nvlist (int /*<<< orphan*/ *) ; 
 int zfs_ioctl_compat_get_nvlist (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int zfs_ioctl_compat_put_nvlist (TYPE_1__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
zfs_ioctl_compat_fix_stats(zfs_cmd_t *zc, const int nc)
{
	nvlist_t *nv, *nvp = NULL;
	nvpair_t *elem;
	int error;

	if ((error = zfs_ioctl_compat_get_nvlist(zc->zc_nvlist_dst,
	    zc->zc_nvlist_dst_size, zc->zc_iflags, &nv)) != 0)
		return (error);

	if (nc == 5) { /* ZFS_IOC_POOL_STATS */
		elem = NULL;
		while ((elem = nvlist_next_nvpair(nv, elem)) != NULL) {
			if (nvpair_value_nvlist(elem, &nvp) == 0)
				zfs_ioctl_compat_fix_stats_nvlist(nvp);
		}
		elem = NULL;
	} else
		zfs_ioctl_compat_fix_stats_nvlist(nv);

	error = zfs_ioctl_compat_put_nvlist(zc, nv);

	nvlist_free(nv);

	return (error);
}