#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u64 ;
struct TYPE_4__ {scalar_t__ event_base; } ;
struct TYPE_3__ {int config; } ;
struct perf_event {TYPE_2__ hw; TYPE_1__ attr; } ;

/* Variables and functions */
 int IMC_EVENT_OFFSET_MASK ; 
 scalar_t__ is_thread_imc_pmu (struct perf_event*) ; 
 scalar_t__ per_cpu (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smp_processor_id () ; 
 int /*<<< orphan*/  thread_imc_mem ; 

__attribute__((used)) static u64 * get_event_base_addr(struct perf_event *event)
{
	u64 addr;

	if (is_thread_imc_pmu(event)) {
		addr = (u64)per_cpu(thread_imc_mem, smp_processor_id());
		return (u64 *)(addr + (event->attr.config & IMC_EVENT_OFFSET_MASK));
	}

	return (u64 *)event->hw.event_base;
}