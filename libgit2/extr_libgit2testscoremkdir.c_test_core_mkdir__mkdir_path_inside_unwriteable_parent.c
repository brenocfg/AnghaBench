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
struct stat {int /*<<< orphan*/  st_mode; } ;
typedef  int /*<<< orphan*/  mode_t ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_MKDIR_PATH ; 
 int /*<<< orphan*/  check_mode (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_is_chmod_supported () ; 
 int /*<<< orphan*/  cl_must_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_set_cleanup (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cleanup_chmod_root ; 
 int /*<<< orphan*/ * git__malloc (int) ; 
 int /*<<< orphan*/  git_futils_mkdir (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_futils_mkdir_relative (char*,char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_path_lstat (char*,struct stat*) ; 
 int /*<<< orphan*/  p_chmod (char*,int) ; 
 int /*<<< orphan*/  p_umask (int) ; 

void test_core_mkdir__mkdir_path_inside_unwriteable_parent(void)
{
	struct stat st;
	mode_t *old;

	/* FAT filesystems don't support exec bit, nor group/world bits */
	if (!cl_is_chmod_supported())
		return;

	cl_assert((old = git__malloc(sizeof(mode_t))) != NULL);
	*old = p_umask(022);
	cl_set_cleanup(cleanup_chmod_root, old);

	cl_git_pass(git_futils_mkdir("r", 0777, 0));
	cl_git_pass(git_futils_mkdir_relative("mode/is/important", "r", 0777, GIT_MKDIR_PATH, NULL));
	cl_git_pass(git_path_lstat("r/mode", &st));
	check_mode(0755, st.st_mode);

	cl_must_pass(p_chmod("r/mode", 0111));
	cl_git_pass(git_path_lstat("r/mode", &st));
	check_mode(0111, st.st_mode);

	cl_git_pass(
		git_futils_mkdir_relative("mode/is/okay/inside", "r", 0777, GIT_MKDIR_PATH, NULL));
	cl_git_pass(git_path_lstat("r/mode/is/okay/inside", &st));
	check_mode(0755, st.st_mode);

	cl_must_pass(p_chmod("r/mode", 0777));
}