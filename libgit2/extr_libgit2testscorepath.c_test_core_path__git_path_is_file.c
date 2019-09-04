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
 int /*<<< orphan*/  GIT_PATH_FS_HFS ; 
 int GIT_PATH_GITFILE_GITATTRIBUTES ; 
 int GIT_PATH_GITFILE_GITIGNORE ; 
 int GIT_PATH_GITFILE_GITMODULES ; 
 int /*<<< orphan*/  cl_git_fail (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_path_is_gitfile (char*,int,int,int /*<<< orphan*/ ) ; 

void test_core_path__git_path_is_file(void)
{
	cl_git_fail(git_path_is_gitfile("blob", 4, -1, GIT_PATH_FS_HFS));
	cl_git_pass(git_path_is_gitfile("blob", 4, GIT_PATH_GITFILE_GITIGNORE, GIT_PATH_FS_HFS));
	cl_git_pass(git_path_is_gitfile("blob", 4, GIT_PATH_GITFILE_GITMODULES, GIT_PATH_FS_HFS));
	cl_git_pass(git_path_is_gitfile("blob", 4, GIT_PATH_GITFILE_GITATTRIBUTES, GIT_PATH_FS_HFS));
	cl_git_fail(git_path_is_gitfile("blob", 4, 3, GIT_PATH_FS_HFS));
}