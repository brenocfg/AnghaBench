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
 int GIT_MKDIR_CHMOD ; 
 int GIT_MKDIR_CHMOD_PATH ; 
 int GIT_MKDIR_PATH ; 
 int /*<<< orphan*/  check_mode (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_set_cleanup (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cleanup_chmod_root ; 
 int /*<<< orphan*/ * git__malloc (int) ; 
 int /*<<< orphan*/  git_futils_mkdir (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_futils_mkdir_relative (char*,char*,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_path_lstat (char*,struct stat*) ; 
 int /*<<< orphan*/  p_umask (int) ; 

void test_core_mkdir__chmods(void)
{
	struct stat st;
	mode_t *old = git__malloc(sizeof(mode_t));
	*old = p_umask(022);

	cl_set_cleanup(cleanup_chmod_root, old);

	cl_git_pass(git_futils_mkdir("r", 0777, 0));

	cl_git_pass(git_futils_mkdir_relative("mode/is/important", "r", 0777, GIT_MKDIR_PATH, NULL));

	cl_git_pass(git_path_lstat("r/mode", &st));
	check_mode(0755, st.st_mode);
	cl_git_pass(git_path_lstat("r/mode/is", &st));
	check_mode(0755, st.st_mode);
	cl_git_pass(git_path_lstat("r/mode/is/important", &st));
	check_mode(0755, st.st_mode);

	cl_git_pass(git_futils_mkdir_relative("mode2/is2/important2", "r", 0777, GIT_MKDIR_PATH | GIT_MKDIR_CHMOD, NULL));

	cl_git_pass(git_path_lstat("r/mode2", &st));
	check_mode(0755, st.st_mode);
	cl_git_pass(git_path_lstat("r/mode2/is2", &st));
	check_mode(0755, st.st_mode);
	cl_git_pass(git_path_lstat("r/mode2/is2/important2", &st));
	check_mode(0777, st.st_mode);

	cl_git_pass(git_futils_mkdir_relative("mode3/is3/important3", "r", 0777, GIT_MKDIR_PATH | GIT_MKDIR_CHMOD_PATH, NULL));

	cl_git_pass(git_path_lstat("r/mode3", &st));
	check_mode(0777, st.st_mode);
	cl_git_pass(git_path_lstat("r/mode3/is3", &st));
	check_mode(0777, st.st_mode);
	cl_git_pass(git_path_lstat("r/mode3/is3/important3", &st));
	check_mode(0777, st.st_mode);

	/* test that we chmod existing dir */

	cl_git_pass(git_futils_mkdir_relative("mode/is/important", "r", 0777, GIT_MKDIR_PATH | GIT_MKDIR_CHMOD, NULL));

	cl_git_pass(git_path_lstat("r/mode", &st));
	check_mode(0755, st.st_mode);
	cl_git_pass(git_path_lstat("r/mode/is", &st));
	check_mode(0755, st.st_mode);
	cl_git_pass(git_path_lstat("r/mode/is/important", &st));
	check_mode(0777, st.st_mode);

	/* test that we chmod even existing dirs if CHMOD_PATH is set */

	cl_git_pass(git_futils_mkdir_relative("mode2/is2/important2.1", "r", 0777, GIT_MKDIR_PATH | GIT_MKDIR_CHMOD_PATH, NULL));

	cl_git_pass(git_path_lstat("r/mode2", &st));
	check_mode(0777, st.st_mode);
	cl_git_pass(git_path_lstat("r/mode2/is2", &st));
	check_mode(0777, st.st_mode);
	cl_git_pass(git_path_lstat("r/mode2/is2/important2.1", &st));
	check_mode(0777, st.st_mode);
}