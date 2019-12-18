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
 int /*<<< orphan*/  assert_is_ignored (int,char*) ; 
 int /*<<< orphan*/  cl_git_mkfile (char*,char*) ; 
 int /*<<< orphan*/  cl_git_rmfile (char*) ; 
 int /*<<< orphan*/  cl_must_pass (int /*<<< orphan*/ ) ; 
 scalar_t__ cl_repo_get_bool (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  g_repo ; 
 int /*<<< orphan*/  p_mkdir (char*,int) ; 
 int /*<<< orphan*/  p_rmdir (char*) ; 

void test_ignore_path__dont_ignore_files_for_folder(void)
{
	cl_git_rmfile("attr/.gitignore");

	cl_git_mkfile("attr/dir/.gitignore", "test/\n");

	/* Create "test" as a file; ensure it is not ignored. */
	cl_git_mkfile("attr/dir/test", "This is a file.");

	assert_is_ignored(false, "dir/test");
	if (cl_repo_get_bool(g_repo, "core.ignorecase"))
		assert_is_ignored(false, "dir/TeSt");

	/* Create "test" as a directory; ensure it is ignored. */
	cl_git_rmfile("attr/dir/test");
	cl_must_pass(p_mkdir("attr/dir/test", 0777));

	assert_is_ignored(true, "dir/test");
	if (cl_repo_get_bool(g_repo, "core.ignorecase"))
		assert_is_ignored(true, "dir/TeSt");

	/* Remove "test" entirely; ensure it is not ignored.
	 * (As it doesn't exist, it is not a directory.)
	 */
	cl_must_pass(p_rmdir("attr/dir/test"));

	assert_is_ignored(false, "dir/test");
	if (cl_repo_get_bool(g_repo, "core.ignorecase"))
		assert_is_ignored(false, "dir/TeSt");
}