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
struct rev_info {struct commit_list* commits; int /*<<< orphan*/  prune; } ;
struct merge_simplify_state {struct commit* simplified; } ;
struct commit_list {struct commit_list* next; struct commit* item; } ;
struct commit {int dummy; } ;
struct TYPE_2__ {struct commit_list* next; } ;

/* Variables and functions */
 TYPE_1__* commit_list_insert (struct commit*,struct commit_list**) ; 
 struct merge_simplify_state* locate_simplify_state (struct rev_info*,struct commit*) ; 
 struct commit* pop_commit (struct commit_list**) ; 
 struct commit_list** simplify_one (struct rev_info*,struct commit*,struct commit_list**) ; 

__attribute__((used)) static void simplify_merges(struct rev_info *revs)
{
	struct commit_list *list, *next;
	struct commit_list *yet_to_do, **tail;
	struct commit *commit;

	if (!revs->prune)
		return;

	/* feed the list reversed */
	yet_to_do = NULL;
	for (list = revs->commits; list; list = next) {
		commit = list->item;
		next = list->next;
		/*
		 * Do not free(list) here yet; the original list
		 * is used later in this function.
		 */
		commit_list_insert(commit, &yet_to_do);
	}
	while (yet_to_do) {
		list = yet_to_do;
		yet_to_do = NULL;
		tail = &yet_to_do;
		while (list) {
			commit = pop_commit(&list);
			tail = simplify_one(revs, commit, tail);
		}
	}

	/* clean up the result, removing the simplified ones */
	list = revs->commits;
	revs->commits = NULL;
	tail = &revs->commits;
	while (list) {
		struct merge_simplify_state *st;

		commit = pop_commit(&list);
		st = locate_simplify_state(revs, commit);
		if (st->simplified == commit)
			tail = &commit_list_insert(commit, tail)->next;
	}
}