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
 int /*<<< orphan*/  GIT_TRACE_FATAL ; 
 scalar_t__ GIT_TRACE_INFO ; 
 scalar_t__ GIT_TRACE_NONE ; 
 int /*<<< orphan*/  cl_assert (int) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_skip () ; 
 int /*<<< orphan*/  git_trace (int /*<<< orphan*/ ,char*,char*) ; 
 scalar_t__ git_trace_level () ; 
 int /*<<< orphan*/  git_trace_set (scalar_t__,int /*<<< orphan*/ *) ; 
 scalar_t__ written ; 

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