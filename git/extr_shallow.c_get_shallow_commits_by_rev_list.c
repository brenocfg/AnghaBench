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
struct rev_info {int dummy; } ;
struct object {int flags; int /*<<< orphan*/  oid; } ;
struct commit_list {struct commit* item; struct commit_list* next; } ;
struct commit {struct object object; struct commit_list* parents; } ;

/* Variables and functions */
 int /*<<< orphan*/  clear_object_flags (int) ; 
 int /*<<< orphan*/  commit_list_insert (struct commit*,struct commit_list**) ; 
 int /*<<< orphan*/  die (char*,...) ; 
 int /*<<< orphan*/  free_commit_list (struct commit_list*) ; 
 int /*<<< orphan*/  is_repository_shallow (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  oid_to_hex (int /*<<< orphan*/ *) ; 
 scalar_t__ parse_commit (struct commit*) ; 
 scalar_t__ prepare_revision_walk (struct rev_info*) ; 
 int /*<<< orphan*/  repo_init_revisions (int /*<<< orphan*/ ,struct rev_info*,int /*<<< orphan*/ *) ; 
 scalar_t__ save_commit_buffer ; 
 int /*<<< orphan*/  setup_revisions (int,char const**,struct rev_info*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  show_commit ; 
 int /*<<< orphan*/  the_repository ; 
 int /*<<< orphan*/  traverse_commit_list (struct rev_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct commit_list**) ; 

struct commit_list *get_shallow_commits_by_rev_list(int ac, const char **av,
						    int shallow_flag,
						    int not_shallow_flag)
{
	struct commit_list *result = NULL, *p;
	struct commit_list *not_shallow_list = NULL;
	struct rev_info revs;
	int both_flags = shallow_flag | not_shallow_flag;

	/*
	 * SHALLOW (excluded) and NOT_SHALLOW (included) should not be
	 * set at this point. But better be safe than sorry.
	 */
	clear_object_flags(both_flags);

	is_repository_shallow(the_repository); /* make sure shallows are read */

	repo_init_revisions(the_repository, &revs, NULL);
	save_commit_buffer = 0;
	setup_revisions(ac, av, &revs, NULL);

	if (prepare_revision_walk(&revs))
		die("revision walk setup failed");
	traverse_commit_list(&revs, show_commit, NULL, &not_shallow_list);

	if (!not_shallow_list)
		die("no commits selected for shallow requests");

	/* Mark all reachable commits as NOT_SHALLOW */
	for (p = not_shallow_list; p; p = p->next)
		p->item->object.flags |= not_shallow_flag;

	/*
	 * mark border commits SHALLOW + NOT_SHALLOW.
	 * We cannot clear NOT_SHALLOW right now. Imagine border
	 * commit A is processed first, then commit B, whose parent is
	 * A, later. If NOT_SHALLOW on A is cleared at step 1, B
	 * itself is considered border at step 2, which is incorrect.
	 */
	for (p = not_shallow_list; p; p = p->next) {
		struct commit *c = p->item;
		struct commit_list *parent;

		if (parse_commit(c))
			die("unable to parse commit %s",
			    oid_to_hex(&c->object.oid));

		for (parent = c->parents; parent; parent = parent->next)
			if (!(parent->item->object.flags & not_shallow_flag)) {
				c->object.flags |= shallow_flag;
				commit_list_insert(c, &result);
				break;
			}
	}
	free_commit_list(not_shallow_list);

	/*
	 * Now we can clean up NOT_SHALLOW on border commits. Having
	 * both flags set can confuse the caller.
	 */
	for (p = result; p; p = p->next) {
		struct object *o = &p->item->object;
		if ((o->flags & both_flags) == both_flags)
			o->flags &= ~not_shallow_flag;
	}
	return result;
}