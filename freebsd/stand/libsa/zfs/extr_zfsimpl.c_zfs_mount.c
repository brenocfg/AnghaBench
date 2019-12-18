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
typedef  scalar_t__ uint64_t ;
struct zfsmount {scalar_t__ rootobj; int /*<<< orphan*/  objset; int /*<<< orphan*/  const* spa; } ;
typedef  int /*<<< orphan*/  spa_t ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  printf (char*) ; 
 scalar_t__ zfs_get_root (int /*<<< orphan*/  const*,scalar_t__*) ; 
 scalar_t__ zfs_mount_dataset (int /*<<< orphan*/  const*,scalar_t__,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
zfs_mount(const spa_t *spa, uint64_t rootobj, struct zfsmount *mount)
{

	mount->spa = spa;

	/*
	 * Find the root object set if not explicitly provided
	 */
	if (rootobj == 0 && zfs_get_root(spa, &rootobj)) {
		printf("ZFS: can't find root filesystem\n");
		return (EIO);
	}

	if (zfs_mount_dataset(spa, rootobj, &mount->objset)) {
		printf("ZFS: can't open root filesystem\n");
		return (EIO);
	}

	mount->rootobj = rootobj;

	return (0);
}