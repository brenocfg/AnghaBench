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
typedef  int /*<<< orphan*/  git_index ;
struct TYPE_7__ {int /*<<< orphan*/  oid_calculations; int /*<<< orphan*/  stat_calls; } ;
typedef  TYPE_1__ git_diff_perfdata ;
struct TYPE_8__ {int flags; } ;
typedef  TYPE_2__ git_diff_options ;
typedef  int /*<<< orphan*/  git_diff ;
typedef  int /*<<< orphan*/  git_buf ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_BUF_INIT ; 
 int GIT_DIFF_INCLUDE_IGNORED ; 
 int GIT_DIFF_INCLUDE_UNTRACKED ; 
 TYPE_2__ GIT_DIFF_OPTIONS_INIT ; 
 TYPE_1__ GIT_DIFF_PERFDATA_INIT ; 
 int GIT_DIFF_UPDATE_INDEX ; 
 int /*<<< orphan*/  basic_diff_status (int /*<<< orphan*/ **,TYPE_2__*) ; 
 int /*<<< orphan*/  cl_assert_equal_sz (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_sandbox_init (char*) ; 
 int /*<<< orphan*/  g_repo ; 
 int /*<<< orphan*/  git_buf_dispose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_buf_sets (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  git_diff_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_diff_get_perfdata (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_path_direach (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_repository_index__weakptr (int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tick_index (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  touch_file ; 

void test_diff_workdir__can_update_index(void)
{
	git_diff_options opts = GIT_DIFF_OPTIONS_INIT;
	git_diff *diff = NULL;
	git_diff_perfdata perf = GIT_DIFF_PERFDATA_INIT;
	git_index *index;

	g_repo = cl_git_sandbox_init("status");

	/* touch all the files so stat times are different */
	{
		git_buf path = GIT_BUF_INIT;
		cl_git_pass(git_buf_sets(&path, "status"));
		cl_git_pass(git_path_direach(&path, 0, touch_file, NULL));
		git_buf_dispose(&path);
	}

	opts.flags |= GIT_DIFF_INCLUDE_IGNORED | GIT_DIFF_INCLUDE_UNTRACKED;

	basic_diff_status(&diff, &opts);

	cl_git_pass(git_diff_get_perfdata(&perf, diff));
	cl_assert_equal_sz(13 + 3, perf.stat_calls);
	cl_assert_equal_sz(5, perf.oid_calculations);

	git_diff_free(diff);

	/* now allow diff to update stat cache */
	opts.flags |= GIT_DIFF_UPDATE_INDEX;

	/* advance a tick for the index so we don't re-calculate racily-clean entries */
	cl_git_pass(git_repository_index__weakptr(&index, g_repo));
	tick_index(index);

	basic_diff_status(&diff, &opts);

	cl_git_pass(git_diff_get_perfdata(&perf, diff));
	cl_assert_equal_sz(13 + 3, perf.stat_calls);
	cl_assert_equal_sz(5, perf.oid_calculations);

	git_diff_free(diff);

	/* now if we do it again, we should see fewer OID calculations */

	/* tick again as the index updating from the previous diff might have reset the timestamp */
	tick_index(index);
	basic_diff_status(&diff, &opts);

	cl_git_pass(git_diff_get_perfdata(&perf, diff));
	cl_assert_equal_sz(13 + 3, perf.stat_calls);
	cl_assert_equal_sz(0, perf.oid_calculations);

	git_diff_free(diff);
}