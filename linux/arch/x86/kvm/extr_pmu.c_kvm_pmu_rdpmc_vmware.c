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
struct kvm_vcpu {TYPE_2__* kvm; } ;
struct TYPE_3__ {scalar_t__ kvmclock_offset; } ;
struct TYPE_4__ {TYPE_1__ arch; } ;

/* Variables and functions */
#define  VMWARE_BACKDOOR_PMC_APPARENT_TIME 130 
#define  VMWARE_BACKDOOR_PMC_HOST_TSC 129 
#define  VMWARE_BACKDOOR_PMC_REAL_TIME 128 
 scalar_t__ ktime_get_boottime_ns () ; 
 scalar_t__ rdtsc () ; 

__attribute__((used)) static int kvm_pmu_rdpmc_vmware(struct kvm_vcpu *vcpu, unsigned idx, u64 *data)
{
	u64 ctr_val;

	switch (idx) {
	case VMWARE_BACKDOOR_PMC_HOST_TSC:
		ctr_val = rdtsc();
		break;
	case VMWARE_BACKDOOR_PMC_REAL_TIME:
		ctr_val = ktime_get_boottime_ns();
		break;
	case VMWARE_BACKDOOR_PMC_APPARENT_TIME:
		ctr_val = ktime_get_boottime_ns() +
			vcpu->kvm->arch.kvmclock_offset;
		break;
	default:
		return 1;
	}

	*data = ctr_val;
	return 0;
}