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
 int /*<<< orphan*/  cl_git_fail (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_mkfile (char*,char*) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_config_delete_entry (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  git_config_open_ondisk (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  p_unlink (char*) ; 

void test_config_include__included_variables_cannot_be_deleted(void)
{
	cl_git_mkfile("top-level", "[include]\npath = included\n");
	cl_git_mkfile("included", "[foo]\nbar = value");

	cl_git_pass(git_config_open_ondisk(&cfg, "top-level"));
	cl_git_fail(git_config_delete_entry(cfg, "foo.bar"));

	cl_git_pass(p_unlink("top-level"));
	cl_git_pass(p_unlink("included"));
}