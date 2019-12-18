#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/ * git_trace_cb; } ;

/* Variables and functions */
 scalar_t__ GIT_TRACE_NONE ; 
 int /*<<< orphan*/  _cl_trace_cb__event_handler ; 
 int /*<<< orphan*/  _load_trace_params () ; 
 int /*<<< orphan*/  cl_trace_register (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_trace_set (scalar_t__,int /*<<< orphan*/ *) ; 
 scalar_t__ s_trace_level ; 
 int /*<<< orphan*/  s_trace_loaded ; 
 TYPE_1__* s_trace_method ; 

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