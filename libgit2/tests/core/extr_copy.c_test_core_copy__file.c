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
 int S_ISREG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_assert (int) ; 
 int /*<<< orphan*/  cl_git_mkfile (char*,char const*) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_futils_cp (char*,char*,int) ; 
 int /*<<< orphan*/  git_path_lstat (char*,struct stat*) ; 
 int /*<<< orphan*/  p_unlink (char*) ; 
 size_t strlen (char const*) ; 

void test_core_copy__file(void)
{
	struct stat st;
	const char *content = "This is some stuff to copy\n";

	cl_git_mkfile("copy_me", content);

	cl_git_pass(git_futils_cp("copy_me", "copy_me_two", 0664));

	cl_git_pass(git_path_lstat("copy_me_two", &st));
	cl_assert(S_ISREG(st.st_mode));
	cl_assert(strlen(content) == (size_t)st.st_size);

	cl_git_pass(p_unlink("copy_me_two"));
	cl_git_pass(p_unlink("copy_me"));
}