#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct status_entry {int member_0; char* member_1; char* member_2; } ;
struct TYPE_4__ {int /*<<< orphan*/  flags; } ;
typedef  TYPE_1__ git_status_options ;
typedef  int /*<<< orphan*/  git_status_list ;

/* Variables and functions */
 TYPE_1__ GIT_STATUS_OPTIONS_INIT ; 
 int /*<<< orphan*/  GIT_STATUS_OPT_INCLUDE_UNTRACKED ; 
 int /*<<< orphan*/  GIT_STATUS_OPT_RENAMES_INDEX_TO_WORKDIR ; 
 int GIT_STATUS_WT_MODIFIED ; 
 int GIT_STATUS_WT_RENAMED ; 
 int /*<<< orphan*/  check_status (int /*<<< orphan*/ *,struct status_entry*,int) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_repo ; 
 int /*<<< orphan*/  git_status_list_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_status_list_new (int /*<<< orphan*/ **,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  rename_and_edit_file (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  rename_file (int /*<<< orphan*/ ,char*,char*) ; 

void test_status_renames__index2workdir_two(void)
{
	git_status_list *statuslist;
	git_status_options opts = GIT_STATUS_OPTIONS_INIT;
	struct status_entry expected[] = {
		{ GIT_STATUS_WT_RENAMED | GIT_STATUS_WT_MODIFIED,
		  "sixserving.txt", "aaa.txt" },
		{ GIT_STATUS_WT_RENAMED | GIT_STATUS_WT_MODIFIED,
		  "untimely.txt", "bbb.txt" },
		{ GIT_STATUS_WT_RENAMED, "songof7cities.txt", "ccc.txt" },
		{ GIT_STATUS_WT_RENAMED, "ikeepsix.txt", "ddd.txt" },
	};

	opts.flags |= GIT_STATUS_OPT_INCLUDE_UNTRACKED;
	opts.flags |= GIT_STATUS_OPT_RENAMES_INDEX_TO_WORKDIR;

	rename_file(g_repo, "ikeepsix.txt", "ddd.txt");
	rename_and_edit_file(g_repo, "sixserving.txt", "aaa.txt");
	rename_file(g_repo, "songof7cities.txt", "ccc.txt");
	rename_and_edit_file(g_repo, "untimely.txt", "bbb.txt");

	cl_git_pass(git_status_list_new(&statuslist, g_repo, &opts));
	check_status(statuslist, expected, 4);
	git_status_list_free(statuslist);
}