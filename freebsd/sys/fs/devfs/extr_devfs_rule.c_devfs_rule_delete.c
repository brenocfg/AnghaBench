#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct devfs_ruleset {int /*<<< orphan*/  ds_rules; int /*<<< orphan*/  ds_refcount; } ;
struct TYPE_2__ {int dr_iacts; int /*<<< orphan*/  dr_incset; } ;
struct devfs_krule {struct devfs_ruleset* dk_ruleset; TYPE_1__ dk_rule; } ;

/* Variables and functions */
 int DRA_INCSET ; 
 int /*<<< orphan*/  KASSERT (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  M_DEVFSRULE ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,struct devfs_krule*,int /*<<< orphan*/ ) ; 
 struct devfs_ruleset* devfs_ruleset_bynum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devfs_ruleset_reap (struct devfs_ruleset*) ; 
 int /*<<< orphan*/  dk_list ; 
 int /*<<< orphan*/  free (struct devfs_krule*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
devfs_rule_delete(struct devfs_krule *dk)
{
	struct devfs_ruleset *ds;

	if (dk->dk_rule.dr_iacts & DRA_INCSET) {
		ds = devfs_ruleset_bynum(dk->dk_rule.dr_incset);
		KASSERT(ds != NULL, ("DRA_INCSET but bad dr_incset"));
		--ds->ds_refcount;
		devfs_ruleset_reap(ds);
	}
	ds = dk->dk_ruleset;
	TAILQ_REMOVE(&ds->ds_rules, dk, dk_list);
	devfs_ruleset_reap(ds);
	free(dk, M_DEVFSRULE);
	return (0);
}