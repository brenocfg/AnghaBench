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
typedef  int /*<<< orphan*/  git_buf ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_BUF_INIT ; 
 int /*<<< orphan*/  cl_assert (int) ; 
 int /*<<< orphan*/  cl_assert_equal_s (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_buf_cstr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_buf_dispose (int /*<<< orphan*/ *) ; 
 scalar_t__ git_buf_oom (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_buf_sets (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  git_buf_swap (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void test_core_buffer__6(void)
{
	git_buf a = GIT_BUF_INIT;
	git_buf b = GIT_BUF_INIT;

	git_buf_sets(&a, "foo");
	cl_assert(git_buf_oom(&a) == 0);
	git_buf_sets(&b, "bar");
	cl_assert(git_buf_oom(&b) == 0);

	cl_assert_equal_s("foo", git_buf_cstr(&a));
	cl_assert_equal_s("bar", git_buf_cstr(&b));

	git_buf_swap(&a, &b);

	cl_assert_equal_s("bar", git_buf_cstr(&a));
	cl_assert_equal_s("foo", git_buf_cstr(&b));

	git_buf_dispose(&a);
	git_buf_dispose(&b);
}