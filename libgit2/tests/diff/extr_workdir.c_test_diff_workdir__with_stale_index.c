#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  git_repository ;
typedef  int /*<<< orphan*/  git_index ;
struct TYPE_7__ {int context_lines; int interhunk_lines; int flags; } ;
typedef  TYPE_1__ git_diff_options ;
typedef  int /*<<< orphan*/  git_diff ;
typedef  int /*<<< orphan*/  exp ;
struct TYPE_8__ {int /*<<< orphan*/ * file_status; int /*<<< orphan*/  files; } ;
typedef  TYPE_2__ diff_expects ;

/* Variables and functions */
 size_t GIT_DELTA_ADDED ; 
 size_t GIT_DELTA_DELETED ; 
 size_t GIT_DELTA_MODIFIED ; 
 size_t GIT_DELTA_UNMODIFIED ; 
 size_t GIT_DELTA_UNTRACKED ; 
 int GIT_DIFF_INCLUDE_UNMODIFIED ; 
 int GIT_DIFF_INCLUDE_UNTRACKED ; 
 TYPE_1__ GIT_DIFF_OPTIONS_INIT ; 
 int /*<<< orphan*/  cl_assert_equal_i (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * cl_git_sandbox_init (char*) ; 
 int /*<<< orphan*/  diff_binary_cb ; 
 int /*<<< orphan*/  diff_file_cb ; 
 int /*<<< orphan*/  diff_hunk_cb ; 
 int /*<<< orphan*/  diff_line_cb ; 
 int /*<<< orphan*/ * g_repo ; 
 int /*<<< orphan*/  git_diff_foreach (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  git_diff_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_diff_index_to_workdir (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  git_index_add_bypath (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  git_index_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_index_remove_bypath (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  git_index_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_repository_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_repository_index (int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_repository_open (int /*<<< orphan*/ **,char*) ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 

void test_diff_workdir__with_stale_index(void)
{
	git_diff_options opts = GIT_DIFF_OPTIONS_INIT;
	git_diff *diff = NULL;
	git_index *idx = NULL;
	diff_expects exp;

	g_repo = cl_git_sandbox_init("status");
	cl_git_pass(git_repository_index(&idx, g_repo));

	/* make the in-memory index invalid */
	{
		git_repository *r2;
		git_index *idx2;
		cl_git_pass(git_repository_open(&r2, "status"));
		cl_git_pass(git_repository_index(&idx2, r2));
		cl_git_pass(git_index_add_bypath(idx2, "new_file"));
		cl_git_pass(git_index_add_bypath(idx2, "subdir/new_file"));
		cl_git_pass(git_index_remove_bypath(idx2, "staged_new_file"));
		cl_git_pass(git_index_remove_bypath(idx2, "staged_changes_file_deleted"));
		cl_git_pass(git_index_write(idx2));
		git_index_free(idx2);
		git_repository_free(r2);
	}

	opts.context_lines = 3;
	opts.interhunk_lines = 1;
	opts.flags |= GIT_DIFF_INCLUDE_UNTRACKED | GIT_DIFF_INCLUDE_UNMODIFIED;

	/* first try with index pointer which should prevent reload */

	cl_git_pass(git_diff_index_to_workdir(&diff, g_repo, idx, &opts));

	memset(&exp, 0, sizeof(exp));

	cl_git_pass(git_diff_foreach(
		diff, diff_file_cb, diff_binary_cb, diff_hunk_cb, diff_line_cb, &exp));

	cl_assert_equal_i(17, exp.files);
	cl_assert_equal_i(0, exp.file_status[GIT_DELTA_ADDED]);
	cl_assert_equal_i(4, exp.file_status[GIT_DELTA_DELETED]);
	cl_assert_equal_i(4, exp.file_status[GIT_DELTA_MODIFIED]);
	cl_assert_equal_i(4, exp.file_status[GIT_DELTA_UNTRACKED]);
	cl_assert_equal_i(5, exp.file_status[GIT_DELTA_UNMODIFIED]);

	git_diff_free(diff);

	/* now let's try without the index pointer which should trigger reload */

	/* two files that were UNTRACKED should have become UNMODIFIED */
	/* one file that was UNMODIFIED should now have become UNTRACKED */
	/* one file that was DELETED should now be gone completely */

	cl_git_pass(git_diff_index_to_workdir(&diff, g_repo, NULL, &opts));

	memset(&exp, 0, sizeof(exp));

	cl_git_pass(git_diff_foreach(
		diff, diff_file_cb, diff_binary_cb, diff_hunk_cb, diff_line_cb, &exp));

	git_diff_free(diff);

	cl_assert_equal_i(16, exp.files);
	cl_assert_equal_i(0, exp.file_status[GIT_DELTA_ADDED]);
	cl_assert_equal_i(3, exp.file_status[GIT_DELTA_DELETED]);
	cl_assert_equal_i(4, exp.file_status[GIT_DELTA_MODIFIED]);
	cl_assert_equal_i(3, exp.file_status[GIT_DELTA_UNTRACKED]);
	cl_assert_equal_i(6, exp.file_status[GIT_DELTA_UNMODIFIED]);

	git_index_free(idx);
}