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
 int /*<<< orphan*/  cfg ; 
 int /*<<< orphan*/  cl_assert_equal_i (int,int) ; 
 int /*<<< orphan*/  cl_git_mkfile (char*,char*) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_config_get_int32 (int*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  git_config_open_ondisk (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  p_unlink (char*) ; 

void test_config_include__variables_in_including_override_included(void)
{
	int i;

	cl_git_mkfile("top-level", "[include]\npath = included\n[foo]\nbar = 1");
	cl_git_mkfile("included", "[foo]\nbar = 2");

	cl_git_pass(git_config_open_ondisk(&cfg, "top-level"));
	cl_git_pass(git_config_get_int32(&i, cfg, "foo.bar"));
	cl_assert_equal_i(i, 1);

	cl_git_pass(p_unlink("top-level"));
	cl_git_pass(p_unlink("included"));
}