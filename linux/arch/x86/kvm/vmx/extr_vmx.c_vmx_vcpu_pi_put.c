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
struct pi_desc {int dummy; } ;
struct kvm_vcpu {scalar_t__ preempted; int /*<<< orphan*/  kvm; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_POSTING_CAP ; 
 int /*<<< orphan*/  irq_remapping_cap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvm_arch_has_assigned_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvm_vcpu_apicv_active (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  pi_set_sn (struct pi_desc*) ; 
 struct pi_desc* vcpu_to_pi_desc (struct kvm_vcpu*) ; 

__attribute__((used)) static void vmx_vcpu_pi_put(struct kvm_vcpu *vcpu)
{
	struct pi_desc *pi_desc = vcpu_to_pi_desc(vcpu);

	if (!kvm_arch_has_assigned_device(vcpu->kvm) ||
		!irq_remapping_cap(IRQ_POSTING_CAP)  ||
		!kvm_vcpu_apicv_active(vcpu))
		return;

	/* Set SN when the vCPU is preempted */
	if (vcpu->preempted)
		pi_set_sn(pi_desc);
}