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
typedef  int /*<<< orphan*/  uint64_t ;

/* Variables and functions */
 size_t ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BUG (char*) ; 
 int /*<<< orphan*/  getnanotime () ; 
 size_t perf_indent ; 
 int /*<<< orphan*/ * perf_start_times ; 
 int /*<<< orphan*/  trace_perf_key ; 
 int /*<<< orphan*/  trace_want (int /*<<< orphan*/ *) ; 

uint64_t trace_performance_enter(void)
{
	uint64_t now;

	if (!trace_want(&trace_perf_key))
		return 0;

	now = getnanotime();
	perf_start_times[perf_indent] = now;
	if (perf_indent + 1 < ARRAY_SIZE(perf_start_times))
		perf_indent++;
	else
		BUG("Too deep indentation");
	return now;
}