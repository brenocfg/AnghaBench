#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_9__ ;
typedef  struct TYPE_17__   TYPE_8__ ;
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_14__ {void* event_exit_inst_len; } ;
struct TYPE_15__ {TYPE_5__ arch; } ;
struct TYPE_12__ {scalar_t__ vm86_active; } ;
struct vcpu_vmx {int idt_vectoring_info; int exit_intr_info; TYPE_6__ vcpu; TYPE_3__ rmode; } ;
struct TYPE_11__ {int /*<<< orphan*/  host_apf_reason; } ;
struct TYPE_13__ {unsigned long dr6; TYPE_2__ apf; } ;
struct kvm_vcpu {int guest_debug; TYPE_4__ arch; struct kvm_run* run; } ;
struct TYPE_18__ {int exception; int error_code; } ;
struct TYPE_16__ {unsigned long dr6; unsigned long dr7; unsigned long pc; int exception; } ;
struct TYPE_17__ {TYPE_7__ arch; } ;
struct TYPE_10__ {int ndata; int* data; int /*<<< orphan*/  suberror; } ;
struct kvm_run {TYPE_9__ ex; int /*<<< orphan*/  exit_reason; TYPE_8__ debug; TYPE_1__ internal; } ;

/* Variables and functions */
#define  AC_VECTOR 130 
#define  BP_VECTOR 129 
#define  DB_VECTOR 128 
 unsigned long DR6_FIXED_1 ; 
 unsigned long DR6_RTM ; 
 unsigned long DR_TRAP_BITS ; 
 int /*<<< orphan*/  EMULTYPE_VMWARE_GP ; 
 int /*<<< orphan*/  EXIT_QUALIFICATION ; 
 int const GP_VECTOR ; 
 int /*<<< orphan*/  GUEST_CS_BASE ; 
 int /*<<< orphan*/  GUEST_DR7 ; 
 int INTR_INFO_DELIVER_CODE_MASK ; 
 int INTR_INFO_VECTOR_MASK ; 
 int /*<<< orphan*/  KVM_EXIT_DEBUG ; 
 int /*<<< orphan*/  KVM_EXIT_EXCEPTION ; 
 int /*<<< orphan*/  KVM_EXIT_INTERNAL_ERROR ; 
 int KVM_GUESTDBG_SINGLESTEP ; 
 int KVM_GUESTDBG_USE_HW_BP ; 
 int /*<<< orphan*/  KVM_INTERNAL_ERROR_SIMUL_EX ; 
 int PFERR_RSVD_MASK ; 
 int VECTORING_INFO_VALID_MASK ; 
 int /*<<< orphan*/  VM_EXIT_INSTRUCTION_LEN ; 
 int /*<<< orphan*/  VM_EXIT_INTR_ERROR_CODE ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 scalar_t__ enable_ept ; 
 int /*<<< orphan*/  enable_vmware_backdoor ; 
 int handle_rmode_exception (struct kvm_vcpu*,int,int) ; 
 int handle_ud (struct kvm_vcpu*) ; 
 scalar_t__ is_gp_fault (int) ; 
 int /*<<< orphan*/  is_icebp (int) ; 
 scalar_t__ is_invalid_opcode (int) ; 
 scalar_t__ is_machine_check (int) ; 
 scalar_t__ is_nmi (int) ; 
 scalar_t__ is_page_fault (int) ; 
 int kvm_emulate_instruction (struct kvm_vcpu*,int /*<<< orphan*/ ) ; 
 int kvm_handle_page_fault (struct kvm_vcpu*,int,unsigned long,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvm_queue_exception (struct kvm_vcpu*,int const) ; 
 int /*<<< orphan*/  kvm_queue_exception_e (struct kvm_vcpu*,int const,int) ; 
 unsigned long kvm_rip_read (struct kvm_vcpu*) ; 
 scalar_t__ rmode_exception (struct kvm_vcpu*,int) ; 
 int /*<<< orphan*/  skip_emulated_instruction (struct kvm_vcpu*) ; 
 struct vcpu_vmx* to_vmx (struct kvm_vcpu*) ; 
 void* vmcs_read32 (int /*<<< orphan*/ ) ; 
 unsigned long vmcs_readl (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int handle_exception_nmi(struct kvm_vcpu *vcpu)
{
	struct vcpu_vmx *vmx = to_vmx(vcpu);
	struct kvm_run *kvm_run = vcpu->run;
	u32 intr_info, ex_no, error_code;
	unsigned long cr2, rip, dr6;
	u32 vect_info;

	vect_info = vmx->idt_vectoring_info;
	intr_info = vmx->exit_intr_info;

	if (is_machine_check(intr_info) || is_nmi(intr_info))
		return 1; /* handled by handle_exception_nmi_irqoff() */

	if (is_invalid_opcode(intr_info))
		return handle_ud(vcpu);

	error_code = 0;
	if (intr_info & INTR_INFO_DELIVER_CODE_MASK)
		error_code = vmcs_read32(VM_EXIT_INTR_ERROR_CODE);

	if (!vmx->rmode.vm86_active && is_gp_fault(intr_info)) {
		WARN_ON_ONCE(!enable_vmware_backdoor);

		/*
		 * VMware backdoor emulation on #GP interception only handles
		 * IN{S}, OUT{S}, and RDPMC, none of which generate a non-zero
		 * error code on #GP.
		 */
		if (error_code) {
			kvm_queue_exception_e(vcpu, GP_VECTOR, error_code);
			return 1;
		}
		return kvm_emulate_instruction(vcpu, EMULTYPE_VMWARE_GP);
	}

	/*
	 * The #PF with PFEC.RSVD = 1 indicates the guest is accessing
	 * MMIO, it is better to report an internal error.
	 * See the comments in vmx_handle_exit.
	 */
	if ((vect_info & VECTORING_INFO_VALID_MASK) &&
	    !(is_page_fault(intr_info) && !(error_code & PFERR_RSVD_MASK))) {
		vcpu->run->exit_reason = KVM_EXIT_INTERNAL_ERROR;
		vcpu->run->internal.suberror = KVM_INTERNAL_ERROR_SIMUL_EX;
		vcpu->run->internal.ndata = 3;
		vcpu->run->internal.data[0] = vect_info;
		vcpu->run->internal.data[1] = intr_info;
		vcpu->run->internal.data[2] = error_code;
		return 0;
	}

	if (is_page_fault(intr_info)) {
		cr2 = vmcs_readl(EXIT_QUALIFICATION);
		/* EPT won't cause page fault directly */
		WARN_ON_ONCE(!vcpu->arch.apf.host_apf_reason && enable_ept);
		return kvm_handle_page_fault(vcpu, error_code, cr2, NULL, 0);
	}

	ex_no = intr_info & INTR_INFO_VECTOR_MASK;

	if (vmx->rmode.vm86_active && rmode_exception(vcpu, ex_no))
		return handle_rmode_exception(vcpu, ex_no, error_code);

	switch (ex_no) {
	case AC_VECTOR:
		kvm_queue_exception_e(vcpu, AC_VECTOR, error_code);
		return 1;
	case DB_VECTOR:
		dr6 = vmcs_readl(EXIT_QUALIFICATION);
		if (!(vcpu->guest_debug &
		      (KVM_GUESTDBG_SINGLESTEP | KVM_GUESTDBG_USE_HW_BP))) {
			vcpu->arch.dr6 &= ~DR_TRAP_BITS;
			vcpu->arch.dr6 |= dr6 | DR6_RTM;
			if (is_icebp(intr_info))
				WARN_ON(!skip_emulated_instruction(vcpu));

			kvm_queue_exception(vcpu, DB_VECTOR);
			return 1;
		}
		kvm_run->debug.arch.dr6 = dr6 | DR6_FIXED_1;
		kvm_run->debug.arch.dr7 = vmcs_readl(GUEST_DR7);
		/* fall through */
	case BP_VECTOR:
		/*
		 * Update instruction length as we may reinject #BP from
		 * user space while in guest debugging mode. Reading it for
		 * #DB as well causes no harm, it is not used in that case.
		 */
		vmx->vcpu.arch.event_exit_inst_len =
			vmcs_read32(VM_EXIT_INSTRUCTION_LEN);
		kvm_run->exit_reason = KVM_EXIT_DEBUG;
		rip = kvm_rip_read(vcpu);
		kvm_run->debug.arch.pc = vmcs_readl(GUEST_CS_BASE) + rip;
		kvm_run->debug.arch.exception = ex_no;
		break;
	default:
		kvm_run->exit_reason = KVM_EXIT_EXCEPTION;
		kvm_run->ex.exception = ex_no;
		kvm_run->ex.error_code = error_code;
		break;
	}
	return 0;
}