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
 int /*<<< orphan*/  cl_assert (int) ; 
 int /*<<< orphan*/  cl_git_mkfile (char*,char*) ; 
 int /*<<< orphan*/  cl_must_pass (int /*<<< orphan*/ ) ; 
 int git_path_is_empty_dir (char*) ; 
 int /*<<< orphan*/  p_mkdir (char*,int) ; 
 int /*<<< orphan*/  p_rmdir (char*) ; 
 int /*<<< orphan*/  p_unlink (char*) ; 

void test_core_dirent__empty_dir(void)
{
	cl_must_pass(p_mkdir("empty_dir", 0777));
	cl_assert(git_path_is_empty_dir("empty_dir"));

	cl_git_mkfile("empty_dir/content", "whatever\n");
	cl_assert(!git_path_is_empty_dir("empty_dir"));
	cl_assert(!git_path_is_empty_dir("empty_dir/content"));

	cl_must_pass(p_unlink("empty_dir/content"));

	cl_must_pass(p_mkdir("empty_dir/content", 0777));
	cl_assert(!git_path_is_empty_dir("empty_dir"));
	cl_assert(git_path_is_empty_dir("empty_dir/content"));

	cl_must_pass(p_rmdir("empty_dir/content"));

	cl_must_pass(p_rmdir("empty_dir"));
}