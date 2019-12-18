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
 int /*<<< orphan*/  GIT_TRACE_NONE ; 
 int /*<<< orphan*/  cl_global_trace_register () ; 
 int /*<<< orphan*/  git_trace_set (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void test_trace_trace__cleanup(void)
{
	git_trace_set(GIT_TRACE_NONE, NULL);

	/* If global tracing was enabled, restart it. */
	cl_global_trace_register();
}