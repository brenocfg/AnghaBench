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
typedef  int /*<<< orphan*/  u32 ;
struct perf_event_attr {int /*<<< orphan*/  exclude_guest; int /*<<< orphan*/  exclude_host; } ;
struct TYPE_2__ {int /*<<< orphan*/  events_guest; int /*<<< orphan*/  events_host; } ;
struct kvm_host_data {TYPE_1__ pmu_events; } ;

/* Variables and functions */
 int /*<<< orphan*/  kvm_host_data ; 
 int /*<<< orphan*/  kvm_pmu_switch_needed (struct perf_event_attr*) ; 
 struct kvm_host_data* this_cpu_ptr (int /*<<< orphan*/ *) ; 

void kvm_set_pmu_events(u32 set, struct perf_event_attr *attr)
{
	struct kvm_host_data *ctx = this_cpu_ptr(&kvm_host_data);

	if (!kvm_pmu_switch_needed(attr))
		return;

	if (!attr->exclude_host)
		ctx->pmu_events.events_host |= set;
	if (!attr->exclude_guest)
		ctx->pmu_events.events_guest |= set;
}