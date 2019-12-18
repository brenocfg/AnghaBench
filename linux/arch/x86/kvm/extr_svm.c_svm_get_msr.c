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
struct TYPE_6__ {int hsave_msr; int vm_cr_msr; } ;
struct vcpu_svm {int sysenter_eip; int sysenter_esp; int tsc_aux; int spec_ctrl; int virt_spec_ctrl; int msr_decfg; TYPE_3__ nested; TYPE_2__* vmcb; } ;
struct msr_data {int index; int data; int /*<<< orphan*/  host_initiated; } ;
struct kvm_vcpu {int dummy; } ;
struct TYPE_4__ {int star; int lstar; int cstar; int kernel_gs_base; int sfmask; int sysenter_cs; int dbgctl; int br_from; int br_to; int last_excp_from; int last_excp_to; } ;
struct TYPE_5__ {TYPE_1__ save; } ;

/* Variables and functions */
#define  MSR_AMD64_VIRT_SPEC_CTRL 147 
#define  MSR_CSTAR 146 
#define  MSR_F10H_DECFG 145 
#define  MSR_F15H_IC_CFG 144 
#define  MSR_IA32_DEBUGCTLMSR 143 
#define  MSR_IA32_LASTBRANCHFROMIP 142 
#define  MSR_IA32_LASTBRANCHTOIP 141 
#define  MSR_IA32_LASTINTFROMIP 140 
#define  MSR_IA32_LASTINTTOIP 139 
#define  MSR_IA32_SPEC_CTRL 138 
#define  MSR_IA32_SYSENTER_CS 137 
#define  MSR_IA32_SYSENTER_EIP 136 
#define  MSR_IA32_SYSENTER_ESP 135 
#define  MSR_KERNEL_GS_BASE 134 
#define  MSR_LSTAR 133 
#define  MSR_STAR 132 
#define  MSR_SYSCALL_MASK 131 
#define  MSR_TSC_AUX 130 
#define  MSR_VM_CR 129 
#define  MSR_VM_HSAVE_PA 128 
 int /*<<< orphan*/  X86_FEATURE_AMD_IBRS ; 
 int /*<<< orphan*/  X86_FEATURE_AMD_SSBD ; 
 int /*<<< orphan*/  X86_FEATURE_RDTSCP ; 
 int /*<<< orphan*/  X86_FEATURE_VIRT_SSBD ; 
 int /*<<< orphan*/  boot_cpu_has (int /*<<< orphan*/ ) ; 
 int guest_cpuid_family (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  guest_cpuid_has (struct kvm_vcpu*,int /*<<< orphan*/ ) ; 
 int guest_cpuid_model (struct kvm_vcpu*) ; 
 int kvm_get_msr_common (struct kvm_vcpu*,struct msr_data*) ; 
 struct vcpu_svm* to_svm (struct kvm_vcpu*) ; 

__attribute__((used)) static int svm_get_msr(struct kvm_vcpu *vcpu, struct msr_data *msr_info)
{
	struct vcpu_svm *svm = to_svm(vcpu);

	switch (msr_info->index) {
	case MSR_STAR:
		msr_info->data = svm->vmcb->save.star;
		break;
#ifdef CONFIG_X86_64
	case MSR_LSTAR:
		msr_info->data = svm->vmcb->save.lstar;
		break;
	case MSR_CSTAR:
		msr_info->data = svm->vmcb->save.cstar;
		break;
	case MSR_KERNEL_GS_BASE:
		msr_info->data = svm->vmcb->save.kernel_gs_base;
		break;
	case MSR_SYSCALL_MASK:
		msr_info->data = svm->vmcb->save.sfmask;
		break;
#endif
	case MSR_IA32_SYSENTER_CS:
		msr_info->data = svm->vmcb->save.sysenter_cs;
		break;
	case MSR_IA32_SYSENTER_EIP:
		msr_info->data = svm->sysenter_eip;
		break;
	case MSR_IA32_SYSENTER_ESP:
		msr_info->data = svm->sysenter_esp;
		break;
	case MSR_TSC_AUX:
		if (!boot_cpu_has(X86_FEATURE_RDTSCP))
			return 1;
		msr_info->data = svm->tsc_aux;
		break;
	/*
	 * Nobody will change the following 5 values in the VMCB so we can
	 * safely return them on rdmsr. They will always be 0 until LBRV is
	 * implemented.
	 */
	case MSR_IA32_DEBUGCTLMSR:
		msr_info->data = svm->vmcb->save.dbgctl;
		break;
	case MSR_IA32_LASTBRANCHFROMIP:
		msr_info->data = svm->vmcb->save.br_from;
		break;
	case MSR_IA32_LASTBRANCHTOIP:
		msr_info->data = svm->vmcb->save.br_to;
		break;
	case MSR_IA32_LASTINTFROMIP:
		msr_info->data = svm->vmcb->save.last_excp_from;
		break;
	case MSR_IA32_LASTINTTOIP:
		msr_info->data = svm->vmcb->save.last_excp_to;
		break;
	case MSR_VM_HSAVE_PA:
		msr_info->data = svm->nested.hsave_msr;
		break;
	case MSR_VM_CR:
		msr_info->data = svm->nested.vm_cr_msr;
		break;
	case MSR_IA32_SPEC_CTRL:
		if (!msr_info->host_initiated &&
		    !guest_cpuid_has(vcpu, X86_FEATURE_AMD_IBRS) &&
		    !guest_cpuid_has(vcpu, X86_FEATURE_AMD_SSBD))
			return 1;

		msr_info->data = svm->spec_ctrl;
		break;
	case MSR_AMD64_VIRT_SPEC_CTRL:
		if (!msr_info->host_initiated &&
		    !guest_cpuid_has(vcpu, X86_FEATURE_VIRT_SSBD))
			return 1;

		msr_info->data = svm->virt_spec_ctrl;
		break;
	case MSR_F15H_IC_CFG: {

		int family, model;

		family = guest_cpuid_family(vcpu);
		model  = guest_cpuid_model(vcpu);

		if (family < 0 || model < 0)
			return kvm_get_msr_common(vcpu, msr_info);

		msr_info->data = 0;

		if (family == 0x15 &&
		    (model >= 0x2 && model < 0x20))
			msr_info->data = 0x1E;
		}
		break;
	case MSR_F10H_DECFG:
		msr_info->data = svm->msr_decfg;
		break;
	default:
		return kvm_get_msr_common(vcpu, msr_info);
	}
	return 0;
}