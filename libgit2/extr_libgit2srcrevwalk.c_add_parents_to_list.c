#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {scalar_t__ first_parent; int /*<<< orphan*/  hide_cb_payload; scalar_t__ (* hide_cb ) (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ;} ;
typedef  TYPE_1__ git_revwalk ;
struct TYPE_10__ {int added; int uninteresting; unsigned short out_degree; int seen; int /*<<< orphan*/  oid; struct TYPE_10__** parents; } ;
typedef  TYPE_2__ git_commit_list_node ;
typedef  int /*<<< orphan*/  git_commit_list ;

/* Variables and functions */
 int /*<<< orphan*/  git_commit_list_insert_by_date (TYPE_2__*,int /*<<< orphan*/ **) ; 
 int git_commit_list_parse (TYPE_1__*,TYPE_2__*) ; 
 int /*<<< orphan*/  mark_parents_uninteresting (TYPE_2__*) ; 
 scalar_t__ stub1 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int add_parents_to_list(git_revwalk *walk, git_commit_list_node *commit, git_commit_list **list)
{
	unsigned short i;
	int error;

	if (commit->added)
		return 0;

	commit->added = 1;

	/*
	 * Go full on in the uninteresting case as we want to include
	 * as many of these as we can.
	 *
	 * Usually we haven't parsed the parent of a parent, but if we
	 * have it we reached it via other means so we want to mark
	 * its parents recursively too.
	 */
	if (commit->uninteresting) {
		for (i = 0; i < commit->out_degree; i++) {
			git_commit_list_node *p = commit->parents[i];
			p->uninteresting = 1;

			/* git does it gently here, but we don't like missing objects */
			if ((error = git_commit_list_parse(walk, p)) < 0)
				return error;

			if (p->parents)
				mark_parents_uninteresting(p);

			p->seen = 1;
			git_commit_list_insert_by_date(p, list);
		}

		return 0;
	}

	/*
	 * Now on to what we do if the commit is indeed
	 * interesting. Here we do want things like first-parent take
	 * effect as this is what we'll be showing.
	 */
	for (i = 0; i < commit->out_degree; i++) {
		git_commit_list_node *p = commit->parents[i];

		if ((error = git_commit_list_parse(walk, p)) < 0)
			return error;

		if (walk->hide_cb && walk->hide_cb(&p->oid, walk->hide_cb_payload))
			continue;

		if (!p->seen) {
			p->seen = 1;
			git_commit_list_insert_by_date(p, list);
		}

		if (walk->first_parent)
			break;
	}
	return 0;
}