#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_7__ ;
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {char** strings; int count; } ;
struct TYPE_16__ {int flags; int /*<<< orphan*/  show; TYPE_1__ pathspec; } ;
typedef  TYPE_6__ git_status_options ;
typedef  int /*<<< orphan*/  git_status_list ;
struct TYPE_17__ {size_t status; TYPE_5__* index_to_workdir; TYPE_3__* head_to_index; } ;
typedef  TYPE_7__ git_status_entry ;
typedef  int /*<<< orphan*/  git_repository ;
typedef  int /*<<< orphan*/  git_index ;
struct TYPE_14__ {int /*<<< orphan*/  path; } ;
struct TYPE_15__ {TYPE_4__ old_file; } ;
struct TYPE_12__ {int /*<<< orphan*/  path; } ;
struct TYPE_13__ {TYPE_2__ old_file; } ;

/* Variables and functions */
 int GIT_INDEX_CAPABILITY_IGNORE_CASE ; 
 TYPE_6__ GIT_STATUS_OPTIONS_INIT ; 
 int GIT_STATUS_OPT_DEFAULTS ; 
 int GIT_STATUS_OPT_DISABLE_PATHSPEC_MATCH ; 
 int GIT_STATUS_OPT_INCLUDE_UNMODIFIED ; 
 int /*<<< orphan*/  GIT_STATUS_SHOW_INDEX_AND_WORKDIR ; 
 int /*<<< orphan*/  GIT_STATUS_SHOW_INDEX_ONLY ; 
 int /*<<< orphan*/  GIT_STATUS_SHOW_WORKDIR_ONLY ; 
 int /*<<< orphan*/  cl_assert_equal_i (int,size_t) ; 
 int /*<<< orphan*/  cl_assert_equal_s (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * cl_git_sandbox_init (char*) ; 
 int git_index_caps (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_index_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_repository_index (int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 TYPE_7__* git_status_byindex (int /*<<< orphan*/ *,size_t) ; 
 size_t git_status_list_entrycount (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_status_list_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_status_list_new (int /*<<< orphan*/ **,int /*<<< orphan*/ *,TYPE_6__*) ; 
 int /*<<< orphan*/ * testrepo2_subdir_paths ; 
 int /*<<< orphan*/ * testrepo2_subdir_paths_icase ; 

void test_status_worktree__with_directory_in_pathlist(void)
{
	git_repository *repo = cl_git_sandbox_init("testrepo2");
	git_index *index;
	git_status_options opts = GIT_STATUS_OPTIONS_INIT;
	git_status_list *statuslist;
	const git_status_entry *status;
	size_t i, entrycount;
	bool native_ignore_case;
	char *subdir_path = "subdir";

	cl_git_pass(git_repository_index(&index, repo));
	native_ignore_case =
			(git_index_caps(index) & GIT_INDEX_CAPABILITY_IGNORE_CASE) != 0;
	git_index_free(index);

	opts.pathspec.strings = &subdir_path;
	opts.pathspec.count = 1;
	opts.flags =
			GIT_STATUS_OPT_DEFAULTS |
			GIT_STATUS_OPT_INCLUDE_UNMODIFIED |
			GIT_STATUS_OPT_DISABLE_PATHSPEC_MATCH;

	opts.show = GIT_STATUS_SHOW_WORKDIR_ONLY;
	git_status_list_new(&statuslist, repo, &opts);

	entrycount = git_status_list_entrycount(statuslist);
	cl_assert_equal_i(4, entrycount);

	for (i = 0; i < entrycount; i++) {
		status = git_status_byindex(statuslist, i);
		cl_assert_equal_i(0, status->status);
		cl_assert_equal_s(native_ignore_case ?
			testrepo2_subdir_paths_icase[i] :
			testrepo2_subdir_paths[i],
			status->index_to_workdir->old_file.path);
	}

	git_status_list_free(statuslist);

	opts.show = GIT_STATUS_SHOW_INDEX_ONLY;
	git_status_list_new(&statuslist, repo, &opts);

	entrycount = git_status_list_entrycount(statuslist);
	cl_assert_equal_i(4, entrycount);

	for (i = 0; i < entrycount; i++) {
		status = git_status_byindex(statuslist, i);
		cl_assert_equal_i(0, status->status);
		cl_assert_equal_s(native_ignore_case ?
			testrepo2_subdir_paths_icase[i] :
			testrepo2_subdir_paths[i],
			status->head_to_index->old_file.path);
	}

	git_status_list_free(statuslist);

	opts.show = GIT_STATUS_SHOW_INDEX_AND_WORKDIR;
	git_status_list_new(&statuslist, repo, &opts);

	entrycount = git_status_list_entrycount(statuslist);
	cl_assert_equal_i(4, entrycount);

	for (i = 0; i < entrycount; i++) {
		status = git_status_byindex(statuslist, i);
		cl_assert_equal_i(0, status->status);
		cl_assert_equal_s(native_ignore_case ?
			testrepo2_subdir_paths_icase[i] :
			testrepo2_subdir_paths[i],
			status->index_to_workdir->old_file.path);
	}

	git_status_list_free(statuslist);
}