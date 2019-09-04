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
struct repository {int dummy; } ;
struct commit_list {struct commit* item; struct commit_list* next; } ;
struct commit {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  all_flags ; 
 int /*<<< orphan*/  clear_commit_marks (struct commit*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clear_commit_marks_many (int,struct commit**,int /*<<< orphan*/ ) ; 
 int commit_list_count (struct commit_list*) ; 
 int /*<<< orphan*/  commit_list_insert_by_date (struct commit*,struct commit_list**) ; 
 int /*<<< orphan*/  free (struct commit**) ; 
 int /*<<< orphan*/  free_commit_list (struct commit_list*) ; 
 struct commit_list* merge_bases_many (struct repository*,struct commit*,int,struct commit**) ; 
 int remove_redundant (struct repository*,struct commit**,int) ; 
 struct commit** xcalloc (int,int) ; 

__attribute__((used)) static struct commit_list *get_merge_bases_many_0(struct repository *r,
						  struct commit *one,
						  int n,
						  struct commit **twos,
						  int cleanup)
{
	struct commit_list *list;
	struct commit **rslt;
	struct commit_list *result;
	int cnt, i;

	result = merge_bases_many(r, one, n, twos);
	for (i = 0; i < n; i++) {
		if (one == twos[i])
			return result;
	}
	if (!result || !result->next) {
		if (cleanup) {
			clear_commit_marks(one, all_flags);
			clear_commit_marks_many(n, twos, all_flags);
		}
		return result;
	}

	/* There are more than one */
	cnt = commit_list_count(result);
	rslt = xcalloc(cnt, sizeof(*rslt));
	for (list = result, i = 0; list; list = list->next)
		rslt[i++] = list->item;
	free_commit_list(result);

	clear_commit_marks(one, all_flags);
	clear_commit_marks_many(n, twos, all_flags);

	cnt = remove_redundant(r, rslt, cnt);
	result = NULL;
	for (i = 0; i < cnt; i++)
		commit_list_insert_by_date(rslt[i], &result);
	free(rslt);
	return result;
}