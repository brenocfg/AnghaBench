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
typedef  int /*<<< orphan*/  ie ;
struct TYPE_9__ {int /*<<< orphan*/  flags; } ;
typedef  TYPE_1__ git_index_entry ;
typedef  int /*<<< orphan*/  git_index ;
typedef  int /*<<< orphan*/  git_diff_options ;
typedef  int /*<<< orphan*/  git_diff ;
typedef  int /*<<< orphan*/  exp ;
struct TYPE_10__ {int /*<<< orphan*/ * file_status; int /*<<< orphan*/  files; } ;
typedef  TYPE_2__ diff_expects ;

/* Variables and functions */
 size_t GIT_DELTA_ADDED ; 
 size_t GIT_DELTA_DELETED ; 
 size_t GIT_DELTA_MODIFIED ; 
 int /*<<< orphan*/  GIT_DIFF_OPTIONS_INIT ; 
 int /*<<< orphan*/  GIT_INDEX_ENTRY_VALID ; 
 int /*<<< orphan*/  cl_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_assert_equal_i (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_sandbox_init (char*) ; 
 int /*<<< orphan*/  diff_binary_cb ; 
 int /*<<< orphan*/  diff_file_cb ; 
 int /*<<< orphan*/  diff_hunk_cb ; 
 int /*<<< orphan*/  diff_line_cb ; 
 int /*<<< orphan*/  g_repo ; 
 int /*<<< orphan*/  git_diff_foreach (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  git_diff_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_diff_index_to_workdir (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_index_add (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  git_index_free (int /*<<< orphan*/ *) ; 
 TYPE_1__* git_index_get_bypath (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_index_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_repository_index (int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (TYPE_1__*,TYPE_1__ const*,int) ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 

void test_diff_workdir__to_index_with_assume_unchanged(void)
{
	git_diff_options opts = GIT_DIFF_OPTIONS_INIT;
	git_diff *diff = NULL;
	git_index *idx = NULL;
	diff_expects exp;
	const git_index_entry *iep;
	git_index_entry ie;

	g_repo = cl_git_sandbox_init("status");

	/* do initial diff */

	cl_git_pass(git_diff_index_to_workdir(&diff, g_repo, NULL, &opts));
	memset(&exp, 0, sizeof(exp));
	cl_git_pass(git_diff_foreach(
		diff, diff_file_cb, diff_binary_cb, diff_hunk_cb, diff_line_cb, &exp));
	cl_assert_equal_i(8, exp.files);
	cl_assert_equal_i(0, exp.file_status[GIT_DELTA_ADDED]);
	cl_assert_equal_i(4, exp.file_status[GIT_DELTA_DELETED]);
	cl_assert_equal_i(4, exp.file_status[GIT_DELTA_MODIFIED]);
	git_diff_free(diff);

	/* mark a couple of entries with ASSUME_UNCHANGED */

	cl_git_pass(git_repository_index(&idx, g_repo));

	cl_assert((iep = git_index_get_bypath(idx, "modified_file", 0)) != NULL);
	memcpy(&ie, iep, sizeof(ie));
	ie.flags |= GIT_INDEX_ENTRY_VALID;
	cl_git_pass(git_index_add(idx, &ie));

	cl_assert((iep = git_index_get_bypath(idx, "file_deleted", 0)) != NULL);
	memcpy(&ie, iep, sizeof(ie));
	ie.flags |= GIT_INDEX_ENTRY_VALID;
	cl_git_pass(git_index_add(idx, &ie));

	cl_git_pass(git_index_write(idx));
	git_index_free(idx);

	/* redo diff and see that entries are skipped */

	cl_git_pass(git_diff_index_to_workdir(&diff, g_repo, NULL, &opts));
	memset(&exp, 0, sizeof(exp));
	cl_git_pass(git_diff_foreach(
		diff, diff_file_cb, diff_binary_cb, diff_hunk_cb, diff_line_cb, &exp));
	cl_assert_equal_i(6, exp.files);
	cl_assert_equal_i(0, exp.file_status[GIT_DELTA_ADDED]);
	cl_assert_equal_i(3, exp.file_status[GIT_DELTA_DELETED]);
	cl_assert_equal_i(3, exp.file_status[GIT_DELTA_MODIFIED]);
	git_diff_free(diff);

}