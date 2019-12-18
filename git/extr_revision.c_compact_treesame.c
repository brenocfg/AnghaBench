#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct treesame_state {unsigned int nparents; int* treesame; } ;
struct rev_info {int /*<<< orphan*/  treesame; scalar_t__ dense; } ;
struct TYPE_5__ {int flags; } ;
struct commit {TYPE_2__ object; TYPE_1__* parents; } ;
struct TYPE_4__ {scalar_t__ next; } ;

/* Variables and functions */
 int TREESAME ; 
 int /*<<< orphan*/  add_decoration (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  die (char*,...) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 struct treesame_state* lookup_decoration (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  memmove (int*,int*,unsigned int) ; 
 scalar_t__ rev_same_tree_as_empty (struct rev_info*,struct commit*) ; 

__attribute__((used)) static int compact_treesame(struct rev_info *revs, struct commit *commit, unsigned nth_parent)
{
	struct treesame_state *st;
	int old_same;

	if (!commit->parents) {
		/*
		 * Have just removed the only parent from a non-merge.
		 * Different handling, as we lack decoration.
		 */
		if (nth_parent != 0)
			die("compact_treesame %u", nth_parent);
		old_same = !!(commit->object.flags & TREESAME);
		if (rev_same_tree_as_empty(revs, commit))
			commit->object.flags |= TREESAME;
		else
			commit->object.flags &= ~TREESAME;
		return old_same;
	}

	st = lookup_decoration(&revs->treesame, &commit->object);
	if (!st || nth_parent >= st->nparents)
		die("compact_treesame %u", nth_parent);

	old_same = st->treesame[nth_parent];
	memmove(st->treesame + nth_parent,
		st->treesame + nth_parent + 1,
		st->nparents - nth_parent - 1);

	/*
	 * If we've just become a non-merge commit, update TREESAME
	 * immediately, and remove the no-longer-needed decoration.
	 * If still a merge, defer update until update_treesame().
	 */
	if (--st->nparents == 1) {
		if (commit->parents->next)
			die("compact_treesame parents mismatch");
		if (st->treesame[0] && revs->dense)
			commit->object.flags |= TREESAME;
		else
			commit->object.flags &= ~TREESAME;
		free(add_decoration(&revs->treesame, &commit->object, NULL));
	}

	return old_same;
}