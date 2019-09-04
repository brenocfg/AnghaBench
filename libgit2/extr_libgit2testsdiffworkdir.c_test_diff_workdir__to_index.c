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
struct TYPE_11__ {int /*<<< orphan*/  oid_calculations; int /*<<< orphan*/  stat_calls; } ;
typedef  TYPE_1__ git_diff_perfdata ;
struct TYPE_12__ {int context_lines; int interhunk_lines; int flags; } ;
typedef  TYPE_2__ git_diff_options ;
typedef  int /*<<< orphan*/  git_diff ;
typedef  int /*<<< orphan*/  exp ;
struct TYPE_13__ {int /*<<< orphan*/  line_dels; int /*<<< orphan*/  line_adds; int /*<<< orphan*/  line_ctxt; int /*<<< orphan*/  lines; int /*<<< orphan*/  hunks; int /*<<< orphan*/ * file_status; int /*<<< orphan*/  files; } ;
typedef  TYPE_3__ diff_expects ;

/* Variables and functions */
 size_t GIT_DELTA_ADDED ; 
 size_t GIT_DELTA_DELETED ; 
 size_t GIT_DELTA_IGNORED ; 
 size_t GIT_DELTA_MODIFIED ; 
 size_t GIT_DELTA_UNTRACKED ; 
 int GIT_DIFF_INCLUDE_IGNORED ; 
 int GIT_DIFF_INCLUDE_UNTRACKED ; 
 TYPE_2__ GIT_DIFF_OPTIONS_INIT ; 
 TYPE_1__ GIT_DIFF_PERFDATA_INIT ; 
 int /*<<< orphan*/  cl_assert_equal_i (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_assert_equal_sz (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_sandbox_init (char*) ; 
 int /*<<< orphan*/  diff_binary_cb ; 
 int /*<<< orphan*/  diff_file_cb ; 
 int /*<<< orphan*/  diff_foreach_via_iterator (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  diff_hunk_cb ; 
 int /*<<< orphan*/  diff_line_cb ; 
 int /*<<< orphan*/  g_repo ; 
 int /*<<< orphan*/  git_diff_foreach (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  git_diff_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_diff_get_perfdata (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_diff_index_to_workdir (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  memset (TYPE_3__*,int /*<<< orphan*/ ,int) ; 

void test_diff_workdir__to_index(void)
{
	git_diff_options opts = GIT_DIFF_OPTIONS_INIT;
	git_diff *diff = NULL;
	diff_expects exp;
	int use_iterator;

	g_repo = cl_git_sandbox_init("status");

	opts.context_lines = 3;
	opts.interhunk_lines = 1;
	opts.flags |= GIT_DIFF_INCLUDE_IGNORED | GIT_DIFF_INCLUDE_UNTRACKED;

	cl_git_pass(git_diff_index_to_workdir(&diff, g_repo, NULL, &opts));

	for (use_iterator = 0; use_iterator <= 1; use_iterator++) {
		memset(&exp, 0, sizeof(exp));

		if (use_iterator)
			cl_git_pass(diff_foreach_via_iterator(
				diff, diff_file_cb, diff_binary_cb, diff_hunk_cb, diff_line_cb, &exp));
		else
			cl_git_pass(git_diff_foreach(
				diff, diff_file_cb, diff_binary_cb, diff_hunk_cb, diff_line_cb, &exp));

		/* to generate these values:
		 * - cd to tests/resources/status,
		 * - mv .gitted .git
		 * - git diff --name-status
		 * - git diff
		 * - mv .git .gitted
		 */
		cl_assert_equal_i(13, exp.files);
		cl_assert_equal_i(0, exp.file_status[GIT_DELTA_ADDED]);
		cl_assert_equal_i(4, exp.file_status[GIT_DELTA_DELETED]);
		cl_assert_equal_i(4, exp.file_status[GIT_DELTA_MODIFIED]);
		cl_assert_equal_i(1, exp.file_status[GIT_DELTA_IGNORED]);
		cl_assert_equal_i(4, exp.file_status[GIT_DELTA_UNTRACKED]);

		cl_assert_equal_i(8, exp.hunks);

		cl_assert_equal_i(14, exp.lines);
		cl_assert_equal_i(5, exp.line_ctxt);
		cl_assert_equal_i(4, exp.line_adds);
		cl_assert_equal_i(5, exp.line_dels);
	}

	{
		git_diff_perfdata perf = GIT_DIFF_PERFDATA_INIT;
		cl_git_pass(git_diff_get_perfdata(&perf, diff));
		cl_assert_equal_sz(
			13 /* in root */ + 3 /* in subdir */, perf.stat_calls);
		cl_assert_equal_sz(5, perf.oid_calculations);
	}

	git_diff_free(diff);
}