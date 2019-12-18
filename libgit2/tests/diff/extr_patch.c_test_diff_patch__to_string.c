#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  git_tree ;
typedef  int /*<<< orphan*/  git_patch ;
typedef  int /*<<< orphan*/  git_diff ;
struct TYPE_5__ {int /*<<< orphan*/  ptr; } ;
typedef  TYPE_1__ git_buf ;

/* Variables and functions */
 TYPE_1__ GIT_BUF_INIT ; 
 int /*<<< orphan*/  cl_assert_equal_i (int,int) ; 
 int /*<<< orphan*/  cl_assert_equal_s (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_assert_equal_sz (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_sandbox_init (char*) ; 
 int /*<<< orphan*/  g_repo ; 
 int /*<<< orphan*/  git_buf_dispose (TYPE_1__*) ; 
 int /*<<< orphan*/  git_diff_free (int /*<<< orphan*/ *) ; 
 scalar_t__ git_diff_num_deltas (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_diff_tree_to_tree (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_patch_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_patch_from_diff (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_patch_size (int /*<<< orphan*/ *,int,int,int) ; 
 int /*<<< orphan*/  git_patch_to_buf (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_tree_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * resolve_commit_oid_to_tree (int /*<<< orphan*/ ,char const*) ; 
 int strlen (char const*) ; 

void test_diff_patch__to_string(void)
{
	const char *one_sha = "26a125e";
	const char *another_sha = "735b6a2";
	git_tree *one, *another;
	git_diff *diff;
	git_patch *patch;
	git_buf buf = GIT_BUF_INIT;
	const char *expected = "diff --git a/subdir.txt b/subdir.txt\ndeleted file mode 100644\nindex e8ee89e..0000000\n--- a/subdir.txt\n+++ /dev/null\n@@ -1,2 +0,0 @@\n-Is it a bird?\n-Is it a plane?\n";

	g_repo = cl_git_sandbox_init("status");

	one = resolve_commit_oid_to_tree(g_repo, one_sha);
	another = resolve_commit_oid_to_tree(g_repo, another_sha);

	cl_git_pass(git_diff_tree_to_tree(&diff, g_repo, one, another, NULL));

	cl_assert_equal_i(1, (int)git_diff_num_deltas(diff));

	cl_git_pass(git_patch_from_diff(&patch, diff, 0));

	cl_git_pass(git_patch_to_buf(&buf, patch));

	cl_assert_equal_s(expected, buf.ptr);

	cl_assert_equal_sz(31, git_patch_size(patch, 0, 0, 0));
	cl_assert_equal_sz(31, git_patch_size(patch, 1, 0, 0));
	cl_assert_equal_sz(31 + 16, git_patch_size(patch, 1, 1, 0));
	cl_assert_equal_sz(strlen(expected), git_patch_size(patch, 1, 1, 1));

	git_buf_dispose(&buf);
	git_patch_free(patch);
	git_diff_free(diff);
	git_tree_free(another);
	git_tree_free(one);
}