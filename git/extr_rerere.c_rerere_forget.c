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
struct string_list_item {int /*<<< orphan*/  string; } ;
struct string_list {int nr; struct string_list_item* items; } ;
struct repository {int /*<<< orphan*/  index; } ;
struct pathspec {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  RERERE_NOAUTOUPDATE ; 
 struct string_list STRING_LIST_INIT_DUP ; 
 int /*<<< orphan*/  _ (char*) ; 
 int error (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  find_conflict (struct repository*,struct string_list*) ; 
 int /*<<< orphan*/  match_pathspec (int /*<<< orphan*/ ,struct pathspec*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ repo_read_index (struct repository*) ; 
 int /*<<< orphan*/  rerere_forget_one_path (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct string_list*) ; 
 int setup_rerere (struct repository*,struct string_list*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unmerge_index (int /*<<< orphan*/ ,struct pathspec*) ; 
 int write_rr (struct string_list*,int) ; 

int rerere_forget(struct repository *r, struct pathspec *pathspec)
{
	int i, fd;
	struct string_list conflict = STRING_LIST_INIT_DUP;
	struct string_list merge_rr = STRING_LIST_INIT_DUP;

	if (repo_read_index(r) < 0)
		return error(_("index file corrupt"));

	fd = setup_rerere(r, &merge_rr, RERERE_NOAUTOUPDATE);
	if (fd < 0)
		return 0;

	/*
	 * The paths may have been resolved (incorrectly);
	 * recover the original conflicted state and then
	 * find the conflicted paths.
	 */
	unmerge_index(r->index, pathspec);
	find_conflict(r, &conflict);
	for (i = 0; i < conflict.nr; i++) {
		struct string_list_item *it = &conflict.items[i];
		if (!match_pathspec(r->index, pathspec, it->string,
				    strlen(it->string), 0, NULL, 0))
			continue;
		rerere_forget_one_path(r->index, it->string, &merge_rr);
	}
	return write_rr(&merge_rr, fd);
}