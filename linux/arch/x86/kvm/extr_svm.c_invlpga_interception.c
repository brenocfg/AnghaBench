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
struct kvm_vcpu {int dummy; } ;
struct vcpu_svm {struct kvm_vcpu vcpu; TYPE_2__* vmcb; } ;
struct TYPE_3__ {int /*<<< orphan*/  rip; } ;
struct TYPE_4__ {TYPE_1__ save; } ;

/* Variables and functions */
 int /*<<< orphan*/  kvm_mmu_invlpg (struct kvm_vcpu*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvm_rax_read (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  kvm_rcx_read (struct kvm_vcpu*) ; 
 int kvm_skip_emulated_instruction (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  trace_kvm_invlpga (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int invlpga_interception(struct vcpu_svm *svm)
{
	struct kvm_vcpu *vcpu = &svm->vcpu;

	trace_kvm_invlpga(svm->vmcb->save.rip, kvm_rcx_read(&svm->vcpu),
			  kvm_rax_read(&svm->vcpu));

	/* Let's treat INVLPGA the same as INVLPG (can be optimized!) */
	kvm_mmu_invlpg(vcpu, kvm_rax_read(&svm->vcpu));

	return kvm_skip_emulated_instruction(&svm->vcpu);
}