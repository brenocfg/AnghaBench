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
typedef  int /*<<< orphan*/  git_attr_session ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (char const**) ; 
 TYPE_1__ GIT_BUF_INIT ; 
 int /*<<< orphan*/  GIT_SYSDIR_SYSTEM ; 
 int /*<<< orphan*/  cl_assert_equal_s (char const*,char*) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_rewritefile (char*,char*) ; 
 int /*<<< orphan*/  cl_git_sandbox_reopen () ; 
 int /*<<< orphan*/  clar_sandbox_path () ; 
 int /*<<< orphan*/  g_repo ; 
 int /*<<< orphan*/  git_attr_get_many_with_session (char const**,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,char const**) ; 
 int /*<<< orphan*/  git_attr_session__free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_attr_session__init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_buf_dispose (TYPE_1__*) ; 
 int /*<<< orphan*/  git_buf_joinpath (TYPE_1__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  git_sysdir_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  p_mkdir (char*,int) ; 
 int /*<<< orphan*/  p_rmdir (char*) ; 
 int /*<<< orphan*/  p_unlink (char*) ; 

void test_attr_repo__sysdir_with_session(void)
{
	const char *values[2], *attrs[2] = { "foo", "bar" };
	git_buf sysdir = GIT_BUF_INIT;
	git_attr_session session;

	cl_git_pass(p_mkdir("system", 0777));
	cl_git_rewritefile("system/gitattributes", "file foo=1 bar=2");
	cl_git_pass(git_buf_joinpath(&sysdir, clar_sandbox_path(), "system"));
	cl_git_pass(git_sysdir_set(GIT_SYSDIR_SYSTEM, sysdir.ptr));
	g_repo = cl_git_sandbox_reopen();

	cl_git_pass(git_attr_session__init(&session, g_repo));
	cl_git_pass(git_attr_get_many_with_session(values, g_repo, &session, 0, "file", ARRAY_SIZE(attrs), attrs));

	cl_assert_equal_s(values[0], "1");
	cl_assert_equal_s(values[1], "2");

	cl_git_pass(p_unlink("system/gitattributes"));
	cl_git_pass(p_rmdir("system"));
	git_buf_dispose(&sysdir);
	git_attr_session__free(&session);
}