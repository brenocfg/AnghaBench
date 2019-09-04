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
struct TYPE_4__ {scalar_t__ status; int /*<<< orphan*/  count; } ;
typedef  TYPE_1__ status_entry_single ;
typedef  int /*<<< orphan*/  result ;
typedef  int /*<<< orphan*/  git_repository ;
typedef  int /*<<< orphan*/  git_index ;

/* Variables and functions */
 scalar_t__ GIT_STATUS_INDEX_NEW ; 
 scalar_t__ GIT_STATUS_WT_NEW ; 
 int /*<<< orphan*/  cb_status__single ; 
 int /*<<< orphan*/  cl_assert (int) ; 
 int /*<<< orphan*/  cl_assert_equal_i (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_mkfile (char*,char*) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_set_cleanup (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  cleanup_new_repo ; 
 int /*<<< orphan*/  git_index_add_bypath (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  git_index_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_index_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_repository_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_repository_index (int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_repository_init (int /*<<< orphan*/ **,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_status_foreach (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

void test_status_worktree_init__first_commit_in_progress(void)
{
	git_repository *repo;
	git_index *index;
	status_entry_single result;

	cl_set_cleanup(&cleanup_new_repo, "getting_started");

	cl_git_pass(git_repository_init(&repo, "getting_started", 0));
	cl_git_mkfile("getting_started/testfile.txt", "content\n");

	memset(&result, 0, sizeof(result));
	cl_git_pass(git_status_foreach(repo, cb_status__single, &result));
	cl_assert_equal_i(1, result.count);
	cl_assert(result.status == GIT_STATUS_WT_NEW);

	cl_git_pass(git_repository_index(&index, repo));
	cl_git_pass(git_index_add_bypath(index, "testfile.txt"));
	cl_git_pass(git_index_write(index));

	memset(&result, 0, sizeof(result));
	cl_git_pass(git_status_foreach(repo, cb_status__single, &result));
	cl_assert_equal_i(1, result.count);
	cl_assert(result.status == GIT_STATUS_INDEX_NEW);

	git_index_free(index);
	git_repository_free(repo);
}