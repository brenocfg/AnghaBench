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
struct perf_event {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  imc_read_counter (struct perf_event*) ; 

__attribute__((used)) static void imc_event_start(struct perf_event *event, int flags)
{
	/*
	 * In Memory Counters are free flowing counters. HW or the microcode
	 * keeps adding to the counter offset in memory. To get event
	 * counter value, we snapshot the value here and we calculate
	 * delta at later point.
	 */
	imc_read_counter(event);
}