#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  study ;
struct object_array {int nr; TYPE_2__* objects; } ;
struct commit_list {struct commit* item; struct commit_list* next; } ;
struct TYPE_6__ {int flags; int /*<<< orphan*/  oid; int /*<<< orphan*/  parsed; } ;
struct commit {TYPE_3__ object; struct commit_list* parents; } ;
typedef  int /*<<< orphan*/  found ;
struct TYPE_5__ {TYPE_1__* item; } ;
struct TYPE_4__ {int flags; } ;

/* Variables and functions */
 int INCOMPLETE ; 
 int SEEN ; 
 int STUDYING ; 
 int /*<<< orphan*/  add_object_array (TYPE_3__*,int /*<<< orphan*/ *,struct object_array*) ; 
 int /*<<< orphan*/  get_commit_tree_oid (struct commit*) ; 
 int /*<<< orphan*/  memset (struct object_array*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  object_array_clear (struct object_array*) ; 
 scalar_t__ object_array_pop (struct object_array*) ; 
 int /*<<< orphan*/  parse_object (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  the_repository ; 
 int /*<<< orphan*/  tree_is_complete (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int commit_is_complete(struct commit *commit)
{
	struct object_array study;
	struct object_array found;
	int is_incomplete = 0;
	int i;

	/* early return */
	if (commit->object.flags & SEEN)
		return 1;
	if (commit->object.flags & INCOMPLETE)
		return 0;
	/*
	 * Find all commits that are reachable and are not marked as
	 * SEEN.  Then make sure the trees and blobs contained are
	 * complete.  After that, mark these commits also as SEEN.
	 * If some of the objects that are needed to complete this
	 * commit are missing, mark this commit as INCOMPLETE.
	 */
	memset(&study, 0, sizeof(study));
	memset(&found, 0, sizeof(found));
	add_object_array(&commit->object, NULL, &study);
	add_object_array(&commit->object, NULL, &found);
	commit->object.flags |= STUDYING;
	while (study.nr) {
		struct commit *c;
		struct commit_list *parent;

		c = (struct commit *)object_array_pop(&study);
		if (!c->object.parsed && !parse_object(the_repository, &c->object.oid))
			c->object.flags |= INCOMPLETE;

		if (c->object.flags & INCOMPLETE) {
			is_incomplete = 1;
			break;
		}
		else if (c->object.flags & SEEN)
			continue;
		for (parent = c->parents; parent; parent = parent->next) {
			struct commit *p = parent->item;
			if (p->object.flags & STUDYING)
				continue;
			p->object.flags |= STUDYING;
			add_object_array(&p->object, NULL, &study);
			add_object_array(&p->object, NULL, &found);
		}
	}
	if (!is_incomplete) {
		/*
		 * make sure all commits in "found" array have all the
		 * necessary objects.
		 */
		for (i = 0; i < found.nr; i++) {
			struct commit *c =
				(struct commit *)found.objects[i].item;
			if (!tree_is_complete(get_commit_tree_oid(c))) {
				is_incomplete = 1;
				c->object.flags |= INCOMPLETE;
			}
		}
		if (!is_incomplete) {
			/* mark all found commits as complete, iow SEEN */
			for (i = 0; i < found.nr; i++)
				found.objects[i].item->flags |= SEEN;
		}
	}
	/* clear flags from the objects we traversed */
	for (i = 0; i < found.nr; i++)
		found.objects[i].item->flags &= ~STUDYING;
	if (is_incomplete)
		commit->object.flags |= INCOMPLETE;
	else {
		/*
		 * If we come here, we have (1) traversed the ancestry chain
		 * from the "commit" until we reach SEEN commits (which are
		 * known to be complete), and (2) made sure that the commits
		 * encountered during the above traversal refer to trees that
		 * are complete.  Which means that we know *all* the commits
		 * we have seen during this process are complete.
		 */
		for (i = 0; i < found.nr; i++)
			found.objects[i].item->flags |= SEEN;
	}
	/* free object arrays */
	object_array_clear(&study);
	object_array_clear(&found);
	return !is_incomplete;
}