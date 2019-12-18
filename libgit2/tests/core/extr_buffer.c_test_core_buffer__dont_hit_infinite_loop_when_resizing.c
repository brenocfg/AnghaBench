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
 int /*<<< orphan*/  SIZE_MAX ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_buf_dispose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_buf_puts (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  git_buf_try_grow (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

void test_core_buffer__dont_hit_infinite_loop_when_resizing(void)
{
	git_buf buf = GIT_BUF_INIT;

	cl_git_pass(git_buf_puts(&buf, "foobar"));
	/*
	 * We do not care whether this succeeds or fails, which
	 * would depend on platform-specific allocation
	 * semantics. We only want to know that the function
	 * actually returns.
	 */
	(void)git_buf_try_grow(&buf, SIZE_MAX, true);

	git_buf_dispose(&buf);
}