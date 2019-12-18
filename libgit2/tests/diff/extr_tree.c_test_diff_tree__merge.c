#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  git_tree ;
typedef  int /*<<< orphan*/  git_diff ;
struct TYPE_3__ {int /*<<< orphan*/  line_dels; int /*<<< orphan*/  line_adds; int /*<<< orphan*/  line_ctxt; int /*<<< orphan*/  lines; int /*<<< orphan*/  hunks; int /*<<< orphan*/ * file_status; int /*<<< orphan*/  files; } ;

/* Variables and functions */
 size_t GIT_DELTA_ADDED ; 
 size_t GIT_DELTA_DELETED ; 
 size_t GIT_DELTA_MODIFIED ; 
 int /*<<< orphan*/ * a ; 
 int /*<<< orphan*/ * b ; 
 int /*<<< orphan*/  cl_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_assert_equal_i (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_sandbox_init (char*) ; 
 int /*<<< orphan*/  diff_binary_cb ; 
 int /*<<< orphan*/  diff_file_cb ; 
 int /*<<< orphan*/  diff_hunk_cb ; 
 int /*<<< orphan*/  diff_line_cb ; 
 TYPE_1__ expect ; 
 int /*<<< orphan*/  g_repo ; 
 int /*<<< orphan*/  git_diff_foreach (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  git_diff_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_diff_merge (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_diff_tree_to_tree (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_tree_free (int /*<<< orphan*/ *) ; 
 void* resolve_commit_oid_to_tree (int /*<<< orphan*/ ,char const*) ; 

void test_diff_tree__merge(void)
{
	/* grabbed a couple of commit oids from the history of the attr repo */
	const char *a_commit = "605812a";
	const char *b_commit = "370fe9ec22";
	const char *c_commit = "f5b0af1fb4f5c";
	git_tree *c;
	git_diff *diff1 = NULL, *diff2 = NULL;

	g_repo = cl_git_sandbox_init("attr");

	cl_assert((a = resolve_commit_oid_to_tree(g_repo, a_commit)) != NULL);
	cl_assert((b = resolve_commit_oid_to_tree(g_repo, b_commit)) != NULL);
	cl_assert((c = resolve_commit_oid_to_tree(g_repo, c_commit)) != NULL);

	cl_git_pass(git_diff_tree_to_tree(&diff1, g_repo, a, b, NULL));

	cl_git_pass(git_diff_tree_to_tree(&diff2, g_repo, c, b, NULL));

	git_tree_free(c);

	cl_git_pass(git_diff_merge(diff1, diff2));

	git_diff_free(diff2);

	cl_git_pass(git_diff_foreach(
		diff1, diff_file_cb, diff_binary_cb, diff_hunk_cb, diff_line_cb, &expect));

	cl_assert_equal_i(6, expect.files);
	cl_assert_equal_i(2, expect.file_status[GIT_DELTA_ADDED]);
	cl_assert_equal_i(1, expect.file_status[GIT_DELTA_DELETED]);
	cl_assert_equal_i(3, expect.file_status[GIT_DELTA_MODIFIED]);

	cl_assert_equal_i(6, expect.hunks);

	cl_assert_equal_i(59, expect.lines);
	cl_assert_equal_i(1, expect.line_ctxt);
	cl_assert_equal_i(36, expect.line_adds);
	cl_assert_equal_i(22, expect.line_dels);

	git_diff_free(diff1);
}