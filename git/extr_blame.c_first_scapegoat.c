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
struct rev_info {int /*<<< orphan*/  children; scalar_t__ first_parent_only; } ;
struct commit_list {int /*<<< orphan*/ * next; } ;
struct commit {int /*<<< orphan*/  object; struct commit_list* parents; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_commit_list (int /*<<< orphan*/ *) ; 
 struct commit_list* lookup_decoration (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct commit_list *first_scapegoat(struct rev_info *revs, struct commit *commit,
					int reverse)
{
	if (!reverse) {
		if (revs->first_parent_only &&
		    commit->parents &&
		    commit->parents->next) {
			free_commit_list(commit->parents->next);
			commit->parents->next = NULL;
		}
		return commit->parents;
	}
	return lookup_decoration(&revs->children, &commit->object);
}