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
typedef  int ulong ;
struct kvmppc_book3s_shadow_vcpu {int in_use; int shadow_srr1; int /*<<< orphan*/  shadow_fscr; int /*<<< orphan*/  last_inst; int /*<<< orphan*/  fault_dsisr; int /*<<< orphan*/  fault_dar; int /*<<< orphan*/  pc; int /*<<< orphan*/  lr; int /*<<< orphan*/  ctr; int /*<<< orphan*/  xer; int /*<<< orphan*/  cr; int /*<<< orphan*/ * gpr; } ;
struct TYPE_4__ {int /*<<< orphan*/  nip; int /*<<< orphan*/  link; int /*<<< orphan*/  ctr; int /*<<< orphan*/  xer; int /*<<< orphan*/  ccr; int /*<<< orphan*/ * gpr; } ;
struct TYPE_5__ {int shadow_srr1; scalar_t__ entry_ic; int /*<<< orphan*/  ic; scalar_t__ entry_vtb; scalar_t__ entry_tb; int /*<<< orphan*/  spurr; int /*<<< orphan*/  purr; int /*<<< orphan*/  shadow_fscr; int /*<<< orphan*/  last_inst; int /*<<< orphan*/  fault_dsisr; int /*<<< orphan*/  fault_dar; TYPE_1__ regs; } ;
struct kvm_vcpu {TYPE_2__ arch; } ;
struct TYPE_6__ {int /*<<< orphan*/  vtb; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPU_FTR_ARCH_207S ; 
 int MSR_PR ; 
 int MSR_TS_MASK ; 
 int /*<<< orphan*/  SPRN_IC ; 
 scalar_t__ cpu_has_feature (int /*<<< orphan*/ ) ; 
 scalar_t__ get_tb () ; 
 scalar_t__ get_vtb () ; 
 int kvmppc_get_msr (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  kvmppc_recalc_shadow_msr (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  kvmppc_set_msr_fast (struct kvm_vcpu*,int) ; 
 scalar_t__ mfspr (int /*<<< orphan*/ ) ; 
 struct kvmppc_book3s_shadow_vcpu* svcpu_get (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  svcpu_put (struct kvmppc_book3s_shadow_vcpu*) ; 
 TYPE_3__* to_book3s (struct kvm_vcpu*) ; 
 scalar_t__ unlikely (int) ; 

void kvmppc_copy_from_svcpu(struct kvm_vcpu *vcpu)
{
	struct kvmppc_book3s_shadow_vcpu *svcpu = svcpu_get(vcpu);
#ifdef CONFIG_PPC_TRANSACTIONAL_MEM
	ulong old_msr;
#endif

	/*
	 * Maybe we were already preempted and synced the svcpu from
	 * our preempt notifiers. Don't bother touching this svcpu then.
	 */
	if (!svcpu->in_use)
		goto out;

	vcpu->arch.regs.gpr[0] = svcpu->gpr[0];
	vcpu->arch.regs.gpr[1] = svcpu->gpr[1];
	vcpu->arch.regs.gpr[2] = svcpu->gpr[2];
	vcpu->arch.regs.gpr[3] = svcpu->gpr[3];
	vcpu->arch.regs.gpr[4] = svcpu->gpr[4];
	vcpu->arch.regs.gpr[5] = svcpu->gpr[5];
	vcpu->arch.regs.gpr[6] = svcpu->gpr[6];
	vcpu->arch.regs.gpr[7] = svcpu->gpr[7];
	vcpu->arch.regs.gpr[8] = svcpu->gpr[8];
	vcpu->arch.regs.gpr[9] = svcpu->gpr[9];
	vcpu->arch.regs.gpr[10] = svcpu->gpr[10];
	vcpu->arch.regs.gpr[11] = svcpu->gpr[11];
	vcpu->arch.regs.gpr[12] = svcpu->gpr[12];
	vcpu->arch.regs.gpr[13] = svcpu->gpr[13];
	vcpu->arch.regs.ccr  = svcpu->cr;
	vcpu->arch.regs.xer = svcpu->xer;
	vcpu->arch.regs.ctr = svcpu->ctr;
	vcpu->arch.regs.link  = svcpu->lr;
	vcpu->arch.regs.nip  = svcpu->pc;
	vcpu->arch.shadow_srr1 = svcpu->shadow_srr1;
	vcpu->arch.fault_dar   = svcpu->fault_dar;
	vcpu->arch.fault_dsisr = svcpu->fault_dsisr;
	vcpu->arch.last_inst   = svcpu->last_inst;
#ifdef CONFIG_PPC_BOOK3S_64
	vcpu->arch.shadow_fscr = svcpu->shadow_fscr;
#endif
	/*
	 * Update purr and spurr using time base on exit.
	 */
	vcpu->arch.purr += get_tb() - vcpu->arch.entry_tb;
	vcpu->arch.spurr += get_tb() - vcpu->arch.entry_tb;
	to_book3s(vcpu)->vtb += get_vtb() - vcpu->arch.entry_vtb;
	if (cpu_has_feature(CPU_FTR_ARCH_207S))
		vcpu->arch.ic += mfspr(SPRN_IC) - vcpu->arch.entry_ic;

#ifdef CONFIG_PPC_TRANSACTIONAL_MEM
	/*
	 * Unlike other MSR bits, MSR[TS]bits can be changed at guest without
	 * notifying host:
	 *  modified by unprivileged instructions like "tbegin"/"tend"/
	 * "tresume"/"tsuspend" in PR KVM guest.
	 *
	 * It is necessary to sync here to calculate a correct shadow_msr.
	 *
	 * privileged guest's tbegin will be failed at present. So we
	 * only take care of problem state guest.
	 */
	old_msr = kvmppc_get_msr(vcpu);
	if (unlikely((old_msr & MSR_PR) &&
		(vcpu->arch.shadow_srr1 & (MSR_TS_MASK)) !=
				(old_msr & (MSR_TS_MASK)))) {
		old_msr &= ~(MSR_TS_MASK);
		old_msr |= (vcpu->arch.shadow_srr1 & (MSR_TS_MASK));
		kvmppc_set_msr_fast(vcpu, old_msr);
		kvmppc_recalc_shadow_msr(vcpu);
	}
#endif

	svcpu->in_use = false;

out:
	svcpu_put(svcpu);
}