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
typedef  scalar_t__ u64 ;
struct perf_event {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dump_trace_imc_data (struct perf_event*) ; 
 scalar_t__ get_trace_imc_event_base_addr () ; 
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void trace_imc_event_stop(struct perf_event *event, int flags)
{
	u64 local_mem = get_trace_imc_event_base_addr();
	dump_trace_imc_data(event);
	memset((void *)local_mem, 0, sizeof(u64));
}