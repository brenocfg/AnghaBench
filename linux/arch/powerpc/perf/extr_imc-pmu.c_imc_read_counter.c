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
typedef  int /*<<< orphan*/  u64 ;
struct TYPE_2__ {int /*<<< orphan*/  prev_count; } ;
struct perf_event {TYPE_1__ hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  READ_ONCE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  be64_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * get_event_base_addr (struct perf_event*) ; 
 int /*<<< orphan*/  local64_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u64 imc_read_counter(struct perf_event *event)
{
	u64 *addr, data;

	/*
	 * In-Memory Collection (IMC) counters are free flowing counters.
	 * So we take a snapshot of the counter value on enable and save it
	 * to calculate the delta at later stage to present the event counter
	 * value.
	 */
	addr = get_event_base_addr(event);
	data = be64_to_cpu(READ_ONCE(*addr));
	local64_set(&event->hw.prev_count, data);

	return data;
}