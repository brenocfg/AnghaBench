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
struct string_list {int strdup_strings; } ;

/* Variables and functions */
 int /*<<< orphan*/  REF_NO_DEREF ; 
 struct string_list STRING_LIST_INIT_NODUP ; 
 int delete_refs (char*,struct string_list*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  for_each_ref_in (char*,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  git_path_bisect_ancestors_ok () ; 
 int /*<<< orphan*/  git_path_bisect_expected_rev () ; 
 int /*<<< orphan*/  git_path_bisect_log () ; 
 int /*<<< orphan*/  git_path_bisect_names () ; 
 int /*<<< orphan*/  git_path_bisect_run () ; 
 int /*<<< orphan*/  git_path_bisect_start () ; 
 int /*<<< orphan*/  git_path_bisect_terms () ; 
 int /*<<< orphan*/  git_path_head_name () ; 
 int /*<<< orphan*/  mark_for_removal ; 
 int /*<<< orphan*/  string_list_append (struct string_list*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  string_list_clear (struct string_list*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unlink_or_warn (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xstrdup (char*) ; 

int bisect_clean_state(void)
{
	int result = 0;

	/* There may be some refs packed during bisection */
	struct string_list refs_for_removal = STRING_LIST_INIT_NODUP;
	for_each_ref_in("refs/bisect", mark_for_removal, (void *) &refs_for_removal);
	string_list_append(&refs_for_removal, xstrdup("BISECT_HEAD"));
	result = delete_refs("bisect: remove", &refs_for_removal, REF_NO_DEREF);
	refs_for_removal.strdup_strings = 1;
	string_list_clear(&refs_for_removal, 0);
	unlink_or_warn(git_path_bisect_expected_rev());
	unlink_or_warn(git_path_bisect_ancestors_ok());
	unlink_or_warn(git_path_bisect_log());
	unlink_or_warn(git_path_bisect_names());
	unlink_or_warn(git_path_bisect_run());
	unlink_or_warn(git_path_bisect_terms());
	/* Cleanup head-name if it got left by an old version of git-bisect */
	unlink_or_warn(git_path_head_name());
	/*
	 * Cleanup BISECT_START last to support the --no-checkout option
	 * introduced in the commit 4796e823a.
	 */
	unlink_or_warn(git_path_bisect_start());

	return result;
}