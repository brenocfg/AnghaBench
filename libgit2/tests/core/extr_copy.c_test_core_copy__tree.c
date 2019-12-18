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
struct stat {int /*<<< orphan*/  st_mode; scalar_t__ st_size; } ;

/* Variables and functions */
 int GIT_CPDIR_COPY_DOTFILES ; 
 int GIT_CPDIR_COPY_SYMLINKS ; 
 int GIT_CPDIR_CREATE_EMPTY_DIRS ; 
 int GIT_CPDIR_LINK_FILES ; 
 int /*<<< orphan*/  GIT_MKDIR_PATH ; 
 int /*<<< orphan*/  GIT_RMDIR_REMOVE_FILES ; 
 int S_ISLNK (int /*<<< orphan*/ ) ; 
 int S_ISREG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert_hard_link (char*) ; 
 int /*<<< orphan*/  cl_assert (int) ; 
 int /*<<< orphan*/  cl_git_fail (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_mkfile (char*,char const*) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_futils_cp_r (char*,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_futils_mkdir (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_futils_rmdir_r (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int git_path_isdir (char*) ; 
 int git_path_isfile (char*) ; 
 int /*<<< orphan*/  git_path_lstat (char*,struct stat*) ; 
 scalar_t__ p_symlink (char*,char*) ; 
 size_t strlen (char const*) ; 

void test_core_copy__tree(void)
{
	struct stat st;
	const char *content = "File content\n";

	cl_git_pass(git_futils_mkdir("src/b", 0775, GIT_MKDIR_PATH));
	cl_git_pass(git_futils_mkdir("src/c/d", 0775, GIT_MKDIR_PATH));
	cl_git_pass(git_futils_mkdir("src/c/e", 0775, GIT_MKDIR_PATH));

	cl_git_mkfile("src/f1", content);
	cl_git_mkfile("src/b/f2", content);
	cl_git_mkfile("src/c/f3", content);
	cl_git_mkfile("src/c/d/f4", content);
	cl_git_mkfile("src/c/d/.f5", content);

#ifndef GIT_WIN32
	cl_assert(p_symlink("../../b/f2", "src/c/d/l1") == 0);
#endif

	cl_assert(git_path_isdir("src"));
	cl_assert(git_path_isdir("src/b"));
	cl_assert(git_path_isdir("src/c/d"));
	cl_assert(git_path_isfile("src/c/d/f4"));

	/* copy with no empty dirs, yes links, no dotfiles, no overwrite */

	cl_git_pass(
		git_futils_cp_r("src", "t1", GIT_CPDIR_COPY_SYMLINKS, 0) );

	cl_assert(git_path_isdir("t1"));
	cl_assert(git_path_isdir("t1/b"));
	cl_assert(git_path_isdir("t1/c"));
	cl_assert(git_path_isdir("t1/c/d"));
	cl_assert(!git_path_isdir("t1/c/e"));

	cl_assert(git_path_isfile("t1/f1"));
	cl_assert(git_path_isfile("t1/b/f2"));
	cl_assert(git_path_isfile("t1/c/f3"));
	cl_assert(git_path_isfile("t1/c/d/f4"));
	cl_assert(!git_path_isfile("t1/c/d/.f5"));

	cl_git_pass(git_path_lstat("t1/c/f3", &st));
	cl_assert(S_ISREG(st.st_mode));
	cl_assert(strlen(content) == (size_t)st.st_size);

#ifndef GIT_WIN32
	cl_git_pass(git_path_lstat("t1/c/d/l1", &st));
	cl_assert(S_ISLNK(st.st_mode));
#endif

	cl_git_pass(git_futils_rmdir_r("t1", NULL, GIT_RMDIR_REMOVE_FILES));
	cl_assert(!git_path_isdir("t1"));

	/* copy with empty dirs, no links, yes dotfiles, no overwrite */

	cl_git_pass(
		git_futils_cp_r("src", "t2", GIT_CPDIR_CREATE_EMPTY_DIRS | GIT_CPDIR_COPY_DOTFILES, 0) );

	cl_assert(git_path_isdir("t2"));
	cl_assert(git_path_isdir("t2/b"));
	cl_assert(git_path_isdir("t2/c"));
	cl_assert(git_path_isdir("t2/c/d"));
	cl_assert(git_path_isdir("t2/c/e"));

	cl_assert(git_path_isfile("t2/f1"));
	cl_assert(git_path_isfile("t2/b/f2"));
	cl_assert(git_path_isfile("t2/c/f3"));
	cl_assert(git_path_isfile("t2/c/d/f4"));
	cl_assert(git_path_isfile("t2/c/d/.f5"));

#ifndef GIT_WIN32
	cl_git_fail(git_path_lstat("t2/c/d/l1", &st));
#endif

	cl_git_pass(git_futils_rmdir_r("t2", NULL, GIT_RMDIR_REMOVE_FILES));
	cl_assert(!git_path_isdir("t2"));

#ifndef GIT_WIN32
	cl_git_pass(git_futils_cp_r("src", "t3", GIT_CPDIR_CREATE_EMPTY_DIRS | GIT_CPDIR_LINK_FILES, 0));
	cl_assert(git_path_isdir("t3"));

	cl_assert(git_path_isdir("t3"));
	cl_assert(git_path_isdir("t3/b"));
	cl_assert(git_path_isdir("t3/c"));
	cl_assert(git_path_isdir("t3/c/d"));
	cl_assert(git_path_isdir("t3/c/e"));

	assert_hard_link("t3/f1");
	assert_hard_link("t3/b/f2");
	assert_hard_link("t3/c/f3");
	assert_hard_link("t3/c/d/f4");
#endif

	cl_git_pass(git_futils_rmdir_r("src", NULL, GIT_RMDIR_REMOVE_FILES));
}