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
 int GIT_ENOTFOUND ; 
 int GIT_RMDIR_REMOVE_BLOCKERS ; 
 int GIT_RMDIR_REMOVE_FILES ; 
 int /*<<< orphan*/  cl_assert (int) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_rewritefile (char const*,char*) ; 
 int /*<<< orphan*/  git_futils_mkpath2file (char const*,int) ; 
 int git_futils_rmdir_r (char const*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void force_create_file(const char *file)
{
	int error = git_futils_rmdir_r(file, NULL,
		GIT_RMDIR_REMOVE_FILES | GIT_RMDIR_REMOVE_BLOCKERS);
	cl_assert(!error || error == GIT_ENOTFOUND);
	cl_git_pass(git_futils_mkpath2file(file, 0777));
	cl_git_rewritefile(file, "yowza!!");
}