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
struct devfs_dirent {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  SX_XLOCKED ; 
 int /*<<< orphan*/  devfs_rule_depth ; 
 int /*<<< orphan*/  devfs_ruleset_applyde (struct devfs_ruleset*,struct devfs_mount*,struct devfs_dirent*,int /*<<< orphan*/ ) ; 
 struct devfs_ruleset* devfs_ruleset_bynum (scalar_t__) ; 
 int /*<<< orphan*/  sx_assert (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sx_rules ; 
 int /*<<< orphan*/  sx_slock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sx_sunlock (int /*<<< orphan*/ *) ; 

void
devfs_rules_apply(struct devfs_mount *dm, struct devfs_dirent *de)
{
	struct devfs_ruleset *ds;

	sx_assert(&dm->dm_lock, SX_XLOCKED);

	if (dm->dm_ruleset == 0)
		return;
	sx_slock(&sx_rules);
	ds = devfs_ruleset_bynum(dm->dm_ruleset);
	KASSERT(ds != NULL, ("mount-point has NULL ruleset"));
	devfs_ruleset_applyde(ds, dm, de, devfs_rule_depth);
	sx_sunlock(&sx_rules);
}