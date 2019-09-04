#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  git_patch ;
typedef  int /*<<< orphan*/  git_index ;
struct TYPE_9__ {int /*<<< orphan*/  flags; } ;
typedef  TYPE_1__ git_diff_options ;
typedef  int /*<<< orphan*/  git_diff ;
struct TYPE_10__ {int /*<<< orphan*/  ptr; } ;
typedef  TYPE_2__ git_buf ;

/* Variables and functions */
 TYPE_2__ GIT_BUF_INIT ; 
 TYPE_1__ GIT_DIFF_OPTIONS_INIT ; 
 int /*<<< orphan*/  GIT_DIFF_PATIENCE ; 
 int /*<<< orphan*/  cl_assert_equal_i (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_assert_equal_s (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_mkfile (char*,char*) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_rewritefile (char*,char*) ; 
 int /*<<< orphan*/  cl_git_sandbox_init (char*) ; 
 int /*<<< orphan*/  cl_repo_commit_from_index (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,char*) ; 
 int /*<<< orphan*/  cl_repo_set_bool (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  g_repo ; 
 int /*<<< orphan*/  git_buf_clear (TYPE_2__*) ; 
 int /*<<< orphan*/  git_buf_dispose (TYPE_2__*) ; 
 int /*<<< orphan*/  git_diff_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_diff_index_to_workdir (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  git_diff_num_deltas (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_index_add_bypath (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  git_index_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_patch_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_patch_from_diff (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_patch_to_buf (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_repository_index (int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 

void test_diff_workdir__patience_diff(void)
{
	git_index *index;
	git_diff_options opts = GIT_DIFF_OPTIONS_INIT;
	git_diff *diff = NULL;
	git_patch *patch = NULL;
	git_buf buf = GIT_BUF_INIT;
	const char *expected_normal = "diff --git a/test.txt b/test.txt\nindex 34a5acc..d52725f 100644\n--- a/test.txt\n+++ b/test.txt\n@@ -1,10 +1,7 @@\n When I wrote this\n I did not know\n-how to create\n-a patience diff\n I did not know\n how to create\n+a patience diff\n another problem\n-I did not know\n-how to create\n a minimal diff\n";
	const char *expected_patience = "diff --git a/test.txt b/test.txt\nindex 34a5acc..d52725f 100644\n--- a/test.txt\n+++ b/test.txt\n@@ -1,10 +1,7 @@\n When I wrote this\n I did not know\n+I did not know\n how to create\n a patience diff\n-I did not know\n-how to create\n another problem\n-I did not know\n-how to create\n a minimal diff\n";

	g_repo = cl_git_sandbox_init("empty_standard_repo");
	cl_repo_set_bool(g_repo, "core.autocrlf", true);
	cl_git_pass(git_repository_index(&index, g_repo));

	cl_git_mkfile(
		"empty_standard_repo/test.txt",
		"When I wrote this\nI did not know\nhow to create\na patience diff\nI did not know\nhow to create\nanother problem\nI did not know\nhow to create\na minimal diff\n");
	cl_git_pass(git_index_add_bypath(index, "test.txt"));
	cl_repo_commit_from_index(NULL, g_repo, NULL, 1372350000, "Base");
	git_index_free(index);

	cl_git_rewritefile(
		"empty_standard_repo/test.txt",
		"When I wrote this\nI did not know\nI did not know\nhow to create\na patience diff\nanother problem\na minimal diff\n");

	cl_git_pass(git_diff_index_to_workdir(&diff, g_repo, NULL, &opts));
	cl_assert_equal_i(1, git_diff_num_deltas(diff));
	cl_git_pass(git_patch_from_diff(&patch, diff, 0));
	cl_git_pass(git_patch_to_buf(&buf, patch));

	cl_assert_equal_s(expected_normal, buf.ptr);
	git_buf_clear(&buf);
	git_patch_free(patch);
	git_diff_free(diff);

	opts.flags |= GIT_DIFF_PATIENCE;

	cl_git_pass(git_diff_index_to_workdir(&diff, g_repo, NULL, &opts));
	cl_assert_equal_i(1, git_diff_num_deltas(diff));
	cl_git_pass(git_patch_from_diff(&patch, diff, 0));
	cl_git_pass(git_patch_to_buf(&buf, patch));

	cl_assert_equal_s(expected_patience, buf.ptr);
	git_buf_clear(&buf);

	git_buf_dispose(&buf);
	git_patch_free(patch);
	git_diff_free(diff);
}