#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  git_tree ;
struct TYPE_10__ {int /*<<< orphan*/  flags; } ;
typedef  TYPE_1__ git_diff_options ;
struct TYPE_11__ {int /*<<< orphan*/  flags; } ;
typedef  TYPE_2__ git_diff_find_options ;
typedef  int /*<<< orphan*/  git_diff ;
typedef  int /*<<< orphan*/  git_config ;
typedef  int /*<<< orphan*/  exp ;
struct TYPE_12__ {int /*<<< orphan*/ * file_status; int /*<<< orphan*/  files; } ;
typedef  TYPE_3__ diff_expects ;

/* Variables and functions */
 char* COPY_RENAME_COMMIT ; 
 size_t GIT_DELTA_ADDED ; 
 size_t GIT_DELTA_COPIED ; 
 size_t GIT_DELTA_DELETED ; 
 size_t GIT_DELTA_MODIFIED ; 
 size_t GIT_DELTA_RENAMED ; 
 size_t GIT_DELTA_UNMODIFIED ; 
 int /*<<< orphan*/  GIT_DIFF_FIND_BY_CONFIG ; 
 TYPE_2__ GIT_DIFF_FIND_OPTIONS_INIT ; 
 int /*<<< orphan*/  GIT_DIFF_INCLUDE_UNMODIFIED ; 
 TYPE_1__ GIT_DIFF_OPTIONS_INIT ; 
 char* INITIAL_COMMIT ; 
 char* REWRITE_COPY_COMMIT ; 
 int /*<<< orphan*/  cl_assert_equal_i (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  diff_binary_cb ; 
 int /*<<< orphan*/  diff_file_cb ; 
 int /*<<< orphan*/  diff_hunk_cb ; 
 int /*<<< orphan*/  diff_line_cb ; 
 int /*<<< orphan*/  g_repo ; 
 int /*<<< orphan*/  git_config_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_config_set_bool (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  git_config_set_string (int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/  git_diff_find_similar (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  git_diff_foreach (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  git_diff_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_diff_tree_to_tree (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  git_repository_config (int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_tree_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (TYPE_3__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * resolve_commit_oid_to_tree (int /*<<< orphan*/ ,char const*) ; 

void test_diff_rename__matches_config_behavior(void)
{
	const char *sha0 = INITIAL_COMMIT;
	const char *sha1 = COPY_RENAME_COMMIT;
	const char *sha2 = REWRITE_COPY_COMMIT;

	git_tree *tree0, *tree1, *tree2;
	git_config *cfg;
	git_diff *diff;
	git_diff_options diffopts = GIT_DIFF_OPTIONS_INIT;
	git_diff_find_options opts = GIT_DIFF_FIND_OPTIONS_INIT;
	diff_expects exp;

	opts.flags = GIT_DIFF_FIND_BY_CONFIG;
	tree0 = resolve_commit_oid_to_tree(g_repo, sha0);
	tree1 = resolve_commit_oid_to_tree(g_repo, sha1);
	tree2 = resolve_commit_oid_to_tree(g_repo, sha2);

	diffopts.flags |= GIT_DIFF_INCLUDE_UNMODIFIED;
	cl_git_pass(git_repository_config(&cfg, g_repo));

	/* diff.renames = false; no rename detection should happen */
	cl_git_pass(git_config_set_bool(cfg, "diff.renames", false));
	cl_git_pass(git_diff_tree_to_tree(
				&diff, g_repo, tree0, tree1, &diffopts));
	memset(&exp, 0, sizeof(exp));
	cl_git_pass(git_diff_find_similar(diff, &opts));
	cl_git_pass(git_diff_foreach(diff,
				diff_file_cb, diff_binary_cb, diff_hunk_cb, diff_line_cb, &exp));
	cl_assert_equal_i(4, exp.files);
	cl_assert_equal_i(1, exp.file_status[GIT_DELTA_UNMODIFIED]);
	cl_assert_equal_i(2, exp.file_status[GIT_DELTA_ADDED]);
	cl_assert_equal_i(1, exp.file_status[GIT_DELTA_DELETED]);
	git_diff_free(diff);

	/* diff.renames = true; should act like -M */
	cl_git_pass(git_config_set_bool(cfg, "diff.renames", true));
	cl_git_pass(git_diff_tree_to_tree(
				&diff, g_repo, tree0, tree1, &diffopts));
	memset(&exp, 0, sizeof(exp));
	cl_git_pass(git_diff_find_similar(diff, &opts));
	cl_git_pass(git_diff_foreach(diff,
				diff_file_cb, diff_binary_cb, diff_hunk_cb, diff_line_cb, &exp));
	cl_assert_equal_i(3, exp.files);
	cl_assert_equal_i(1, exp.file_status[GIT_DELTA_UNMODIFIED]);
	cl_assert_equal_i(1, exp.file_status[GIT_DELTA_ADDED]);
	cl_assert_equal_i(1, exp.file_status[GIT_DELTA_RENAMED]);
	git_diff_free(diff);

	/* diff.renames = copies; should act like -M -C */
	cl_git_pass(git_config_set_string(cfg, "diff.renames", "copies"));
	cl_git_pass(git_diff_tree_to_tree(
				&diff, g_repo, tree1, tree2, &diffopts));
	memset(&exp, 0, sizeof(exp));
	cl_git_pass(git_diff_find_similar(diff, &opts));
	cl_git_pass(git_diff_foreach(diff,
				diff_file_cb, diff_binary_cb, diff_hunk_cb, diff_line_cb, &exp));
	cl_assert_equal_i(4, exp.files);
	cl_assert_equal_i(1, exp.file_status[GIT_DELTA_UNMODIFIED]);
	cl_assert_equal_i(2, exp.file_status[GIT_DELTA_MODIFIED]);
	cl_assert_equal_i(1, exp.file_status[GIT_DELTA_COPIED]);
	git_diff_free(diff);

	/* NULL find options is the same as GIT_DIFF_FIND_BY_CONFIG */
	cl_git_pass(git_diff_tree_to_tree(
				&diff, g_repo, tree1, tree2, &diffopts));
	memset(&exp, 0, sizeof(exp));
	cl_git_pass(git_diff_find_similar(diff, NULL));
	cl_git_pass(git_diff_foreach(diff,
				diff_file_cb, diff_binary_cb, diff_hunk_cb, diff_line_cb, &exp));
	cl_assert_equal_i(4, exp.files);
	cl_assert_equal_i(1, exp.file_status[GIT_DELTA_UNMODIFIED]);
	cl_assert_equal_i(2, exp.file_status[GIT_DELTA_MODIFIED]);
	cl_assert_equal_i(1, exp.file_status[GIT_DELTA_COPIED]);
	git_diff_free(diff);

	/* Cleanup */
	git_tree_free(tree0);
	git_tree_free(tree1);
	git_tree_free(tree2);
	git_config_free(cfg);
}