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
typedef  int /*<<< orphan*/  git_index ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_FILEMODE_BLOB ; 
 int /*<<< orphan*/  GIT_FILEMODE_BLOB_EXECUTABLE ; 
 int /*<<< orphan*/  add_entry_and_check_mode (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_repo_set_bool (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  g_repo ; 
 int /*<<< orphan*/  git_index_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_repository_index (int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 

void test_index_filemodes__explicit(void)
{
	git_index *index;

	/* These tests should run and work everywhere, as the filemode is
	 * given explicitly to git_index_add or git_index_add_from_buffer
	 */
	cl_repo_set_bool(g_repo, "core.filemode", false);

	cl_git_pass(git_repository_index(&index, g_repo));

	/* Each of these tests keeps overwriting the same file in the index. */
	/* 1 - add new 0644 entry  */
	add_entry_and_check_mode(index, true, GIT_FILEMODE_BLOB);

	/* 2 - add 0755 entry over existing 0644 */
	add_entry_and_check_mode(index, true, GIT_FILEMODE_BLOB_EXECUTABLE);

	/* 3 - add 0644 entry over existing 0755 */
	add_entry_and_check_mode(index, true, GIT_FILEMODE_BLOB);

	/* 4 - add 0755 buffer entry over existing 0644  */
	add_entry_and_check_mode(index, false, GIT_FILEMODE_BLOB_EXECUTABLE);

	/* 5 - add 0644 buffer entry over existing 0755 */
	add_entry_and_check_mode(index, false, GIT_FILEMODE_BLOB);

	git_index_free(index);
}