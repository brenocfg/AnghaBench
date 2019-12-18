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
 int /*<<< orphan*/  cl_assert (int) ; 
 int /*<<< orphan*/  cl_git_mkfile (char*,char*) ; 
 int /*<<< orphan*/  git_path_exists (char*) ; 
 int /*<<< orphan*/  p_mkdir (char*,int) ; 
 int /*<<< orphan*/  p_unlink (char*) ; 

void test_ignore_path__subdirectory_gitignore(void)
{
	p_unlink("attr/.gitignore");
	cl_assert(!git_path_exists("attr/.gitignore"));
	cl_git_mkfile(
		"attr/.gitignore",
		"file1\n");
	p_mkdir("attr/dir", 0777);
	cl_git_mkfile(
		"attr/dir/.gitignore",
		"file2/\n");

	assert_is_ignored(true, "file1");
	assert_is_ignored(true, "dir/file1");
	assert_is_ignored(true, "dir/file2/actual_file");  /* in ignored dir */
	assert_is_ignored(false, "dir/file3");
}