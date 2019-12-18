#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int flags; } ;
typedef  TYPE_3__ git_status_options ;
typedef  int /*<<< orphan*/  git_status_list ;
struct TYPE_11__ {int /*<<< orphan*/  status; TYPE_2__* head_to_index; } ;
typedef  TYPE_4__ git_status_entry ;
struct TYPE_8__ {int /*<<< orphan*/  path; } ;
struct TYPE_9__ {TYPE_1__ old_file; } ;

/* Variables and functions */
 TYPE_3__ GIT_STATUS_OPTIONS_INIT ; 
 int GIT_STATUS_OPT_INCLUDE_IGNORED ; 
 int GIT_STATUS_OPT_INCLUDE_UNMODIFIED ; 
 int GIT_STATUS_OPT_INCLUDE_UNREADABLE ; 
 int GIT_STATUS_OPT_INCLUDE_UNREADABLE_AS_UNTRACKED ; 
 int GIT_STATUS_OPT_INCLUDE_UNTRACKED ; 
 int GIT_STATUS_OPT_RECURSE_IGNORED_DIRS ; 
 int GIT_STATUS_OPT_RECURSE_UNTRACKED_DIRS ; 
 int GIT_STATUS_OPT_RENAMES_FROM_REWRITES ; 
 int GIT_STATUS_OPT_RENAMES_HEAD_TO_INDEX ; 
 int GIT_STATUS_OPT_RENAMES_INDEX_TO_WORKDIR ; 
 int /*<<< orphan*/  cl_assert_equal_i (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_repo ; 
 TYPE_4__* git_status_byindex (int /*<<< orphan*/ *,size_t) ; 
 size_t git_status_list_entrycount (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_status_list_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_status_list_new (int /*<<< orphan*/ **,int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  setup_fixture_submod3 () ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 

void test_status_submodules__mixed_case(void)
{
	git_status_list *status;
	git_status_options status_opts = GIT_STATUS_OPTIONS_INIT;
	const git_status_entry *s;
	size_t i;

	status_opts.flags =
		GIT_STATUS_OPT_INCLUDE_UNTRACKED |
		GIT_STATUS_OPT_INCLUDE_IGNORED |
		GIT_STATUS_OPT_INCLUDE_UNMODIFIED |
		GIT_STATUS_OPT_RECURSE_UNTRACKED_DIRS |
		GIT_STATUS_OPT_RECURSE_IGNORED_DIRS |
		GIT_STATUS_OPT_RENAMES_HEAD_TO_INDEX |
		GIT_STATUS_OPT_RENAMES_INDEX_TO_WORKDIR |
		GIT_STATUS_OPT_RENAMES_FROM_REWRITES |
		GIT_STATUS_OPT_INCLUDE_UNREADABLE |
		GIT_STATUS_OPT_INCLUDE_UNREADABLE_AS_UNTRACKED;

    g_repo = setup_fixture_submod3();

	cl_git_pass(git_status_list_new(&status, g_repo, &status_opts));

	for (i = 0; i < git_status_list_entrycount(status); i++) {
		s = git_status_byindex(status, i);

		if (s->head_to_index &&
			strcmp(s->head_to_index->old_file.path, ".gitmodules") == 0)
			continue;

		cl_assert_equal_i(0, s->status);
	}

	git_status_list_free(status);
}