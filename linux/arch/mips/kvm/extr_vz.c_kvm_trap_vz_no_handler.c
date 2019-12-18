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
typedef  int u32 ;
struct TYPE_4__ {int host_cp0_cause; unsigned long host_cp0_badvaddr; scalar_t__ pc; } ;
struct kvm_vcpu {TYPE_1__* run; TYPE_2__ arch; } ;
struct TYPE_3__ {int /*<<< orphan*/  exit_reason; } ;

/* Variables and functions */
 int CAUSEB_EXCCODE ; 
 int CAUSEF_BD ; 
 int CAUSEF_EXCCODE ; 
 int /*<<< orphan*/  KVM_EXIT_INTERNAL_ERROR ; 
 int RESUME_HOST ; 
 int /*<<< orphan*/  kvm_arch_vcpu_dump_regs (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  kvm_err (char*,int,int*,int,unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvm_get_badinstr (int*,struct kvm_vcpu*,int*) ; 
 int /*<<< orphan*/  read_gc0_status () ; 

__attribute__((used)) static int kvm_trap_vz_no_handler(struct kvm_vcpu *vcpu)
{
	u32 *opc = (u32 *) vcpu->arch.pc;
	u32 cause = vcpu->arch.host_cp0_cause;
	u32 exccode = (cause & CAUSEF_EXCCODE) >> CAUSEB_EXCCODE;
	unsigned long badvaddr = vcpu->arch.host_cp0_badvaddr;
	u32 inst = 0;

	/*
	 *  Fetch the instruction.
	 */
	if (cause & CAUSEF_BD)
		opc += 1;
	kvm_get_badinstr(opc, vcpu, &inst);

	kvm_err("Exception Code: %d not handled @ PC: %p, inst: 0x%08x BadVaddr: %#lx Status: %#x\n",
		exccode, opc, inst, badvaddr,
		read_gc0_status());
	kvm_arch_vcpu_dump_regs(vcpu);
	vcpu->run->exit_reason = KVM_EXIT_INTERNAL_ERROR;
	return RESUME_HOST;
}