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
struct devfs_mount {unsigned int dm_generation; int /*<<< orphan*/  dm_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  SX_XLOCKED ; 
 unsigned int devfs_generation ; 
 scalar_t__ devfs_populate_loop (struct devfs_mount*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sx_assert (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void
devfs_populate(struct devfs_mount *dm)
{
	unsigned gen;

	sx_assert(&dm->dm_lock, SX_XLOCKED);
	gen = devfs_generation;
	if (dm->dm_generation == gen)
		return;
	while (devfs_populate_loop(dm, 0))
		continue;
	dm->dm_generation = gen;
}