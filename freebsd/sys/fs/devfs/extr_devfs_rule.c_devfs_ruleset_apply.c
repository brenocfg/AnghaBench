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
struct devfs_ruleset {int dummy; } ;
struct devfs_mount {scalar_t__ dm_ruleset; int /*<<< orphan*/  dm_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  SX_XLOCKED ; 
 int /*<<< orphan*/  devfs_ruleset_applydm (struct devfs_ruleset*,struct devfs_mount*) ; 
 struct devfs_ruleset* devfs_ruleset_bynum (scalar_t__) ; 
 int /*<<< orphan*/  sx_assert (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sx_rules ; 
 int /*<<< orphan*/  sx_xlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sx_xunlock (int /*<<< orphan*/ *) ; 

void
devfs_ruleset_apply(struct devfs_mount *dm)
{
	struct devfs_ruleset *ds;

	sx_assert(&dm->dm_lock, SX_XLOCKED);

	sx_xlock(&sx_rules);
	if (dm->dm_ruleset == 0) {
		sx_xunlock(&sx_rules);
		return;
	}
	ds = devfs_ruleset_bynum(dm->dm_ruleset);
	if (ds != NULL)
		devfs_ruleset_applydm(ds, dm);
	sx_xunlock(&sx_rules);
}