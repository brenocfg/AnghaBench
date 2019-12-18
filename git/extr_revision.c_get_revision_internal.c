#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct rev_info {int boundary; scalar_t__ max_count; scalar_t__ skip_count; int /*<<< orphan*/  boundary_commits; int /*<<< orphan*/  commits; } ;
struct object {int flags; } ;
struct commit_list {TYPE_2__* item; struct commit_list* next; } ;
struct TYPE_3__ {int flags; } ;
struct commit {struct commit_list* parents; TYPE_1__ object; } ;
struct TYPE_4__ {struct object object; } ;

/* Variables and functions */
 int CHILD_SHOWN ; 
 int SHOWN ; 
 int /*<<< orphan*/  add_object_array (struct object*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  create_boundary_commit_list (struct rev_info*) ; 
 int /*<<< orphan*/  gc_boundary (int /*<<< orphan*/ *) ; 
 struct commit* get_revision_1 (struct rev_info*) ; 
 struct commit* pop_commit (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct commit *get_revision_internal(struct rev_info *revs)
{
	struct commit *c = NULL;
	struct commit_list *l;

	if (revs->boundary == 2) {
		/*
		 * All of the normal commits have already been returned,
		 * and we are now returning boundary commits.
		 * create_boundary_commit_list() has populated
		 * revs->commits with the remaining commits to return.
		 */
		c = pop_commit(&revs->commits);
		if (c)
			c->object.flags |= SHOWN;
		return c;
	}

	/*
	 * If our max_count counter has reached zero, then we are done. We
	 * don't simply return NULL because we still might need to show
	 * boundary commits. But we want to avoid calling get_revision_1, which
	 * might do a considerable amount of work finding the next commit only
	 * for us to throw it away.
	 *
	 * If it is non-zero, then either we don't have a max_count at all
	 * (-1), or it is still counting, in which case we decrement.
	 */
	if (revs->max_count) {
		c = get_revision_1(revs);
		if (c) {
			while (revs->skip_count > 0) {
				revs->skip_count--;
				c = get_revision_1(revs);
				if (!c)
					break;
			}
		}

		if (revs->max_count > 0)
			revs->max_count--;
	}

	if (c)
		c->object.flags |= SHOWN;

	if (!revs->boundary)
		return c;

	if (!c) {
		/*
		 * get_revision_1() runs out the commits, and
		 * we are done computing the boundaries.
		 * switch to boundary commits output mode.
		 */
		revs->boundary = 2;

		/*
		 * Update revs->commits to contain the list of
		 * boundary commits.
		 */
		create_boundary_commit_list(revs);

		return get_revision_internal(revs);
	}

	/*
	 * boundary commits are the commits that are parents of the
	 * ones we got from get_revision_1() but they themselves are
	 * not returned from get_revision_1().  Before returning
	 * 'c', we need to mark its parents that they could be boundaries.
	 */

	for (l = c->parents; l; l = l->next) {
		struct object *p;
		p = &(l->item->object);
		if (p->flags & (CHILD_SHOWN | SHOWN))
			continue;
		p->flags |= CHILD_SHOWN;
		gc_boundary(&revs->boundary_commits);
		add_object_array(p, NULL, &revs->boundary_commits);
	}

	return c;
}