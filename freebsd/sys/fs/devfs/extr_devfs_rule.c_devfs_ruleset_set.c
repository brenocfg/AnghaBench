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
struct devfs_mount {int /*<<< orphan*/  dm_lock; } ;
typedef  int /*<<< orphan*/  devfs_rsnum ;

/* Variables and functions */
 int /*<<< orphan*/  SX_XLOCKED ; 
 int /*<<< orphan*/  devfs_ruleset_use (int /*<<< orphan*/ ,struct devfs_mount*) ; 
 int /*<<< orphan*/  sx_assert (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sx_rules ; 
 int /*<<< orphan*/  sx_xlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sx_xunlock (int /*<<< orphan*/ *) ; 

void
devfs_ruleset_set(devfs_rsnum rsnum, struct devfs_mount *dm)
{

	sx_assert(&dm->dm_lock, SX_XLOCKED);

	sx_xlock(&sx_rules);
	devfs_ruleset_use(rsnum, dm);
	sx_xunlock(&sx_rules);
}