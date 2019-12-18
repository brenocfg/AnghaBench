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
struct devfs_mount {int /*<<< orphan*/  dm_rootdir; int /*<<< orphan*/  dm_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  SX_XLOCKED ; 
 scalar_t__ devfs_populate_loop (struct devfs_mount*,int) ; 
 int /*<<< orphan*/  devfs_purge (struct devfs_mount*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sx_assert (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void
devfs_cleanup(struct devfs_mount *dm)
{

	sx_assert(&dm->dm_lock, SX_XLOCKED);
	while (devfs_populate_loop(dm, 1))
		continue;
	devfs_purge(dm, dm->dm_rootdir);
}