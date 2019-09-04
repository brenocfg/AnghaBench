#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */

/* Variables and functions */

void test_status_renames__precomposed_unicode_toggle_is_rename(void)
{
#ifdef GIT_USE_ICONV
	git_status_list *statuslist;
	git_status_options opts = GIT_STATUS_OPTIONS_INIT;
	struct status_entry expected0[] = {
		{ GIT_STATUS_INDEX_RENAMED, "ikeepsix.txt", nfd },
	};
	struct status_entry expected1[] = {
		{ GIT_STATUS_WT_RENAMED, nfd, nfc },
	};
	struct status_entry expected2[] = {
		{ GIT_STATUS_INDEX_RENAMED, nfd, nfc },
	};
	struct status_entry expected3[] = {
		{ GIT_STATUS_INDEX_RENAMED | GIT_STATUS_WT_RENAMED, nfd, nfd },
	};

	cl_repo_set_bool(g_repo, "core.precomposeunicode", false);
	rename_file(g_repo, "ikeepsix.txt", nfd);

	{
		git_index *index;
		cl_git_pass(git_repository_index(&index, g_repo));
		cl_git_pass(git_index_remove_bypath(index, "ikeepsix.txt"));
		cl_git_pass(git_index_add_bypath(index, nfd));
		cl_git_pass(git_index_write(index));
		git_index_free(index);
	}

	opts.flags |= GIT_STATUS_OPT_INCLUDE_UNTRACKED |
		GIT_STATUS_OPT_RENAMES_HEAD_TO_INDEX |
		GIT_STATUS_OPT_RENAMES_INDEX_TO_WORKDIR;

	cl_git_pass(git_status_list_new(&statuslist, g_repo, &opts));
	check_status(statuslist, expected0, ARRAY_SIZE(expected0));
	git_status_list_free(statuslist);

	cl_repo_commit_from_index(NULL, g_repo, NULL, 0, "commit nfd");

	cl_git_pass(git_status_list_new(&statuslist, g_repo, &opts));
	cl_assert_equal_sz(0, git_status_list_entrycount(statuslist));
	git_status_list_free(statuslist);

	cl_repo_set_bool(g_repo, "core.precomposeunicode", true);

	cl_git_pass(git_status_list_new(&statuslist, g_repo, &opts));
	check_status(statuslist, expected1, ARRAY_SIZE(expected1));
	git_status_list_free(statuslist);

	{
		git_index *index;
		cl_git_pass(git_repository_index(&index, g_repo));
		cl_git_pass(git_index_remove_bypath(index, nfd));
		cl_git_pass(git_index_add_bypath(index, nfc));
		cl_git_pass(git_index_write(index));
		git_index_free(index);
	}

	cl_git_pass(git_status_list_new(&statuslist, g_repo, &opts));
	check_status(statuslist, expected2, ARRAY_SIZE(expected2));
	git_status_list_free(statuslist);

	cl_repo_set_bool(g_repo, "core.precomposeunicode", false);

	cl_git_pass(git_status_list_new(&statuslist, g_repo, &opts));
	check_status(statuslist, expected3, ARRAY_SIZE(expected3));
	git_status_list_free(statuslist);
#endif
}