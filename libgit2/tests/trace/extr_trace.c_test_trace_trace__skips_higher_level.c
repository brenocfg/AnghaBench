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
 int /*<<< orphan*/  GIT_TRACE_DEBUG ; 
 int /*<<< orphan*/  cl_assert (int) ; 
 int /*<<< orphan*/  cl_skip () ; 
 int /*<<< orphan*/  git_trace (int /*<<< orphan*/ ,char*,char*) ; 
 scalar_t__ written ; 

void test_trace_trace__skips_higher_level(void)
{
#ifdef GIT_TRACE
	cl_assert(written == 0);
	git_trace(GIT_TRACE_DEBUG, "Hello %s!", "world");
	cl_assert(written == 0);
#else
	cl_skip();
#endif
}