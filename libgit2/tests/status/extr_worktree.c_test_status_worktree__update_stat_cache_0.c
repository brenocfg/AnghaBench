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
struct TYPE_7__ {int /*<<< orphan*/  flags; } ;
typedef  TYPE_1__ git_status_options ;
typedef  int /*<<< orphan*/  git_status_list ;
typedef  int /*<<< orphan*/  git_repository ;
typedef  int /*<<< orphan*/  git_index ;
struct TYPE_8__ {int /*<<< orphan*/  oid_calculations; int /*<<< orphan*/  stat_calls; } ;
typedef  TYPE_2__ git_diff_perfdata ;

/* Variables and functions */
 TYPE_2__ GIT_DIFF_PERFDATA_INIT ; 
 TYPE_1__ GIT_STATUS_OPTIONS_INIT ; 
 int /*<<< orphan*/  GIT_STATUS_OPT_DEFAULTS ; 
 int /*<<< orphan*/  GIT_STATUS_OPT_UPDATE_INDEX ; 
 int /*<<< orphan*/  check_status0 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cl_assert_equal_sz (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * cl_git_sandbox_init (char*) ; 
 int /*<<< orphan*/  git_repository_index__weakptr (int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_status_list_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_status_list_get_perfdata (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_status_list_new (int /*<<< orphan*/ **,int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  tick_index (int /*<<< orphan*/ *) ; 

void test_status_worktree__update_stat_cache_0(void)
{
	git_repository *repo = cl_git_sandbox_init("status");
	git_status_options opts = GIT_STATUS_OPTIONS_INIT;
	git_status_list *status;
	git_diff_perfdata perf = GIT_DIFF_PERFDATA_INIT;
	git_index *index;

	opts.flags = GIT_STATUS_OPT_DEFAULTS;

	cl_git_pass(git_status_list_new(&status, repo, &opts));
	check_status0(status);
	cl_git_pass(git_status_list_get_perfdata(&perf, status));
	cl_assert_equal_sz(13 + 3, perf.stat_calls);
	cl_assert_equal_sz(5, perf.oid_calculations);

	git_status_list_free(status);

	/* tick the index so we avoid recalculating racily-clean entries */
	cl_git_pass(git_repository_index__weakptr(&index, repo));
	tick_index(index);

	opts.flags |= GIT_STATUS_OPT_UPDATE_INDEX;

	cl_git_pass(git_status_list_new(&status, repo, &opts));
	check_status0(status);
	cl_git_pass(git_status_list_get_perfdata(&perf, status));
	cl_assert_equal_sz(13 + 3, perf.stat_calls);
	cl_assert_equal_sz(5, perf.oid_calculations);

	git_status_list_free(status);

	opts.flags &= ~GIT_STATUS_OPT_UPDATE_INDEX;

	/* tick again as the index updating from the previous diff might have reset the timestamp */
	tick_index(index);
	cl_git_pass(git_status_list_new(&status, repo, &opts));
	check_status0(status);
	cl_git_pass(git_status_list_get_perfdata(&perf, status));
	cl_assert_equal_sz(13 + 3, perf.stat_calls);
	cl_assert_equal_sz(0, perf.oid_calculations);

	git_status_list_free(status);
}