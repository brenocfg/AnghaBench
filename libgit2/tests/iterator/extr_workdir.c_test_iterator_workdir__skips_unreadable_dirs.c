#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  git_iterator ;
struct TYPE_3__ {int /*<<< orphan*/  path; } ;
typedef  TYPE_1__ git_index_entry ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_ITEROVER ; 
 int /*<<< orphan*/  cl_assert_equal_i (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_assert_equal_s (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_mkfile (char*,char*) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_sandbox_init (char*) ; 
 int /*<<< orphan*/  cl_is_chmod_supported () ; 
 int /*<<< orphan*/  cl_must_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_skip () ; 
 int /*<<< orphan*/  g_repo ; 
 scalar_t__ geteuid () ; 
 int /*<<< orphan*/  git_iterator_advance (TYPE_1__ const**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_iterator_for_filesystem (int /*<<< orphan*/ **,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_iterator_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  p_chmod (char*,int) ; 
 int /*<<< orphan*/  p_mkdir (char*,int) ; 

void test_iterator_workdir__skips_unreadable_dirs(void)
{
	git_iterator *i;
	const git_index_entry *e;

	if (!cl_is_chmod_supported())
		return;

#ifndef GIT_WIN32
	if (geteuid() == 0)
		cl_skip();
#endif

	g_repo = cl_git_sandbox_init("empty_standard_repo");

	cl_must_pass(p_mkdir("empty_standard_repo/r", 0777));
	cl_git_mkfile("empty_standard_repo/r/a", "hello");
	cl_must_pass(p_mkdir("empty_standard_repo/r/b", 0777));
	cl_git_mkfile("empty_standard_repo/r/b/problem", "not me");
	cl_must_pass(p_chmod("empty_standard_repo/r/b", 0000));
	cl_must_pass(p_mkdir("empty_standard_repo/r/c", 0777));
	cl_git_mkfile("empty_standard_repo/r/c/foo", "aloha");
	cl_git_mkfile("empty_standard_repo/r/d", "final");

	cl_git_pass(git_iterator_for_filesystem(
		&i, "empty_standard_repo/r", NULL));

	cl_git_pass(git_iterator_advance(&e, i)); /* a */
	cl_assert_equal_s("a", e->path);

	cl_git_pass(git_iterator_advance(&e, i)); /* c/foo */
	cl_assert_equal_s("c/foo", e->path);

	cl_git_pass(git_iterator_advance(&e, i)); /* d */
	cl_assert_equal_s("d", e->path);

	cl_must_pass(p_chmod("empty_standard_repo/r/b", 0777));

	cl_assert_equal_i(GIT_ITEROVER, git_iterator_advance(&e, i));
	git_iterator_free(i);
}