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

void cl_global_trace_disable(void)
{
#if defined(GIT_TRACE)
	cl_trace_register(NULL, NULL);
	git_trace_set(GIT_TRACE_NONE, NULL);
	if (s_trace_method && s_trace_method->close)
		s_trace_method->close();

	/* Leave s_trace_ vars set so they can restart tracing
	 * since we only want to hit the environment variables
	 * once.
	 */
#endif
}