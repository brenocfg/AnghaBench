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
struct rev_info {scalar_t__ first_parent_only; } ;
struct commit_list {struct commit_list* next; struct commit* item; } ;
struct commit {int dummy; } ;

/* Variables and functions */
 scalar_t__ relevant_commit (struct commit*) ; 

__attribute__((used)) static struct commit *one_relevant_parent(const struct rev_info *revs,
					  struct commit_list *orig)
{
	struct commit_list *list = orig;
	struct commit *relevant = NULL;

	if (!orig)
		return NULL;

	/*
	 * For 1-parent commits, or if first-parent-only, then return that
	 * first parent (even if not "relevant" by the above definition).
	 * TREESAME will have been set purely on that parent.
	 */
	if (revs->first_parent_only || !orig->next)
		return orig->item;

	/*
	 * For multi-parent commits, identify a sole relevant parent, if any.
	 * If we have only one relevant parent, then TREESAME will be set purely
	 * with regard to that parent, and we can simplify accordingly.
	 *
	 * If we have more than one relevant parent, or no relevant parents
	 * (and multiple irrelevant ones), then we can't select a parent here
	 * and return NULL.
	 */
	while (list) {
		struct commit *commit = list->item;
		list = list->next;
		if (relevant_commit(commit)) {
			if (relevant)
				return NULL;
			relevant = commit;
		}
	}
	return relevant;
}