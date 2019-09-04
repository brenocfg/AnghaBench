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
struct stat {scalar_t__ st_size; } ;
typedef  int /*<<< orphan*/  git_tree ;
typedef  int /*<<< orphan*/  git_patch ;
typedef  int /*<<< orphan*/  git_diff_options ;
typedef  int /*<<< orphan*/  git_diff ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_DIFF_OPTIONS_INIT ; 
 int /*<<< orphan*/  cl_assert (int) ; 
 int /*<<< orphan*/  cl_assert_equal_i (int,int) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_rewritefile (char*,char*) ; 
 int /*<<< orphan*/  cl_git_sandbox_init (char*) ; 
 int /*<<< orphan*/  g_repo ; 
 int /*<<< orphan*/  git_diff_free (int /*<<< orphan*/ *) ; 
 scalar_t__ git_diff_num_deltas (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_diff_tree_to_workdir (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_patch_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_patch_from_diff (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  git_path_exists (char*) ; 
 int /*<<< orphan*/  git_path_lstat (char*,struct stat*) ; 
 int /*<<< orphan*/  git_tree_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  p_unlink (char*) ; 
 int /*<<< orphan*/ * resolve_commit_oid_to_tree (int /*<<< orphan*/ ,char*) ; 

void test_diff_workdir__can_diff_empty_file(void)
{
	git_diff *diff;
	git_tree *tree;
	git_diff_options opts = GIT_DIFF_OPTIONS_INIT;
	struct stat st;
	git_patch *patch;

	g_repo = cl_git_sandbox_init("attr_index");

	tree = resolve_commit_oid_to_tree(g_repo, "3812cfef3661"); /* HEAD */

	/* baseline - make sure there are no outstanding diffs */

	cl_git_pass(git_diff_tree_to_workdir(&diff, g_repo, tree, &opts));
	cl_assert_equal_i(2, (int)git_diff_num_deltas(diff));
	git_diff_free(diff);

	/* empty contents of file */

	cl_git_rewritefile("attr_index/README.txt", "");
	cl_git_pass(git_path_lstat("attr_index/README.txt", &st));
	cl_assert_equal_i(0, (int)st.st_size);

	cl_git_pass(git_diff_tree_to_workdir(&diff, g_repo, tree, &opts));
	cl_assert_equal_i(3, (int)git_diff_num_deltas(diff));
	/* diffs are: .gitattributes, README.txt, sub/sub/.gitattributes */
	cl_git_pass(git_patch_from_diff(&patch, diff, 1));
	git_patch_free(patch);
	git_diff_free(diff);

	/* remove a file altogether */

	cl_git_pass(p_unlink("attr_index/README.txt"));
	cl_assert(!git_path_exists("attr_index/README.txt"));

	cl_git_pass(git_diff_tree_to_workdir(&diff, g_repo, tree, &opts));
	cl_assert_equal_i(3, (int)git_diff_num_deltas(diff));
	cl_git_pass(git_patch_from_diff(&patch, diff, 1));
	git_patch_free(patch);
	git_diff_free(diff);

	git_tree_free(tree);
}