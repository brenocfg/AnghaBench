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
struct object_array {unsigned int nr; struct object_array_entry* objects; } ;
struct rev_info {int /*<<< orphan*/  sort_order; int /*<<< orphan*/ * commits; struct object_array boundary_commits; } ;
struct object_array_entry {scalar_t__ item; } ;
struct TYPE_2__ {int flags; } ;
struct commit {TYPE_1__ object; } ;

/* Variables and functions */
 int BOUNDARY ; 
 int CHILD_SHOWN ; 
 int SHOWN ; 
 int /*<<< orphan*/  commit_list_insert (struct commit*,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  free_commit_list (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sort_in_topological_order (int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void create_boundary_commit_list(struct rev_info *revs)
{
	unsigned i;
	struct commit *c;
	struct object_array *array = &revs->boundary_commits;
	struct object_array_entry *objects = array->objects;

	/*
	 * If revs->commits is non-NULL at this point, an error occurred in
	 * get_revision_1().  Ignore the error and continue printing the
	 * boundary commits anyway.  (This is what the code has always
	 * done.)
	 */
	if (revs->commits) {
		free_commit_list(revs->commits);
		revs->commits = NULL;
	}

	/*
	 * Put all of the actual boundary commits from revs->boundary_commits
	 * into revs->commits
	 */
	for (i = 0; i < array->nr; i++) {
		c = (struct commit *)(objects[i].item);
		if (!c)
			continue;
		if (!(c->object.flags & CHILD_SHOWN))
			continue;
		if (c->object.flags & (SHOWN | BOUNDARY))
			continue;
		c->object.flags |= BOUNDARY;
		commit_list_insert(c, &revs->commits);
	}

	/*
	 * If revs->topo_order is set, sort the boundary commits
	 * in topological order
	 */
	sort_in_topological_order(&revs->commits, revs->sort_order);
}