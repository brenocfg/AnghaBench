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
struct devfs_ruleset {scalar_t__ ds_number; scalar_t__ ds_refcount; int /*<<< orphan*/  ds_rules; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  M_DEVFSRULE ; 
 int /*<<< orphan*/  TAILQ_EMPTY (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,struct devfs_ruleset*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devfs_rulesets ; 
 int /*<<< orphan*/  ds_list ; 
 int /*<<< orphan*/  free (struct devfs_ruleset*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
devfs_ruleset_reap(struct devfs_ruleset *ds)
{

	KASSERT(ds->ds_number != 0, ("reaping ruleset zero "));

	if (!TAILQ_EMPTY(&ds->ds_rules) || ds->ds_refcount != 0) 
		return;

	TAILQ_REMOVE(&devfs_rulesets, ds, ds_list);
	free(ds, M_DEVFSRULE);
}