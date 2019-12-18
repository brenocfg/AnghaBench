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
 scalar_t__ GIT_TRACE_INFO ; 
 int /*<<< orphan*/  cl_assert (int) ; 
 int /*<<< orphan*/  cl_skip () ; 
 scalar_t__ git_trace_level () ; 

void test_trace_trace__sets(void)
{
#ifdef GIT_TRACE
	cl_assert(git_trace_level() == GIT_TRACE_INFO);
#else
	cl_skip();
#endif
}