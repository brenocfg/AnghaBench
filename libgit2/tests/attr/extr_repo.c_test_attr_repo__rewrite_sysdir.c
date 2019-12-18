#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  ptr; } ;
typedef  TYPE_1__ git_buf ;

/* Variables and functions */
 TYPE_1__ GIT_BUF_INIT ; 
 int /*<<< orphan*/  GIT_SYSDIR_SYSTEM ; 
 int /*<<< orphan*/  cl_assert_equal_s (char const*,char*) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_rewritefile (char*,char*) ; 
 int /*<<< orphan*/  cl_git_sandbox_reopen () ; 
 int /*<<< orphan*/  clar_sandbox_path () ; 
 int /*<<< orphan*/  g_repo ; 
 int /*<<< orphan*/  git_attr_get (char const**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  git_buf_dispose (TYPE_1__*) ; 
 int /*<<< orphan*/  git_buf_joinpath (TYPE_1__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  git_sysdir_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  p_mkdir (char*,int) ; 

void test_attr_repo__rewrite_sysdir(void)
{
	git_buf sysdir = GIT_BUF_INIT;
	const char *value;

	cl_git_pass(p_mkdir("system", 0777));
	cl_git_pass(git_buf_joinpath(&sysdir, clar_sandbox_path(), "system"));
	cl_git_pass(git_sysdir_set(GIT_SYSDIR_SYSTEM, sysdir.ptr));
	g_repo = cl_git_sandbox_reopen();

	cl_git_rewritefile("system/gitattributes", "file foo=first");
	cl_git_pass(git_attr_get(&value, g_repo, 0, "file", "foo"));
	cl_assert_equal_s(value, "first");

	cl_git_rewritefile("system/gitattributes", "file foo=second");
	cl_git_pass(git_attr_get(&value, g_repo, 0, "file", "foo"));
	cl_assert_equal_s(value, "second");

	git_buf_dispose(&sysdir);
}