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
struct commit_list {struct commit_list* next; struct commit* item; } ;
struct commit {int dummy; } ;

/* Variables and functions */
 int can_all_from_reach (struct commit_list*,struct commit_list*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  commit_list_insert (struct commit*,struct commit_list**) ; 
 int /*<<< orphan*/  free_commit_list (struct commit_list*) ; 
 scalar_t__ generation_numbers_enabled (int /*<<< orphan*/ ) ; 
 scalar_t__ in_merge_bases (struct commit*,struct commit*) ; 
 int /*<<< orphan*/  the_repository ; 

int is_descendant_of(struct commit *commit, struct commit_list *with_commit)
{
	if (!with_commit)
		return 1;

	if (generation_numbers_enabled(the_repository)) {
		struct commit_list *from_list = NULL;
		int result;
		commit_list_insert(commit, &from_list);
		result = can_all_from_reach(from_list, with_commit, 0);
		free_commit_list(from_list);
		return result;
	} else {
		while (with_commit) {
			struct commit *other;

			other = with_commit->item;
			with_commit = with_commit->next;
			if (in_merge_bases(other, commit))
				return 1;
		}
		return 0;
	}
}