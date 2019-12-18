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
struct status_entry {char* member_1; char* member_2; int /*<<< orphan*/  member_0; } ;
struct TYPE_4__ {int /*<<< orphan*/  flags; } ;
typedef  TYPE_1__ git_status_options ;
typedef  int /*<<< orphan*/  git_status_list ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (struct status_entry*) ; 
 TYPE_1__ GIT_STATUS_OPTIONS_INIT ; 
 int /*<<< orphan*/  GIT_STATUS_OPT_INCLUDE_UNTRACKED ; 
 int /*<<< orphan*/  GIT_STATUS_OPT_RENAMES_INDEX_TO_WORKDIR ; 
 int /*<<< orphan*/  GIT_STATUS_WT_DELETED ; 
 int /*<<< orphan*/  GIT_STATUS_WT_NEW ; 
 int /*<<< orphan*/  GIT_STATUS_WT_RENAMED ; 
 int /*<<< orphan*/  check_status (int /*<<< orphan*/ *,struct status_entry*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_repo_set_bool (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  g_repo ; 
 int /*<<< orphan*/  git_status_list_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_status_list_new (int /*<<< orphan*/ **,int /*<<< orphan*/ ,TYPE_1__*) ; 
 char* nfc ; 
 char* nfd ; 
 int /*<<< orphan*/  rename_file (int /*<<< orphan*/ ,char*,char*) ; 

void test_status_renames__precomposed_unicode_rename(void)
{
#ifdef GIT_USE_ICONV
	git_status_list *statuslist;
	git_status_options opts = GIT_STATUS_OPTIONS_INIT;
	struct status_entry expected0[] = {
		{ GIT_STATUS_WT_NEW, nfd, NULL },
		{ GIT_STATUS_WT_DELETED, "sixserving.txt", NULL },
	};
	struct status_entry expected1[] = {
		{ GIT_STATUS_WT_RENAMED, "sixserving.txt", nfd },
	};
	struct status_entry expected2[] = {
		{ GIT_STATUS_WT_DELETED, "sixserving.txt", NULL },
		{ GIT_STATUS_WT_NEW, nfc, NULL },
	};
	struct status_entry expected3[] = {
		{ GIT_STATUS_WT_RENAMED, "sixserving.txt", nfc },
	};

	rename_file(g_repo, "sixserving.txt", nfd);

	opts.flags |= GIT_STATUS_OPT_INCLUDE_UNTRACKED;

	cl_repo_set_bool(g_repo, "core.precomposeunicode", false);

	cl_git_pass(git_status_list_new(&statuslist, g_repo, &opts));
	check_status(statuslist, expected0, ARRAY_SIZE(expected0));
	git_status_list_free(statuslist);

	opts.flags |= GIT_STATUS_OPT_RENAMES_INDEX_TO_WORKDIR;

	cl_git_pass(git_status_list_new(&statuslist, g_repo, &opts));
	check_status(statuslist, expected1, ARRAY_SIZE(expected1));
	git_status_list_free(statuslist);

	cl_repo_set_bool(g_repo, "core.precomposeunicode", true);

	opts.flags &= ~GIT_STATUS_OPT_RENAMES_INDEX_TO_WORKDIR;

	cl_git_pass(git_status_list_new(&statuslist, g_repo, &opts));
	check_status(statuslist, expected2, ARRAY_SIZE(expected2));
	git_status_list_free(statuslist);

	opts.flags |= GIT_STATUS_OPT_RENAMES_INDEX_TO_WORKDIR;

	cl_git_pass(git_status_list_new(&statuslist, g_repo, &opts));
	check_status(statuslist, expected3, ARRAY_SIZE(expected3));
	git_status_list_free(statuslist);
#endif
}