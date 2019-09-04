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
struct repository {int dummy; } ;
struct object_id {int dummy; } ;
struct commit_graft {int nr_parent; int /*<<< orphan*/  oid; } ;
struct TYPE_2__ {scalar_t__ parsed; } ;
struct commit {int /*<<< orphan*/ * parents; TYPE_1__ object; } ;

/* Variables and functions */
 struct commit* lookup_commit (int /*<<< orphan*/ ,struct object_id const*) ; 
 int /*<<< orphan*/  oidcpy (int /*<<< orphan*/ *,struct object_id const*) ; 
 int register_commit_graft (struct repository*,struct commit_graft*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  the_repository ; 
 struct commit_graft* xmalloc (int) ; 

int register_shallow(struct repository *r, const struct object_id *oid)
{
	struct commit_graft *graft =
		xmalloc(sizeof(struct commit_graft));
	struct commit *commit = lookup_commit(the_repository, oid);

	oidcpy(&graft->oid, oid);
	graft->nr_parent = -1;
	if (commit && commit->object.parsed)
		commit->parents = NULL;
	return register_commit_graft(r, graft, 0);
}