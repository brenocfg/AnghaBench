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
struct TYPE_3__ {int /*<<< orphan*/  global_status; } ;
struct TYPE_4__ {TYPE_1__ pmu; } ;
struct kvm_vcpu {TYPE_2__ arch; } ;

/* Variables and functions */
 int /*<<< orphan*/  KVM_REQ_PMI ; 
 int /*<<< orphan*/  MSR_CORE_PERF_GLOBAL_OVF_CTRL_TRACE_TOPA_PMI_BIT ; 
 int /*<<< orphan*/  __set_bit (int /*<<< orphan*/ ,unsigned long*) ; 
 struct kvm_vcpu* __this_cpu_read (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  current_vcpu ; 
 int /*<<< orphan*/  kvm_make_request (int /*<<< orphan*/ ,struct kvm_vcpu*) ; 

__attribute__((used)) static void kvm_handle_intel_pt_intr(void)
{
	struct kvm_vcpu *vcpu = __this_cpu_read(current_vcpu);

	kvm_make_request(KVM_REQ_PMI, vcpu);
	__set_bit(MSR_CORE_PERF_GLOBAL_OVF_CTRL_TRACE_TOPA_PMI_BIT,
			(unsigned long *)&vcpu->arch.pmu.global_status);
}