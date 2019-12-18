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
typedef  int /*<<< orphan*/  git_filebuf ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_FILEBUF_INIT ; 
 int /*<<< orphan*/  GIT_RMDIR_REMOVE_FILES ; 
 int /*<<< orphan*/  cl_git_fail (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_skip () ; 
 int /*<<< orphan*/  clar_sandbox_path () ; 
 int /*<<< orphan*/  git_filebuf_open (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  git_futils_rmdir_r (char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_path_supports_symlinks (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  p_mkdir (char const*,int) ; 
 int /*<<< orphan*/  p_symlink (char*,char const*) ; 

void test_core_filebuf__symlink_depth(void)
{
	git_filebuf file = GIT_FILEBUF_INIT;
	const char *dir = "linkdir", *source = "linkdir/link";

	if (!git_path_supports_symlinks(clar_sandbox_path()))
		cl_skip();

	cl_git_pass(p_mkdir(dir, 0777));
	/* Endless loop */
	cl_git_pass(p_symlink("link", source));

	cl_git_fail(git_filebuf_open(&file, source, 0, 0666));

	cl_git_pass(git_futils_rmdir_r(dir, NULL, GIT_RMDIR_REMOVE_FILES));
}