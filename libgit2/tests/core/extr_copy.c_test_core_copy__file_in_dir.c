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
struct stat {scalar_t__ st_size; int /*<<< orphan*/  st_mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_MKDIR_PATH ; 
 int /*<<< orphan*/  GIT_RMDIR_REMOVE_FILES ; 
 int S_ISREG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_assert (int) ; 
 int /*<<< orphan*/  cl_git_mkfile (char*,char const*) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_futils_cp (char*,char*,int) ; 
 int /*<<< orphan*/  git_futils_mkdir (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_futils_mkpath2file (char*,int) ; 
 int /*<<< orphan*/  git_futils_rmdir_r (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int git_path_isdir (char*) ; 
 int /*<<< orphan*/  git_path_lstat (char*,struct stat*) ; 
 size_t strlen (char const*) ; 

void test_core_copy__file_in_dir(void)
{
	struct stat st;
	const char *content = "This is some other stuff to copy\n";

	cl_git_pass(git_futils_mkdir("an_dir/in_a_dir", 0775, GIT_MKDIR_PATH));
	cl_git_mkfile("an_dir/in_a_dir/copy_me", content);
	cl_assert(git_path_isdir("an_dir"));

	cl_git_pass(git_futils_mkpath2file
		("an_dir/second_dir/and_more/copy_me_two", 0775));

	cl_git_pass(git_futils_cp
		("an_dir/in_a_dir/copy_me",
		 "an_dir/second_dir/and_more/copy_me_two",
		 0664));

	cl_git_pass(git_path_lstat("an_dir/second_dir/and_more/copy_me_two", &st));
	cl_assert(S_ISREG(st.st_mode));
	cl_assert(strlen(content) == (size_t)st.st_size);

	cl_git_pass(git_futils_rmdir_r("an_dir", NULL, GIT_RMDIR_REMOVE_FILES));
	cl_assert(!git_path_isdir("an_dir"));
}