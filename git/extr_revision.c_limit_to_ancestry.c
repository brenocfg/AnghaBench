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
struct commit_list {struct commit* item; struct commit_list* next; } ;
struct TYPE_2__ {int flags; } ;
struct commit {TYPE_1__ object; struct commit_list* parents; } ;

/* Variables and functions */
 int TMP_MARK ; 
 int UNINTERESTING ; 
 int /*<<< orphan*/  commit_list_insert (struct commit*,struct commit_list**) ; 
 int /*<<< orphan*/  free_commit_list (struct commit_list*) ; 

__attribute__((used)) static void limit_to_ancestry(struct commit_list *bottom, struct commit_list *list)
{
	struct commit_list *p;
	struct commit_list *rlist = NULL;
	int made_progress;

	/*
	 * Reverse the list so that it will be likely that we would
	 * process parents before children.
	 */
	for (p = list; p; p = p->next)
		commit_list_insert(p->item, &rlist);

	for (p = bottom; p; p = p->next)
		p->item->object.flags |= TMP_MARK;

	/*
	 * Mark the ones that can reach bottom commits in "list",
	 * in a bottom-up fashion.
	 */
	do {
		made_progress = 0;
		for (p = rlist; p; p = p->next) {
			struct commit *c = p->item;
			struct commit_list *parents;
			if (c->object.flags & (TMP_MARK | UNINTERESTING))
				continue;
			for (parents = c->parents;
			     parents;
			     parents = parents->next) {
				if (!(parents->item->object.flags & TMP_MARK))
					continue;
				c->object.flags |= TMP_MARK;
				made_progress = 1;
				break;
			}
		}
	} while (made_progress);

	/*
	 * NEEDSWORK: decide if we want to remove parents that are
	 * not marked with TMP_MARK from commit->parents for commits
	 * in the resulting list.  We may not want to do that, though.
	 */

	/*
	 * The ones that are not marked with TMP_MARK are uninteresting
	 */
	for (p = list; p; p = p->next) {
		struct commit *c = p->item;
		if (c->object.flags & TMP_MARK)
			continue;
		c->object.flags |= UNINTERESTING;
	}

	/* We are done with the TMP_MARK */
	for (p = list; p; p = p->next)
		p->item->object.flags &= ~TMP_MARK;
	for (p = bottom; p; p = p->next)
		p->item->object.flags &= ~TMP_MARK;
	free_commit_list(rlist);
}