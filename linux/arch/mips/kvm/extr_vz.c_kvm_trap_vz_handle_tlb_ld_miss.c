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
union mips_instruction {int /*<<< orphan*/  word; } ;
typedef  int /*<<< orphan*/  ulong ;
typedef  int u32 ;
struct TYPE_2__ {int host_cp0_cause; int /*<<< orphan*/  host_cp0_badvaddr; scalar_t__ pc; } ;
struct kvm_vcpu {TYPE_1__ arch; struct kvm_run* run; } ;
struct kvm_run {void* exit_reason; } ;
typedef  enum emulation_result { ____Placeholder_emulation_result } emulation_result ;

/* Variables and functions */
 int CAUSEF_BD ; 
 int EMULATE_DONE ; 
 int EMULATE_DO_MMIO ; 
 int EMULATE_FAIL ; 
 void* KVM_EXIT_INTERNAL_ERROR ; 
 void* KVM_EXIT_MMIO ; 
 int RESUME_GUEST ; 
 int RESUME_HOST ; 
 int /*<<< orphan*/  kvm_err (char*,int*,int /*<<< orphan*/ ) ; 
 int kvm_get_badinstr (int*,struct kvm_vcpu*,int /*<<< orphan*/ *) ; 
 scalar_t__ kvm_is_ifetch_fault (TYPE_1__*) ; 
 int kvm_mips_emulate_load (union mips_instruction,int,struct kvm_run*,struct kvm_vcpu*) ; 
 scalar_t__ kvm_mips_handle_vz_root_tlb_fault (int /*<<< orphan*/ ,struct kvm_vcpu*,int) ; 

__attribute__((used)) static int kvm_trap_vz_handle_tlb_ld_miss(struct kvm_vcpu *vcpu)
{
	struct kvm_run *run = vcpu->run;
	u32 *opc = (u32 *) vcpu->arch.pc;
	u32 cause = vcpu->arch.host_cp0_cause;
	ulong badvaddr = vcpu->arch.host_cp0_badvaddr;
	union mips_instruction inst;
	enum emulation_result er = EMULATE_DONE;
	int err, ret = RESUME_GUEST;

	if (kvm_mips_handle_vz_root_tlb_fault(badvaddr, vcpu, false)) {
		/* A code fetch fault doesn't count as an MMIO */
		if (kvm_is_ifetch_fault(&vcpu->arch)) {
			run->exit_reason = KVM_EXIT_INTERNAL_ERROR;
			return RESUME_HOST;
		}

		/* Fetch the instruction */
		if (cause & CAUSEF_BD)
			opc += 1;
		err = kvm_get_badinstr(opc, vcpu, &inst.word);
		if (err) {
			run->exit_reason = KVM_EXIT_INTERNAL_ERROR;
			return RESUME_HOST;
		}

		/* Treat as MMIO */
		er = kvm_mips_emulate_load(inst, cause, run, vcpu);
		if (er == EMULATE_FAIL) {
			kvm_err("Guest Emulate Load from MMIO space failed: PC: %p, BadVaddr: %#lx\n",
				opc, badvaddr);
			run->exit_reason = KVM_EXIT_INTERNAL_ERROR;
		}
	}

	if (er == EMULATE_DONE) {
		ret = RESUME_GUEST;
	} else if (er == EMULATE_DO_MMIO) {
		run->exit_reason = KVM_EXIT_MMIO;
		ret = RESUME_HOST;
	} else {
		run->exit_reason = KVM_EXIT_INTERNAL_ERROR;
		ret = RESUME_HOST;
	}
	return ret;
}