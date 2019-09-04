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
 int strlen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_string ; 

void test_buf_basic__resize(void)
{
	git_buf buf1 = GIT_BUF_INIT;
	git_buf_puts(&buf1, test_string);
	cl_assert(git_buf_oom(&buf1) == 0);
	cl_assert_equal_s(git_buf_cstr(&buf1), test_string);

	git_buf_puts(&buf1, test_string);
	cl_assert(strlen(git_buf_cstr(&buf1)) == strlen(test_string) * 2);
	git_buf_dispose(&buf1);
}