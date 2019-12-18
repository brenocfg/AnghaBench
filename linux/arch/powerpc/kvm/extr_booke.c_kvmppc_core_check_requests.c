#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int epr_needed; } ;
struct kvm_vcpu {TYPE_3__* run; TYPE_2__ arch; } ;
struct TYPE_4__ {scalar_t__ epr; } ;
struct TYPE_6__ {int /*<<< orphan*/  exit_reason; TYPE_1__ epr; } ;

/* Variables and functions */
 int /*<<< orphan*/  KVM_EXIT_EPR ; 
 int /*<<< orphan*/  KVM_EXIT_WATCHDOG ; 
 int /*<<< orphan*/  KVM_REQ_EPR_EXIT ; 
 int /*<<< orphan*/  KVM_REQ_PENDING_TIMER ; 
 int /*<<< orphan*/  KVM_REQ_TLB_FLUSH ; 
 int /*<<< orphan*/  KVM_REQ_WATCHDOG ; 
 scalar_t__ kvm_check_request (int /*<<< orphan*/ ,struct kvm_vcpu*) ; 
 int /*<<< orphan*/  kvmppc_core_flush_tlb (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  update_timer_ints (struct kvm_vcpu*) ; 

int kvmppc_core_check_requests(struct kvm_vcpu *vcpu)
{
	int r = 1; /* Indicate we want to get back into the guest */

	if (kvm_check_request(KVM_REQ_PENDING_TIMER, vcpu))
		update_timer_ints(vcpu);
#if defined(CONFIG_KVM_E500V2) || defined(CONFIG_KVM_E500MC)
	if (kvm_check_request(KVM_REQ_TLB_FLUSH, vcpu))
		kvmppc_core_flush_tlb(vcpu);
#endif

	if (kvm_check_request(KVM_REQ_WATCHDOG, vcpu)) {
		vcpu->run->exit_reason = KVM_EXIT_WATCHDOG;
		r = 0;
	}

	if (kvm_check_request(KVM_REQ_EPR_EXIT, vcpu)) {
		vcpu->run->epr.epr = 0;
		vcpu->arch.epr_needed = true;
		vcpu->run->exit_reason = KVM_EXIT_EPR;
		r = 0;
	}

	return r;
}