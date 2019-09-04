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
 int /*<<< orphan*/  cl_skip () ; 

void test_trace_trace__can_unset(void)
{
#ifdef GIT_TRACE
	cl_assert(git_trace_level() == GIT_TRACE_INFO);
	cl_git_pass(git_trace_set(GIT_TRACE_NONE, NULL));

	cl_assert(git_trace_level() == GIT_TRACE_NONE);

	cl_assert(written == 0);
	git_trace(GIT_TRACE_FATAL, "Hello %s!", "world");
	cl_assert(written == 0);
#else
	cl_skip();
#endif
}