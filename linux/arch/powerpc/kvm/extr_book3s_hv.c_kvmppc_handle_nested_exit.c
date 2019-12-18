#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int msr; } ;
struct TYPE_8__ {int trap; int fault_dsisr; TYPE_2__ shregs; int /*<<< orphan*/  fault_dar; int /*<<< orphan*/  mce_evt; } ;
struct TYPE_5__ {int /*<<< orphan*/  ext_intr_exits; int /*<<< orphan*/  dec_exits; int /*<<< orphan*/  sum_exits; } ;
struct kvm_vcpu {TYPE_4__ arch; TYPE_3__* kvm; TYPE_1__ stat; } ;
struct kvm_run {int dummy; } ;
struct TYPE_7__ {int /*<<< orphan*/  srcu; } ;

/* Variables and functions */
#define  BOOK3S_INTERRUPT_EXTERNAL 139 
#define  BOOK3S_INTERRUPT_HMI 138 
#define  BOOK3S_INTERRUPT_HV_DECREMENTER 137 
#define  BOOK3S_INTERRUPT_HV_RM_HARD 136 
#define  BOOK3S_INTERRUPT_HV_SOFTPATCH 135 
#define  BOOK3S_INTERRUPT_H_DATA_STORAGE 134 
#define  BOOK3S_INTERRUPT_H_DOORBELL 133 
#define  BOOK3S_INTERRUPT_H_INST_STORAGE 132 
#define  BOOK3S_INTERRUPT_H_VIRT 131 
#define  BOOK3S_INTERRUPT_MACHINE_CHECK 130 
#define  BOOK3S_INTERRUPT_PERFMON 129 
#define  BOOK3S_INTERRUPT_SYSTEM_RESET 128 
 int DSISR_ISSTORE ; 
 int DSISR_SRR1_MATCH_64S ; 
 int HSRR1_HISI_WRITE ; 
 int MSR_HV ; 
 int RESUME_GUEST ; 
 int RESUME_HOST ; 
 int kvmhv_nested_page_fault (struct kvm_run*,struct kvm_vcpu*) ; 
 int kvmhv_p9_tm_emulation (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  kvmppc_dump_regs (struct kvm_vcpu*) ; 
 int kvmppc_get_msr (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  kvmppc_get_pc (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  kvmppc_xics_rm_complete (struct kvm_vcpu*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  machine_check_print_event_info (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  pr_emerg (char*,...) ; 
 int srcu_read_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  srcu_read_unlock (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  xics_on_xive () ; 

__attribute__((used)) static int kvmppc_handle_nested_exit(struct kvm_run *run, struct kvm_vcpu *vcpu)
{
	int r;
	int srcu_idx;

	vcpu->stat.sum_exits++;

	/*
	 * This can happen if an interrupt occurs in the last stages
	 * of guest entry or the first stages of guest exit (i.e. after
	 * setting paca->kvm_hstate.in_guest to KVM_GUEST_MODE_GUEST_HV
	 * and before setting it to KVM_GUEST_MODE_HOST_HV).
	 * That can happen due to a bug, or due to a machine check
	 * occurring at just the wrong time.
	 */
	if (vcpu->arch.shregs.msr & MSR_HV) {
		pr_emerg("KVM trap in HV mode while nested!\n");
		pr_emerg("trap=0x%x | pc=0x%lx | msr=0x%llx\n",
			 vcpu->arch.trap, kvmppc_get_pc(vcpu),
			 vcpu->arch.shregs.msr);
		kvmppc_dump_regs(vcpu);
		return RESUME_HOST;
	}
	switch (vcpu->arch.trap) {
	/* We're good on these - the host merely wanted to get our attention */
	case BOOK3S_INTERRUPT_HV_DECREMENTER:
		vcpu->stat.dec_exits++;
		r = RESUME_GUEST;
		break;
	case BOOK3S_INTERRUPT_EXTERNAL:
		vcpu->stat.ext_intr_exits++;
		r = RESUME_HOST;
		break;
	case BOOK3S_INTERRUPT_H_DOORBELL:
	case BOOK3S_INTERRUPT_H_VIRT:
		vcpu->stat.ext_intr_exits++;
		r = RESUME_GUEST;
		break;
	/* SR/HMI/PMI are HV interrupts that host has handled. Resume guest.*/
	case BOOK3S_INTERRUPT_HMI:
	case BOOK3S_INTERRUPT_PERFMON:
	case BOOK3S_INTERRUPT_SYSTEM_RESET:
		r = RESUME_GUEST;
		break;
	case BOOK3S_INTERRUPT_MACHINE_CHECK:
		/* Pass the machine check to the L1 guest */
		r = RESUME_HOST;
		/* Print the MCE event to host console. */
		machine_check_print_event_info(&vcpu->arch.mce_evt, false, true);
		break;
	/*
	 * We get these next two if the guest accesses a page which it thinks
	 * it has mapped but which is not actually present, either because
	 * it is for an emulated I/O device or because the corresonding
	 * host page has been paged out.
	 */
	case BOOK3S_INTERRUPT_H_DATA_STORAGE:
		srcu_idx = srcu_read_lock(&vcpu->kvm->srcu);
		r = kvmhv_nested_page_fault(run, vcpu);
		srcu_read_unlock(&vcpu->kvm->srcu, srcu_idx);
		break;
	case BOOK3S_INTERRUPT_H_INST_STORAGE:
		vcpu->arch.fault_dar = kvmppc_get_pc(vcpu);
		vcpu->arch.fault_dsisr = kvmppc_get_msr(vcpu) &
					 DSISR_SRR1_MATCH_64S;
		if (vcpu->arch.shregs.msr & HSRR1_HISI_WRITE)
			vcpu->arch.fault_dsisr |= DSISR_ISSTORE;
		srcu_idx = srcu_read_lock(&vcpu->kvm->srcu);
		r = kvmhv_nested_page_fault(run, vcpu);
		srcu_read_unlock(&vcpu->kvm->srcu, srcu_idx);
		break;

#ifdef CONFIG_PPC_TRANSACTIONAL_MEM
	case BOOK3S_INTERRUPT_HV_SOFTPATCH:
		/*
		 * This occurs for various TM-related instructions that
		 * we need to emulate on POWER9 DD2.2.  We have already
		 * handled the cases where the guest was in real-suspend
		 * mode and was transitioning to transactional state.
		 */
		r = kvmhv_p9_tm_emulation(vcpu);
		break;
#endif

	case BOOK3S_INTERRUPT_HV_RM_HARD:
		vcpu->arch.trap = 0;
		r = RESUME_GUEST;
		if (!xics_on_xive())
			kvmppc_xics_rm_complete(vcpu, 0);
		break;
	default:
		r = RESUME_HOST;
		break;
	}

	return r;
}