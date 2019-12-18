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
struct rev_info {int min_age; int min_parents; scalar_t__ max_parents; scalar_t__ dense; scalar_t__ prune; scalar_t__ unpacked; } ;
struct commit_list {int /*<<< orphan*/  item; struct commit_list* next; } ;
struct TYPE_2__ {int flags; int /*<<< orphan*/  oid; } ;
struct commit {struct commit_list* parents; TYPE_1__ object; } ;
typedef  enum commit_action { ____Placeholder_commit_action } commit_action ;

/* Variables and functions */
 int SHOWN ; 
 int TREESAME ; 
 int UNINTERESTING ; 
 int commit_ignore ; 
 int commit_list_count (struct commit_list*) ; 
 int /*<<< orphan*/  commit_match (struct commit*,struct rev_info*) ; 
 int commit_show ; 
 int comparison_date (struct rev_info*,struct commit*) ; 
 scalar_t__ has_object_pack (int /*<<< orphan*/ *) ; 
 scalar_t__ relevant_commit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  want_ancestry (struct rev_info*) ; 

enum commit_action get_commit_action(struct rev_info *revs, struct commit *commit)
{
	if (commit->object.flags & SHOWN)
		return commit_ignore;
	if (revs->unpacked && has_object_pack(&commit->object.oid))
		return commit_ignore;
	if (commit->object.flags & UNINTERESTING)
		return commit_ignore;
	if (revs->min_age != -1 &&
	    comparison_date(revs, commit) > revs->min_age)
			return commit_ignore;
	if (revs->min_parents || (revs->max_parents >= 0)) {
		int n = commit_list_count(commit->parents);
		if ((n < revs->min_parents) ||
		    ((revs->max_parents >= 0) && (n > revs->max_parents)))
			return commit_ignore;
	}
	if (!commit_match(commit, revs))
		return commit_ignore;
	if (revs->prune && revs->dense) {
		/* Commit without changes? */
		if (commit->object.flags & TREESAME) {
			int n;
			struct commit_list *p;
			/* drop merges unless we want parenthood */
			if (!want_ancestry(revs))
				return commit_ignore;
			/*
			 * If we want ancestry, then need to keep any merges
			 * between relevant commits to tie together topology.
			 * For consistency with TREESAME and simplification
			 * use "relevant" here rather than just INTERESTING,
			 * to treat bottom commit(s) as part of the topology.
			 */
			for (n = 0, p = commit->parents; p; p = p->next)
				if (relevant_commit(p->item))
					if (++n >= 2)
						return commit_show;
			return commit_ignore;
		}
	}
	return commit_show;
}