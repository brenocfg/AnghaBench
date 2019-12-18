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
 scalar_t__ current_thread_info () ; 
 int /*<<< orphan*/  trace_hardirqs_on () ; 

void um_trace_signals_on(void)
{
	if (current_thread_info())
		trace_hardirqs_on();
}