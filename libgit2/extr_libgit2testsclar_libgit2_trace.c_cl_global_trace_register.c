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

void cl_global_trace_register(void)
{
#if defined(GIT_TRACE)
	if (!s_trace_loaded)
		_load_trace_params();

	if (s_trace_level == GIT_TRACE_NONE)
		return;
	if (s_trace_method == NULL)
		return;
	if (s_trace_method->git_trace_cb == NULL)
		return;

	git_trace_set(s_trace_level, s_trace_method->git_trace_cb);
	cl_trace_register(_cl_trace_cb__event_handler, NULL);
#endif
}