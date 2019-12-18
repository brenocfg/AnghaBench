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
struct pt_regs {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __perf_event_interrupt (struct pt_regs*) ; 
 int /*<<< orphan*/  perf_sample_event_took (scalar_t__) ; 
 scalar_t__ sched_clock () ; 

__attribute__((used)) static void perf_event_interrupt(struct pt_regs *regs)
{
	u64 start_clock = sched_clock();

	__perf_event_interrupt(regs);
	perf_sample_event_took(sched_clock() - start_clock);
}