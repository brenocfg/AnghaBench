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
struct TYPE_4__ {int /*<<< orphan*/ * vdev_path; scalar_t__ vdev_guid; } ;
typedef  TYPE_1__ vdev_t ;
typedef  int /*<<< orphan*/  u_longlong_t ;

/* Variables and functions */
 void* spa_strdup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spa_strfree (int /*<<< orphan*/ *) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfs_dbgmsg (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,...) ; 

__attribute__((used)) static void
vdev_copy_path_impl(vdev_t *svd, vdev_t *dvd)
{
	if (svd->vdev_path != NULL && dvd->vdev_path != NULL) {
		if (strcmp(svd->vdev_path, dvd->vdev_path) != 0) {
			zfs_dbgmsg("vdev_copy_path: vdev %llu: path changed "
			    "from '%s' to '%s'", (u_longlong_t)dvd->vdev_guid,
			    dvd->vdev_path, svd->vdev_path);
			spa_strfree(dvd->vdev_path);
			dvd->vdev_path = spa_strdup(svd->vdev_path);
		}
	} else if (svd->vdev_path != NULL) {
		dvd->vdev_path = spa_strdup(svd->vdev_path);
		zfs_dbgmsg("vdev_copy_path: vdev %llu: path set to '%s'",
		    (u_longlong_t)dvd->vdev_guid, dvd->vdev_path);
	}
}