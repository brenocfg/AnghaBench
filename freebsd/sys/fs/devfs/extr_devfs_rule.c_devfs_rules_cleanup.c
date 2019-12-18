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
struct devfs_ruleset {int /*<<< orphan*/  ds_refcount; } ;
struct devfs_mount {scalar_t__ dm_ruleset; int /*<<< orphan*/  dm_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  SX_XLOCKED ; 
 struct devfs_ruleset* devfs_ruleset_bynum (scalar_t__) ; 
 int /*<<< orphan*/  devfs_ruleset_reap (struct devfs_ruleset*) ; 
 int /*<<< orphan*/  sx_assert (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void
devfs_rules_cleanup(struct devfs_mount *dm)
{
	struct devfs_ruleset *ds;

	sx_assert(&dm->dm_lock, SX_XLOCKED);
	if (dm->dm_ruleset != 0) {
		ds = devfs_ruleset_bynum(dm->dm_ruleset);
		--ds->ds_refcount;
		devfs_ruleset_reap(ds);
	}
}