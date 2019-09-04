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
struct TYPE_7__ {int expected_entry_count; char const** expected_paths; unsigned int const* expected_statuses; int /*<<< orphan*/  wrong_sorted_path; int /*<<< orphan*/  wrong_status_flags_count; int /*<<< orphan*/  entry_count; } ;
typedef  TYPE_1__ status_entry_counts ;
typedef  int /*<<< orphan*/  git_status_show_t ;
struct TYPE_8__ {unsigned int flags; int /*<<< orphan*/  show; } ;
typedef  TYPE_2__ git_status_options ;
typedef  int /*<<< orphan*/  git_repository ;

/* Variables and functions */
 TYPE_2__ GIT_STATUS_OPTIONS_INIT ; 
 unsigned int GIT_STATUS_OPT_DEFAULTS ; 
 int /*<<< orphan*/  cb_status__normal ; 
 int /*<<< orphan*/  cl_assert_equal_i (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_status_foreach_ext (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int,int) ; 

void assert_show(
	const int entry_counts,
	const char *entry_paths[],
	const unsigned int entry_statuses[],
	git_repository *repo,
	git_status_show_t show,
	unsigned int extra_flags)
{
	status_entry_counts counts;
	git_status_options opts = GIT_STATUS_OPTIONS_INIT;

	memset(&counts, 0x0, sizeof(status_entry_counts));
	counts.expected_entry_count = entry_counts;
	counts.expected_paths = entry_paths;
	counts.expected_statuses = entry_statuses;

	opts.flags = GIT_STATUS_OPT_DEFAULTS | extra_flags;
	opts.show = show;

	cl_git_pass(
		git_status_foreach_ext(repo, &opts, cb_status__normal, &counts)
	);

	cl_assert_equal_i(counts.expected_entry_count, counts.entry_count);
	cl_assert_equal_i(0, counts.wrong_status_flags_count);
	cl_assert_equal_i(0, counts.wrong_sorted_path);
}