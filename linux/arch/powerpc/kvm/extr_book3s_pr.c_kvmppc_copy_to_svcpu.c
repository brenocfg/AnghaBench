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
struct kvmppc_book3s_shadow_vcpu {int in_use; int /*<<< orphan*/  shadow_fscr; int /*<<< orphan*/  pc; int /*<<< orphan*/  lr; int /*<<< orphan*/  ctr; int /*<<< orphan*/  xer; int /*<<< orphan*/  cr; int /*<<< orphan*/ * gpr; } ;
struct TYPE_3__ {int /*<<< orphan*/  nip; int /*<<< orphan*/  link; int /*<<< orphan*/  ctr; int /*<<< orphan*/  xer; int /*<<< orphan*/  ccr; int /*<<< orphan*/ * gpr; } ;
struct TYPE_4__ {int /*<<< orphan*/  entry_ic; int /*<<< orphan*/  entry_vtb; int /*<<< orphan*/  entry_tb; int /*<<< orphan*/  shadow_fscr; TYPE_1__ regs; } ;
struct kvm_vcpu {TYPE_2__ arch; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPU_FTR_ARCH_207S ; 
 int /*<<< orphan*/  SPRN_IC ; 
 scalar_t__ cpu_has_feature (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_tb () ; 
 int /*<<< orphan*/  get_vtb () ; 
 int /*<<< orphan*/  mfspr (int /*<<< orphan*/ ) ; 
 struct kvmppc_book3s_shadow_vcpu* svcpu_get (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  svcpu_put (struct kvmppc_book3s_shadow_vcpu*) ; 

void kvmppc_copy_to_svcpu(struct kvm_vcpu *vcpu)
{
	struct kvmppc_book3s_shadow_vcpu *svcpu = svcpu_get(vcpu);

	svcpu->gpr[0] = vcpu->arch.regs.gpr[0];
	svcpu->gpr[1] = vcpu->arch.regs.gpr[1];
	svcpu->gpr[2] = vcpu->arch.regs.gpr[2];
	svcpu->gpr[3] = vcpu->arch.regs.gpr[3];
	svcpu->gpr[4] = vcpu->arch.regs.gpr[4];
	svcpu->gpr[5] = vcpu->arch.regs.gpr[5];
	svcpu->gpr[6] = vcpu->arch.regs.gpr[6];
	svcpu->gpr[7] = vcpu->arch.regs.gpr[7];
	svcpu->gpr[8] = vcpu->arch.regs.gpr[8];
	svcpu->gpr[9] = vcpu->arch.regs.gpr[9];
	svcpu->gpr[10] = vcpu->arch.regs.gpr[10];
	svcpu->gpr[11] = vcpu->arch.regs.gpr[11];
	svcpu->gpr[12] = vcpu->arch.regs.gpr[12];
	svcpu->gpr[13] = vcpu->arch.regs.gpr[13];
	svcpu->cr  = vcpu->arch.regs.ccr;
	svcpu->xer = vcpu->arch.regs.xer;
	svcpu->ctr = vcpu->arch.regs.ctr;
	svcpu->lr  = vcpu->arch.regs.link;
	svcpu->pc  = vcpu->arch.regs.nip;
#ifdef CONFIG_PPC_BOOK3S_64
	svcpu->shadow_fscr = vcpu->arch.shadow_fscr;
#endif
	/*
	 * Now also save the current time base value. We use this
	 * to find the guest purr and spurr value.
	 */
	vcpu->arch.entry_tb = get_tb();
	vcpu->arch.entry_vtb = get_vtb();
	if (cpu_has_feature(CPU_FTR_ARCH_207S))
		vcpu->arch.entry_ic = mfspr(SPRN_IC);
	svcpu->in_use = true;

	svcpu_put(svcpu);
}