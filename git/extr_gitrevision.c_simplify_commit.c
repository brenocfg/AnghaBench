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
struct rev_info {scalar_t__ full_diff; scalar_t__ dense; scalar_t__ prune; } ;
struct commit {int dummy; } ;
typedef  enum commit_action { ____Placeholder_commit_action } commit_action ;

/* Variables and functions */
 int commit_error ; 
 int commit_show ; 
 int get_commit_action (struct rev_info*,struct commit*) ; 
 int /*<<< orphan*/  rewrite_one ; 
 scalar_t__ rewrite_parents (struct rev_info*,struct commit*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  save_parents (struct rev_info*,struct commit*) ; 
 scalar_t__ want_ancestry (struct rev_info*) ; 

enum commit_action simplify_commit(struct rev_info *revs, struct commit *commit)
{
	enum commit_action action = get_commit_action(revs, commit);

	if (action == commit_show &&
	    revs->prune && revs->dense && want_ancestry(revs)) {
		/*
		 * --full-diff on simplified parents is no good: it
		 * will show spurious changes from the commits that
		 * were elided.  So we save the parents on the side
		 * when --full-diff is in effect.
		 */
		if (revs->full_diff)
			save_parents(revs, commit);
		if (rewrite_parents(revs, commit, rewrite_one) < 0)
			return commit_error;
	}
	return action;
}