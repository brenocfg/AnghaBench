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
struct TYPE_4__ {unsigned int status; int /*<<< orphan*/  count; } ;
typedef  TYPE_1__ status_entry_single ;
typedef  int /*<<< orphan*/  result ;
typedef  int /*<<< orphan*/  git_repository ;
typedef  int /*<<< orphan*/  git_index ;

/* Variables and functions */
 unsigned int GIT_STATUS_IGNORED ; 
 unsigned int GIT_STATUS_INDEX_NEW ; 
 unsigned int GIT_STATUS_WT_NEW ; 
 int /*<<< orphan*/  cb_status__single ; 
 int /*<<< orphan*/  cl_assert (int) ; 
 int /*<<< orphan*/  cl_assert_equal_i (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_mkfile (char*,char*) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_rewritefile (char*,char*) ; 
 int /*<<< orphan*/  cl_set_cleanup (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  cleanup_new_repo ; 
 int /*<<< orphan*/  git_index_add_bypath (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  git_index_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_index_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_repository_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_repository_index (int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_repository_init (int /*<<< orphan*/ **,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_status_file (unsigned int*,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  git_status_foreach (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

void test_status_worktree_init__space_in_filename(void)
{
	git_repository *repo;
	git_index *index;
	status_entry_single result;
	unsigned int status_flags;

#define FILE_WITH_SPACE "LICENSE - copy.md"

	cl_set_cleanup(&cleanup_new_repo, "with_space");
	cl_git_pass(git_repository_init(&repo, "with_space", 0));
	cl_git_mkfile("with_space/" FILE_WITH_SPACE, "I have a space in my name\n");

	/* file is new to working directory */

	memset(&result, 0, sizeof(result));
	cl_git_pass(git_status_foreach(repo, cb_status__single, &result));
	cl_assert_equal_i(1, result.count);
	cl_assert(result.status == GIT_STATUS_WT_NEW);

	cl_git_pass(git_status_file(&status_flags, repo, FILE_WITH_SPACE));
	cl_assert(status_flags == GIT_STATUS_WT_NEW);

	/* ignore the file */

	cl_git_rewritefile("with_space/.gitignore", "*.md\n.gitignore\n");

	memset(&result, 0, sizeof(result));
	cl_git_pass(git_status_foreach(repo, cb_status__single, &result));
	cl_assert_equal_i(2, result.count);
	cl_assert(result.status == GIT_STATUS_IGNORED);

	cl_git_pass(git_status_file(&status_flags, repo, FILE_WITH_SPACE));
	cl_assert(status_flags == GIT_STATUS_IGNORED);

	/* don't ignore the file */

	cl_git_rewritefile("with_space/.gitignore", ".gitignore\n");

	memset(&result, 0, sizeof(result));
	cl_git_pass(git_status_foreach(repo, cb_status__single, &result));
	cl_assert_equal_i(2, result.count);
	cl_assert(result.status == GIT_STATUS_WT_NEW);

	cl_git_pass(git_status_file(&status_flags, repo, FILE_WITH_SPACE));
	cl_assert(status_flags == GIT_STATUS_WT_NEW);

	/* add the file to the index */

	cl_git_pass(git_repository_index(&index, repo));
	cl_git_pass(git_index_add_bypath(index, FILE_WITH_SPACE));
	cl_git_pass(git_index_write(index));

	memset(&result, 0, sizeof(result));
	cl_git_pass(git_status_foreach(repo, cb_status__single, &result));
	cl_assert_equal_i(2, result.count);
	cl_assert(result.status == GIT_STATUS_INDEX_NEW);

	cl_git_pass(git_status_file(&status_flags, repo, FILE_WITH_SPACE));
	cl_assert(status_flags == GIT_STATUS_INDEX_NEW);

	git_index_free(index);
	git_repository_free(repo);
}