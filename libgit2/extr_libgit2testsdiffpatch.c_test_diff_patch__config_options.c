#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  git_tree ;
typedef  int /*<<< orphan*/  git_patch ;
struct TYPE_11__ {int count; char** strings; } ;
struct TYPE_12__ {TYPE_1__ pathspec; } ;
typedef  TYPE_2__ git_diff_options ;
typedef  int /*<<< orphan*/  git_diff ;
typedef  int /*<<< orphan*/  git_config ;
struct TYPE_13__ {int /*<<< orphan*/  ptr; } ;
typedef  TYPE_3__ git_buf ;

/* Variables and functions */
 TYPE_3__ GIT_BUF_INIT ; 
 TYPE_2__ GIT_DIFF_OPTIONS_INIT ; 
 int /*<<< orphan*/  cl_assert_equal_i (int,int) ; 
 int /*<<< orphan*/  cl_assert_equal_s (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_sandbox_init (char*) ; 
 int /*<<< orphan*/  g_repo ; 
 int /*<<< orphan*/  git_buf_clear (TYPE_3__*) ; 
 int /*<<< orphan*/  git_buf_dispose (TYPE_3__*) ; 
 int /*<<< orphan*/  git_config_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_config_set_int32 (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  git_config_set_string (int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/  git_diff_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_diff_index_to_workdir (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_2__*) ; 
 scalar_t__ git_diff_num_deltas (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_diff_tree_to_index (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  git_patch_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_patch_from_diff (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_patch_to_buf (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_repository_config (int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_tree_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * resolve_commit_oid_to_tree (int /*<<< orphan*/ ,char const*) ; 

void test_diff_patch__config_options(void)
{
	const char *one_sha = "26a125e"; /* current HEAD */
	git_tree *one;
	git_config *cfg;
	git_diff *diff;
	git_patch *patch;
	git_buf buf = GIT_BUF_INIT;
	git_diff_options opts = GIT_DIFF_OPTIONS_INIT;
	char *onefile = "staged_changes_modified_file";
	const char *expected1 = "diff --git c/staged_changes_modified_file i/staged_changes_modified_file\nindex 70bd944..906ee77 100644\n--- c/staged_changes_modified_file\n+++ i/staged_changes_modified_file\n@@ -1 +1,2 @@\n staged_changes_modified_file\n+staged_changes_modified_file\n";
	const char *expected2 = "diff --git i/staged_changes_modified_file w/staged_changes_modified_file\nindex 906ee77..011c344 100644\n--- i/staged_changes_modified_file\n+++ w/staged_changes_modified_file\n@@ -1,2 +1,3 @@\n staged_changes_modified_file\n staged_changes_modified_file\n+staged_changes_modified_file\n";
	const char *expected3 = "diff --git staged_changes_modified_file staged_changes_modified_file\nindex 906ee77..011c344 100644\n--- staged_changes_modified_file\n+++ staged_changes_modified_file\n@@ -1,2 +1,3 @@\n staged_changes_modified_file\n staged_changes_modified_file\n+staged_changes_modified_file\n";
	const char *expected4 = "diff --git staged_changes_modified_file staged_changes_modified_file\nindex 70bd9443ada0..906ee7711f4f 100644\n--- staged_changes_modified_file\n+++ staged_changes_modified_file\n@@ -1 +1,2 @@\n staged_changes_modified_file\n+staged_changes_modified_file\n";

	g_repo = cl_git_sandbox_init("status");
	cl_git_pass(git_repository_config(&cfg, g_repo));
	one = resolve_commit_oid_to_tree(g_repo, one_sha);
	opts.pathspec.count = 1;
	opts.pathspec.strings = &onefile;


	cl_git_pass(git_config_set_string(cfg, "diff.mnemonicprefix", "true"));

	cl_git_pass(git_diff_tree_to_index(&diff, g_repo, one, NULL, &opts));

	cl_assert_equal_i(1, (int)git_diff_num_deltas(diff));
	cl_git_pass(git_patch_from_diff(&patch, diff, 0));
	cl_git_pass(git_patch_to_buf(&buf, patch));
	cl_assert_equal_s(expected1, buf.ptr);

	git_buf_clear(&buf);
	git_patch_free(patch);
	git_diff_free(diff);

	cl_git_pass(git_diff_index_to_workdir(&diff, g_repo, NULL, &opts));

	cl_assert_equal_i(1, (int)git_diff_num_deltas(diff));
	cl_git_pass(git_patch_from_diff(&patch, diff, 0));
	cl_git_pass(git_patch_to_buf(&buf, patch));
	cl_assert_equal_s(expected2, buf.ptr);

	git_buf_clear(&buf);
	git_patch_free(patch);
	git_diff_free(diff);


	cl_git_pass(git_config_set_string(cfg, "diff.noprefix", "true"));

	cl_git_pass(git_diff_index_to_workdir(&diff, g_repo, NULL, &opts));

	cl_assert_equal_i(1, (int)git_diff_num_deltas(diff));
	cl_git_pass(git_patch_from_diff(&patch, diff, 0));
	cl_git_pass(git_patch_to_buf(&buf, patch));
	cl_assert_equal_s(expected3, buf.ptr);

	git_buf_clear(&buf);
	git_patch_free(patch);
	git_diff_free(diff);


	cl_git_pass(git_config_set_int32(cfg, "core.abbrev", 12));

	cl_git_pass(git_diff_tree_to_index(&diff, g_repo, one, NULL, &opts));

	cl_assert_equal_i(1, (int)git_diff_num_deltas(diff));
	cl_git_pass(git_patch_from_diff(&patch, diff, 0));
	cl_git_pass(git_patch_to_buf(&buf, patch));
	cl_assert_equal_s(expected4, buf.ptr);

	git_buf_clear(&buf);
	git_patch_free(patch);
	git_diff_free(diff);

	git_buf_dispose(&buf);
	git_tree_free(one);
	git_config_free(cfg);
}