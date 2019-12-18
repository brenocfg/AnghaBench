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
 int /*<<< orphan*/  GIT_TRACE_INFO ; 
 int /*<<< orphan*/  cl_global_trace_disable () ; 
 int /*<<< orphan*/  git_trace_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_callback ; 
 scalar_t__ written ; 

void test_trace_trace__initialize(void)
{
	/* If global tracing is enabled, disable for the duration of this test. */
	cl_global_trace_disable();

	git_trace_set(GIT_TRACE_INFO, trace_callback);
	written = 0;
}