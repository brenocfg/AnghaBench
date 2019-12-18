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

void test_ignore_path__gitignore_in_subdir(void)
{
	cl_git_rmfile("attr/.gitignore");

	cl_must_pass(p_mkdir("attr/dir1", 0777));
	cl_must_pass(p_mkdir("attr/dir1/dir2", 0777));
	cl_must_pass(p_mkdir("attr/dir1/dir2/dir3", 0777));

	cl_git_mkfile("attr/dir1/dir2/dir3/.gitignore", "dir1/\ndir1/subdir/");

	assert_is_ignored(false, "dir1/file");
	assert_is_ignored(false, "dir1/dir2/file");
	assert_is_ignored(false, "dir1/dir2/dir3/file");
	assert_is_ignored(true,  "dir1/dir2/dir3/dir1/file");
	assert_is_ignored(true,  "dir1/dir2/dir3/dir1/subdir/foo");

	if (cl_repo_get_bool(g_repo, "core.ignorecase")) {
		cl_git_mkfile("attr/dir1/dir2/dir3/.gitignore", "DiR1/\nDiR1/subdir/\n");

		assert_is_ignored(false, "dir1/file");
		assert_is_ignored(false, "dir1/dir2/file");
		assert_is_ignored(false, "dir1/dir2/dir3/file");
		assert_is_ignored(true,  "dir1/dir2/dir3/dir1/file");
		assert_is_ignored(true,  "dir1/dir2/dir3/dir1/subdir/foo");
	}
}