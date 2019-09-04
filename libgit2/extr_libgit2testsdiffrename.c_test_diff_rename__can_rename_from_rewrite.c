#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct rename_expected {int member_0; unsigned int* member_1; char const** member_2; char const** member_3; scalar_t__ idx; scalar_t__ len; } ;
typedef  int /*<<< orphan*/  git_tree ;
typedef  int /*<<< orphan*/  git_object ;
typedef  int /*<<< orphan*/  git_index ;
typedef  int /*<<< orphan*/  git_diff_options ;
struct TYPE_4__ {int flags; } ;
typedef  TYPE_1__ git_diff_find_options ;
typedef  int /*<<< orphan*/  git_diff ;

/* Variables and functions */
 unsigned int GIT_DELTA_RENAMED ; 
 int GIT_DIFF_FIND_AND_BREAK_REWRITES ; 
 TYPE_1__ GIT_DIFF_FIND_OPTIONS_INIT ; 
 int GIT_DIFF_FIND_RENAMES_FROM_REWRITES ; 
 int GIT_DIFF_FIND_REWRITES ; 
 int /*<<< orphan*/  GIT_DIFF_OPTIONS_INIT ; 
 int /*<<< orphan*/  cl_assert (int) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_repo ; 
 int /*<<< orphan*/  git_diff_find_similar (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  git_diff_foreach (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct rename_expected*) ; 
 int /*<<< orphan*/  git_diff_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_diff_tree_to_index (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_index_add_bypath (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  git_index_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_index_remove_bypath (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  git_index_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_repository_index (int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_revparse_single (int /*<<< orphan*/ **,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  git_tree_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  p_rename (char*,char*) ; 
 int /*<<< orphan*/  test_names_expected ; 

void test_diff_rename__can_rename_from_rewrite(void)
{
	git_index *index;
	git_tree *tree;
	git_diff *diff;
	git_diff_options diffopts = GIT_DIFF_OPTIONS_INIT;
	git_diff_find_options findopts = GIT_DIFF_FIND_OPTIONS_INIT;

	unsigned int status[] = { GIT_DELTA_RENAMED, GIT_DELTA_RENAMED };
	const char *sources[] = { "ikeepsix.txt", "songof7cities.txt" };
	const char *targets[] = { "songof7cities.txt", "this-is-a-rename.txt" };
	struct rename_expected expect = { 2, status, sources, targets };

	cl_git_pass(git_repository_index(&index, g_repo));

	cl_git_pass(p_rename("renames/songof7cities.txt", "renames/this-is-a-rename.txt"));
	cl_git_pass(p_rename("renames/ikeepsix.txt", "renames/songof7cities.txt"));

	cl_git_pass(git_index_remove_bypath(index, "ikeepsix.txt"));

	cl_git_pass(git_index_add_bypath(index, "songof7cities.txt"));
	cl_git_pass(git_index_add_bypath(index, "this-is-a-rename.txt"));

	cl_git_pass(git_index_write(index));

	cl_git_pass(
		git_revparse_single((git_object **)&tree, g_repo, "HEAD^{tree}"));

	cl_git_pass(
		git_diff_tree_to_index(&diff, g_repo, tree, index, &diffopts));

	findopts.flags |= GIT_DIFF_FIND_AND_BREAK_REWRITES |
		GIT_DIFF_FIND_REWRITES |
		GIT_DIFF_FIND_RENAMES_FROM_REWRITES;

	cl_git_pass(git_diff_find_similar(diff, &findopts));

	cl_git_pass(git_diff_foreach(
		diff, test_names_expected, NULL, NULL, NULL, &expect));

	cl_assert(expect.idx == expect.len);

	git_diff_free(diff);
	git_tree_free(tree);
	git_index_free(index);
}