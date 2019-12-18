#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  git_tree ;
struct TYPE_6__ {int member_1; char** strings; int /*<<< orphan*/ * member_0; } ;
typedef  TYPE_2__ git_strarray ;
typedef  int /*<<< orphan*/  git_pathspec_match_list ;
typedef  int /*<<< orphan*/  git_pathspec ;
typedef  int /*<<< orphan*/  git_diff_options ;
typedef  int /*<<< orphan*/  git_diff ;
struct TYPE_5__ {int /*<<< orphan*/ * path; } ;
struct TYPE_7__ {scalar_t__ status; TYPE_1__ new_file; } ;

/* Variables and functions */
 int GIT_DELTA_ADDED ; 
 int GIT_DELTA_DELETED ; 
 int GIT_DELTA_MODIFIED ; 
 int /*<<< orphan*/  GIT_DIFF_OPTIONS_INIT ; 
 int /*<<< orphan*/  GIT_PATHSPEC_DEFAULT ; 
 int /*<<< orphan*/  cl_assert (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cl_assert_equal_i (int,int) ; 
 int /*<<< orphan*/  cl_assert_equal_s (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_repo ; 
 int /*<<< orphan*/  git_diff_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_diff_tree_to_tree (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_diff_tree_to_workdir (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_pathspec_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_pathspec_match_diff (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_4__* git_pathspec_match_list_diff_entry (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * git_pathspec_match_list_entry (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ git_pathspec_match_list_entrycount (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_pathspec_match_list_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_pathspec_match_tree (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_pathspec_new (int /*<<< orphan*/ **,TYPE_2__*) ; 
 int /*<<< orphan*/  git_tree_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * resolve_commit_oid_to_tree (int /*<<< orphan*/ ,char const*) ; 

void test_diff_pathspec__0(void)
{
	const char *a_commit = "26a125ee"; /* the current HEAD */
	const char *b_commit = "0017bd4a"; /* the start */
	git_tree *a = resolve_commit_oid_to_tree(g_repo, a_commit);
	git_tree *b = resolve_commit_oid_to_tree(g_repo, b_commit);
	git_diff_options opts = GIT_DIFF_OPTIONS_INIT;
	git_diff *diff = NULL;
	git_strarray paths = { NULL, 1 };
	char *path;
	git_pathspec *ps;
	git_pathspec_match_list *matches;

	cl_assert(a);
	cl_assert(b);

	path = "*_file";
	paths.strings = &path;
	cl_git_pass(git_pathspec_new(&ps, &paths));

	cl_git_pass(git_pathspec_match_tree(&matches, a, GIT_PATHSPEC_DEFAULT, ps));
	cl_assert_equal_i(7, (int)git_pathspec_match_list_entrycount(matches));
	cl_assert_equal_s("current_file", git_pathspec_match_list_entry(matches,0));
	cl_assert(git_pathspec_match_list_diff_entry(matches,0) == NULL);
	git_pathspec_match_list_free(matches);

	cl_git_pass(git_diff_tree_to_tree(&diff, g_repo, NULL, a, &opts));

	cl_git_pass(git_pathspec_match_diff(
		&matches, diff, GIT_PATHSPEC_DEFAULT, ps));
	cl_assert_equal_i(7, (int)git_pathspec_match_list_entrycount(matches));
	cl_assert(git_pathspec_match_list_diff_entry(matches, 0) != NULL);
	cl_assert(git_pathspec_match_list_entry(matches, 0) == NULL);
	cl_assert_equal_s("current_file",
		git_pathspec_match_list_diff_entry(matches,0)->new_file.path);
	cl_assert_equal_i(GIT_DELTA_ADDED,
		(int)git_pathspec_match_list_diff_entry(matches,0)->status);
	git_pathspec_match_list_free(matches);

	git_diff_free(diff);
	diff = NULL;

	cl_git_pass(git_diff_tree_to_tree(&diff, g_repo, a, b, &opts));

	cl_git_pass(git_pathspec_match_diff(
		&matches, diff, GIT_PATHSPEC_DEFAULT, ps));
	cl_assert_equal_i(3, (int)git_pathspec_match_list_entrycount(matches));
	cl_assert(git_pathspec_match_list_diff_entry(matches, 0) != NULL);
	cl_assert(git_pathspec_match_list_entry(matches, 0) == NULL);
	cl_assert_equal_s("subdir/current_file",
		git_pathspec_match_list_diff_entry(matches,0)->new_file.path);
	cl_assert_equal_i(GIT_DELTA_DELETED,
		(int)git_pathspec_match_list_diff_entry(matches,0)->status);
	git_pathspec_match_list_free(matches);

	git_diff_free(diff);
	diff = NULL;

	cl_git_pass(git_diff_tree_to_workdir(&diff, g_repo, a, &opts));

	cl_git_pass(git_pathspec_match_diff(
		&matches, diff, GIT_PATHSPEC_DEFAULT, ps));
	cl_assert_equal_i(4, (int)git_pathspec_match_list_entrycount(matches));
	cl_assert(git_pathspec_match_list_diff_entry(matches, 0) != NULL);
	cl_assert(git_pathspec_match_list_entry(matches, 0) == NULL);
	cl_assert_equal_s("modified_file",
		git_pathspec_match_list_diff_entry(matches,0)->new_file.path);
	cl_assert_equal_i(GIT_DELTA_MODIFIED,
		(int)git_pathspec_match_list_diff_entry(matches,0)->status);
	git_pathspec_match_list_free(matches);

	git_diff_free(diff);
	diff = NULL;

	git_tree_free(a);
	git_tree_free(b);
	git_pathspec_free(ps);
}