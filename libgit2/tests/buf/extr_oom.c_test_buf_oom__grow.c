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
 int /*<<< orphan*/  cl_git_pass (int) ; 
 int /*<<< orphan*/  git_buf_dispose (int /*<<< orphan*/ *) ; 
 int git_buf_grow (int /*<<< orphan*/ *,int) ; 
 int git_buf_oom (int /*<<< orphan*/ *) ; 

void test_buf_oom__grow(void)
{
	git_buf buf = GIT_BUF_INIT;

	cl_git_pass(git_buf_grow(&buf, 42));
	cl_assert(!git_buf_oom(&buf));

	cl_assert(git_buf_grow(&buf, 101) == -1);
	cl_assert(git_buf_oom(&buf));

	git_buf_dispose(&buf);
}