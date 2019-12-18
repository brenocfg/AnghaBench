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
 int /*<<< orphan*/  cl_git_rewritefile (char*,char*) ; 
 int /*<<< orphan*/  git_path_exists (char*) ; 
 int /*<<< orphan*/  p_mkdir (char*,int) ; 
 int /*<<< orphan*/  p_unlink (char*) ; 

void test_ignore_path__skip_gitignore_directory(void)
{
	cl_git_rewritefile("attr/.git/info/exclude", "/NewFolder\n/NewFolder/NewFolder");
	p_unlink("attr/.gitignore");
	cl_assert(!git_path_exists("attr/.gitignore"));
	p_mkdir("attr/.gitignore", 0777);
	cl_git_mkfile("attr/.gitignore/garbage.txt", "new_file\n");

	assert_is_ignored(false, "File.txt");
	assert_is_ignored(true, "NewFolder");
	assert_is_ignored(true, "NewFolder/NewFolder");
	assert_is_ignored(true, "NewFolder/NewFolder/File.txt");
}