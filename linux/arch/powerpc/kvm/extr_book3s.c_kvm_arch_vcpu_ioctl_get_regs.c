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
struct TYPE_2__ {int /*<<< orphan*/  pid; } ;
struct kvm_vcpu {TYPE_1__ arch; } ;
struct kvm_regs {int /*<<< orphan*/ * gpr; int /*<<< orphan*/  sprg7; int /*<<< orphan*/  sprg6; int /*<<< orphan*/  sprg5; int /*<<< orphan*/  sprg4; int /*<<< orphan*/  sprg3; int /*<<< orphan*/  sprg2; int /*<<< orphan*/  sprg1; int /*<<< orphan*/  sprg0; int /*<<< orphan*/  pid; int /*<<< orphan*/  srr1; int /*<<< orphan*/  srr0; int /*<<< orphan*/  msr; int /*<<< orphan*/  xer; int /*<<< orphan*/  lr; int /*<<< orphan*/  ctr; int /*<<< orphan*/  cr; int /*<<< orphan*/  pc; } ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kvmppc_get_cr (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  kvmppc_get_ctr (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  kvmppc_get_gpr (struct kvm_vcpu*,int) ; 
 int /*<<< orphan*/  kvmppc_get_lr (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  kvmppc_get_msr (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  kvmppc_get_pc (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  kvmppc_get_sprg0 (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  kvmppc_get_sprg1 (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  kvmppc_get_sprg2 (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  kvmppc_get_sprg3 (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  kvmppc_get_sprg4 (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  kvmppc_get_sprg5 (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  kvmppc_get_sprg6 (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  kvmppc_get_sprg7 (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  kvmppc_get_srr0 (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  kvmppc_get_srr1 (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  kvmppc_get_xer (struct kvm_vcpu*) ; 

int kvm_arch_vcpu_ioctl_get_regs(struct kvm_vcpu *vcpu, struct kvm_regs *regs)
{
	int i;

	regs->pc = kvmppc_get_pc(vcpu);
	regs->cr = kvmppc_get_cr(vcpu);
	regs->ctr = kvmppc_get_ctr(vcpu);
	regs->lr = kvmppc_get_lr(vcpu);
	regs->xer = kvmppc_get_xer(vcpu);
	regs->msr = kvmppc_get_msr(vcpu);
	regs->srr0 = kvmppc_get_srr0(vcpu);
	regs->srr1 = kvmppc_get_srr1(vcpu);
	regs->pid = vcpu->arch.pid;
	regs->sprg0 = kvmppc_get_sprg0(vcpu);
	regs->sprg1 = kvmppc_get_sprg1(vcpu);
	regs->sprg2 = kvmppc_get_sprg2(vcpu);
	regs->sprg3 = kvmppc_get_sprg3(vcpu);
	regs->sprg4 = kvmppc_get_sprg4(vcpu);
	regs->sprg5 = kvmppc_get_sprg5(vcpu);
	regs->sprg6 = kvmppc_get_sprg6(vcpu);
	regs->sprg7 = kvmppc_get_sprg7(vcpu);

	for (i = 0; i < ARRAY_SIZE(regs->gpr); i++)
		regs->gpr[i] = kvmppc_get_gpr(vcpu, i);

	return 0;
}