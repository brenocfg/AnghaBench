#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  u32 ;
typedef  scalar_t__ u16 ;
struct TYPE_8__ {int nmi_injected; } ;
struct TYPE_11__ {TYPE_1__ arch; } ;
struct vcpu_svm {TYPE_4__ vcpu; TYPE_3__* vmcb; } ;
struct TYPE_9__ {int exit_int_info; unsigned long long exit_info_2; scalar_t__ exit_info_1; } ;
struct TYPE_10__ {TYPE_2__ control; } ;

/* Variables and functions */
 int BP_VECTOR ; 
 int OF_VECTOR ; 
 int SVM_EVTINJ_VEC_MASK ; 
 unsigned long long SVM_EXITINFOSHIFT_TS_HAS_ERROR_CODE ; 
 unsigned long long SVM_EXITINFOSHIFT_TS_REASON_IRET ; 
 unsigned long long SVM_EXITINFOSHIFT_TS_REASON_JMP ; 
#define  SVM_EXITINTINFO_TYPE_EXEPT 130 
#define  SVM_EXITINTINFO_TYPE_INTR 129 
 int SVM_EXITINTINFO_TYPE_MASK ; 
#define  SVM_EXITINTINFO_TYPE_NMI 128 
 int SVM_EXITINTINFO_TYPE_SOFT ; 
 int SVM_EXITINTINFO_VALID ; 
 int TASK_SWITCH_CALL ; 
 int TASK_SWITCH_GATE ; 
 int TASK_SWITCH_IRET ; 
 int TASK_SWITCH_JMP ; 
 int /*<<< orphan*/  kvm_clear_exception_queue (TYPE_4__*) ; 
 int /*<<< orphan*/  kvm_clear_interrupt_queue (TYPE_4__*) ; 
 int kvm_task_switch (TYPE_4__*,scalar_t__,int,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skip_emulated_instruction (TYPE_4__*) ; 

__attribute__((used)) static int task_switch_interception(struct vcpu_svm *svm)
{
	u16 tss_selector;
	int reason;
	int int_type = svm->vmcb->control.exit_int_info &
		SVM_EXITINTINFO_TYPE_MASK;
	int int_vec = svm->vmcb->control.exit_int_info & SVM_EVTINJ_VEC_MASK;
	uint32_t type =
		svm->vmcb->control.exit_int_info & SVM_EXITINTINFO_TYPE_MASK;
	uint32_t idt_v =
		svm->vmcb->control.exit_int_info & SVM_EXITINTINFO_VALID;
	bool has_error_code = false;
	u32 error_code = 0;

	tss_selector = (u16)svm->vmcb->control.exit_info_1;

	if (svm->vmcb->control.exit_info_2 &
	    (1ULL << SVM_EXITINFOSHIFT_TS_REASON_IRET))
		reason = TASK_SWITCH_IRET;
	else if (svm->vmcb->control.exit_info_2 &
		 (1ULL << SVM_EXITINFOSHIFT_TS_REASON_JMP))
		reason = TASK_SWITCH_JMP;
	else if (idt_v)
		reason = TASK_SWITCH_GATE;
	else
		reason = TASK_SWITCH_CALL;

	if (reason == TASK_SWITCH_GATE) {
		switch (type) {
		case SVM_EXITINTINFO_TYPE_NMI:
			svm->vcpu.arch.nmi_injected = false;
			break;
		case SVM_EXITINTINFO_TYPE_EXEPT:
			if (svm->vmcb->control.exit_info_2 &
			    (1ULL << SVM_EXITINFOSHIFT_TS_HAS_ERROR_CODE)) {
				has_error_code = true;
				error_code =
					(u32)svm->vmcb->control.exit_info_2;
			}
			kvm_clear_exception_queue(&svm->vcpu);
			break;
		case SVM_EXITINTINFO_TYPE_INTR:
			kvm_clear_interrupt_queue(&svm->vcpu);
			break;
		default:
			break;
		}
	}

	if (reason != TASK_SWITCH_GATE ||
	    int_type == SVM_EXITINTINFO_TYPE_SOFT ||
	    (int_type == SVM_EXITINTINFO_TYPE_EXEPT &&
	     (int_vec == OF_VECTOR || int_vec == BP_VECTOR))) {
		if (!skip_emulated_instruction(&svm->vcpu))
			return 0;
	}

	if (int_type != SVM_EXITINTINFO_TYPE_SOFT)
		int_vec = -1;

	return kvm_task_switch(&svm->vcpu, tss_selector, int_vec, reason,
			       has_error_code, error_code);
}