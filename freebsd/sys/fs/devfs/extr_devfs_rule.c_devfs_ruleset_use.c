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
struct devfs_mount {scalar_t__ dm_ruleset; } ;
typedef  scalar_t__ devfs_rsnum ;

/* Variables and functions */
 struct devfs_ruleset* devfs_ruleset_bynum (scalar_t__) ; 
 struct devfs_ruleset* devfs_ruleset_create (scalar_t__) ; 
 int /*<<< orphan*/  devfs_ruleset_reap (struct devfs_ruleset*) ; 

__attribute__((used)) static int
devfs_ruleset_use(devfs_rsnum rsnum, struct devfs_mount *dm)
{
	struct devfs_ruleset *cds, *ds;

	if (dm->dm_ruleset != 0) {
		cds = devfs_ruleset_bynum(dm->dm_ruleset);
		--cds->ds_refcount;
		devfs_ruleset_reap(cds);
	}

	if (rsnum == 0) {
		dm->dm_ruleset = 0;
		return (0);
	}

	ds = devfs_ruleset_bynum(rsnum);
	if (ds == NULL)
		ds = devfs_ruleset_create(rsnum);
	/* These should probably be made atomic somehow. */
	++ds->ds_refcount;
	dm->dm_ruleset = rsnum;

	return (0);
}