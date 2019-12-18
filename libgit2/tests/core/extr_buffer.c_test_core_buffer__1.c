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
 int /*<<< orphan*/  git_buf_printf (int /*<<< orphan*/ *,char*,char*,...) ; 

void test_core_buffer__1(void)
{
	git_buf buf = GIT_BUF_INIT;

	git_buf_printf(&buf, "%s %s %d ", "shoop", "da", 23);
	cl_assert(git_buf_oom(&buf) == 0);
	cl_assert_equal_s("shoop da 23 ", git_buf_cstr(&buf));

	git_buf_printf(&buf, "%s %d", "woop", 42);
	cl_assert(git_buf_oom(&buf) == 0);
	cl_assert_equal_s("shoop da 23 woop 42", git_buf_cstr(&buf));

	git_buf_dispose(&buf);
}