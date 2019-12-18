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
struct TYPE_2__ {int /*<<< orphan*/  events_guest; int /*<<< orphan*/  events_host; } ;
struct kvm_host_data {TYPE_1__ pmu_events; } ;

/* Variables and functions */
 int /*<<< orphan*/  kvm_host_data ; 
 struct kvm_host_data* this_cpu_ptr (int /*<<< orphan*/ *) ; 

void kvm_clr_pmu_events(u32 clr)
{
	struct kvm_host_data *ctx = this_cpu_ptr(&kvm_host_data);

	ctx->pmu_events.events_host &= ~clr;
	ctx->pmu_events.events_guest &= ~clr;
}