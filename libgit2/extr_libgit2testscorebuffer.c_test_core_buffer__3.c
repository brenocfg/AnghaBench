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
 int /*<<< orphan*/  cl_assert_equal_s (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_buf_cstr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_buf_dispose (int /*<<< orphan*/ *) ; 
 scalar_t__ git_buf_oom (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_buf_puts (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_buf_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  test_4096 ; 
 int /*<<< orphan*/  test_8192 ; 

void test_core_buffer__3(void)
{
	git_buf buf = GIT_BUF_INIT;

	/* set to string */
	git_buf_set(&buf, test_4096, 4096);
	cl_assert(git_buf_oom(&buf) == 0);
	cl_assert_equal_s(test_4096, git_buf_cstr(&buf));

	/* append string */
	git_buf_puts(&buf, test_4096);
	cl_assert(git_buf_oom(&buf) == 0);
	cl_assert_equal_s(test_8192, git_buf_cstr(&buf));

	/* set to string again (should overwrite - not append) */
	git_buf_set(&buf, test_4096, 4096);
	cl_assert(git_buf_oom(&buf) == 0);
	cl_assert_equal_s(test_4096, git_buf_cstr(&buf));

	git_buf_dispose(&buf);
}