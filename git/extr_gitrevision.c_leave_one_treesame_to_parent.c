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
struct treesame_state {scalar_t__* treesame; } ;
struct rev_info {int /*<<< orphan*/  treesame; } ;
struct commit_list {struct commit* item; struct commit_list* next; } ;
struct TYPE_2__ {int flags; } ;
struct commit {TYPE_1__ object; struct commit_list* parents; } ;

/* Variables and functions */
 int TMP_MARK ; 
 struct treesame_state* lookup_decoration (int /*<<< orphan*/ *,TYPE_1__*) ; 

__attribute__((used)) static int leave_one_treesame_to_parent(struct rev_info *revs, struct commit *commit)
{
	struct treesame_state *ts = lookup_decoration(&revs->treesame, &commit->object);
	struct commit *unmarked = NULL, *marked = NULL;
	struct commit_list *p;
	unsigned n;

	for (p = commit->parents, n = 0; p; p = p->next, n++) {
		if (ts->treesame[n]) {
			if (p->item->object.flags & TMP_MARK) {
				if (!marked)
					marked = p->item;
			} else {
				if (!unmarked) {
					unmarked = p->item;
					break;
				}
			}
		}
	}

	/*
	 * If we are TREESAME to a marked-for-deletion parent, but not to any
	 * unmarked parents, unmark the first TREESAME parent. This is the
	 * parent that the default simplify_history==1 scan would have followed,
	 * and it doesn't make sense to omit that path when asking for a
	 * simplified full history. Retaining it improves the chances of
	 * understanding odd missed merges that took an old version of a file.
	 *
	 * Example:
	 *
	 *   I--------*X       A modified the file, but mainline merge X used
	 *    \       /        "-s ours", so took the version from I. X is
	 *     `-*A--'         TREESAME to I and !TREESAME to A.
	 *
	 * Default log from X would produce "I". Without this check,
	 * --full-history --simplify-merges would produce "I-A-X", showing
	 * the merge commit X and that it changed A, but not making clear that
	 * it had just taken the I version. With this check, the topology above
	 * is retained.
	 *
	 * Note that it is possible that the simplification chooses a different
	 * TREESAME parent from the default, in which case this test doesn't
	 * activate, and we _do_ drop the default parent. Example:
	 *
	 *   I------X         A modified the file, but it was reverted in B,
	 *    \    /          meaning mainline merge X is TREESAME to both
	 *    *A-*B           parents.
	 *
	 * Default log would produce "I" by following the first parent;
	 * --full-history --simplify-merges will produce "I-A-B". But this is a
	 * reasonable result - it presents a logical full history leading from
	 * I to X, and X is not an important merge.
	 */
	if (!unmarked && marked) {
		marked->object.flags &= ~TMP_MARK;
		return 1;
	}

	return 0;
}