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
typedef  scalar_t__ uint64_t ;
struct vcpu_info {int dummy; } ;
struct TYPE_2__ {struct vcpu_info* vcpu_info; } ;

/* Variables and functions */
 TYPE_1__* HYPERVISOR_shared_info ; 
 int NSEC_IN_USEC ; 
 scalar_t__ xen_fetch_vcpu_time (struct vcpu_info*) ; 

void
xen_delay(int n)
{
	struct vcpu_info *vcpu = &HYPERVISOR_shared_info->vcpu_info[0];
	uint64_t end_ns;
	uint64_t current;

	end_ns = xen_fetch_vcpu_time(vcpu);
	end_ns += n * NSEC_IN_USEC;

	for (;;) {
		current = xen_fetch_vcpu_time(vcpu);
		if (current >= end_ns)
			break;
	}
}