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
typedef  int /*<<< orphan*/  git_buf ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_RMDIR_REMOVE_FILES ; 
 int /*<<< orphan*/  GIT_UNUSED (void*) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 scalar_t__ git__suffixcmp (char const*,char*) ; 
 char* git_buf_cstr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_futils_rmdir_r (char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ git_path_isdir (char const*) ; 
 int /*<<< orphan*/  p_unlink (char*) ; 

__attribute__((used)) static int remove_file_cb(void *data, git_buf *file)
{
	const char *filename = git_buf_cstr(file);

	GIT_UNUSED(data);

	if (git__suffixcmp(filename, ".git") == 0)
		return 0;

	if (git_path_isdir(filename))
		cl_git_pass(git_futils_rmdir_r(filename, NULL, GIT_RMDIR_REMOVE_FILES));
	else
		cl_git_pass(p_unlink(git_buf_cstr(file)));

	return 0;
}