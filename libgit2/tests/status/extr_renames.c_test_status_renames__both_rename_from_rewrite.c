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
typedef  int /*<<< orphan*/  git_index ;

/* Variables and functions */
 int GIT_STATUS_INDEX_RENAMED ; 
 TYPE_1__ GIT_STATUS_OPTIONS_INIT ; 
 int /*<<< orphan*/  GIT_STATUS_OPT_INCLUDE_UNTRACKED ; 
 int /*<<< orphan*/  GIT_STATUS_OPT_RENAMES_FROM_REWRITES ; 
 int /*<<< orphan*/  GIT_STATUS_OPT_RENAMES_HEAD_TO_INDEX ; 
 int /*<<< orphan*/  GIT_STATUS_OPT_RENAMES_INDEX_TO_WORKDIR ; 
 int GIT_STATUS_WT_RENAMED ; 
 int /*<<< orphan*/  check_status (int /*<<< orphan*/ *,struct status_entry*,int) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_repo ; 
 int /*<<< orphan*/  git_index_add_bypath (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  git_index_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_index_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_repository_index (int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_status_list_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_status_list_new (int /*<<< orphan*/ **,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  rename_file (int /*<<< orphan*/ ,char*,char*) ; 

void test_status_renames__both_rename_from_rewrite(void)
{
	git_index *index;
	git_status_list *statuslist;
	git_status_options opts = GIT_STATUS_OPTIONS_INIT;
	struct status_entry expected[] = {
		{ GIT_STATUS_INDEX_RENAMED | GIT_STATUS_WT_RENAMED,
		  "songof7cities.txt", "ikeepsix.txt" },
		{ GIT_STATUS_INDEX_RENAMED | GIT_STATUS_WT_RENAMED,
		  "ikeepsix.txt", "sixserving.txt" },
		{ GIT_STATUS_INDEX_RENAMED | GIT_STATUS_WT_RENAMED,
		  "sixserving.txt", "songof7cities.txt" },
	};

	opts.flags |= GIT_STATUS_OPT_INCLUDE_UNTRACKED;
	opts.flags |= GIT_STATUS_OPT_RENAMES_HEAD_TO_INDEX;
	opts.flags |= GIT_STATUS_OPT_RENAMES_INDEX_TO_WORKDIR;
	opts.flags |= GIT_STATUS_OPT_RENAMES_FROM_REWRITES;

	cl_git_pass(git_repository_index(&index, g_repo));

	rename_file(g_repo, "ikeepsix.txt", "_temp_.txt");
	rename_file(g_repo, "sixserving.txt", "ikeepsix.txt");
	rename_file(g_repo, "songof7cities.txt", "sixserving.txt");
	rename_file(g_repo, "_temp_.txt", "songof7cities.txt");

	cl_git_pass(git_index_add_bypath(index, "ikeepsix.txt"));
	cl_git_pass(git_index_add_bypath(index, "sixserving.txt"));
	cl_git_pass(git_index_add_bypath(index, "songof7cities.txt"));
	cl_git_pass(git_index_write(index));

	rename_file(g_repo, "songof7cities.txt", "_temp_.txt");
	rename_file(g_repo, "ikeepsix.txt", "songof7cities.txt");
	rename_file(g_repo, "sixserving.txt", "ikeepsix.txt");
	rename_file(g_repo, "_temp_.txt", "sixserving.txt");

	cl_git_pass(git_status_list_new(&statuslist, g_repo, &opts));
	check_status(statuslist, expected, 3);
	git_status_list_free(statuslist);

	git_index_free(index);
}