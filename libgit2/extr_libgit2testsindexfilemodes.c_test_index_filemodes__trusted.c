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
 int GIT_INDEX_CAPABILITY_NO_FILEMODE ; 
 int O_CREAT ; 
 int O_TRUNC ; 
 int O_WRONLY ; 
 int /*<<< orphan*/  add_and_check_mode (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_assert (int) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_write2file (char*,char*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  cl_is_chmod_supported () ; 
 int /*<<< orphan*/  cl_repo_set_bool (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  g_repo ; 
 int git_index_caps (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_index_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_repository_index (int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  replace_file_with_mode (char*,char*,int) ; 

void test_index_filemodes__trusted(void)
{
	git_index *index;

	/* Only run these tests on platforms where I can actually
	 * chmod a file and get the stat results I expect!
	 */
	if (!cl_is_chmod_supported())
		return;

	cl_repo_set_bool(g_repo, "core.filemode", true);

	cl_git_pass(git_repository_index(&index, g_repo));
	cl_assert((git_index_caps(index) & GIT_INDEX_CAPABILITY_NO_FILEMODE) == 0);

	/* 1 - add 0644 over existing 0644 -> expect 0644 */
	replace_file_with_mode("exec_off", "filemodes/exec_off.0", 0644);
	add_and_check_mode(index, "exec_off", GIT_FILEMODE_BLOB);

	/* 2 - add 0644 over existing 0755 -> expect 0644 */
	replace_file_with_mode("exec_on", "filemodes/exec_on.0", 0644);
	add_and_check_mode(index, "exec_on", GIT_FILEMODE_BLOB);

	/* 3 - add 0755 over existing 0644 -> expect 0755 */
	replace_file_with_mode("exec_off", "filemodes/exec_off.1", 0755);
	add_and_check_mode(index, "exec_off", GIT_FILEMODE_BLOB_EXECUTABLE);

	/* 4 - add 0755 over existing 0755 -> expect 0755 */
	replace_file_with_mode("exec_on", "filemodes/exec_on.1", 0755);
	add_and_check_mode(index, "exec_on", GIT_FILEMODE_BLOB_EXECUTABLE);

	/*  5 - add new 0644 -> expect 0644 */
	cl_git_write2file("filemodes/new_off", "blah", 0,
		O_WRONLY | O_CREAT | O_TRUNC, 0644);
	add_and_check_mode(index, "new_off", GIT_FILEMODE_BLOB);

	/* 6 - add 0755 -> expect 0755 */
	cl_git_write2file("filemodes/new_on", "blah", 0,
		O_WRONLY | O_CREAT | O_TRUNC, 0755);
	add_and_check_mode(index, "new_on", GIT_FILEMODE_BLOB_EXECUTABLE);

	git_index_free(index);
}