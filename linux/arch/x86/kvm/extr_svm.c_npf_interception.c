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
typedef  int /*<<< orphan*/  u64 ;
struct vcpu_svm {TYPE_1__* vmcb; int /*<<< orphan*/  vcpu; } ;
struct TYPE_4__ {int /*<<< orphan*/  insn_len; int /*<<< orphan*/ * insn_bytes; int /*<<< orphan*/  exit_info_1; int /*<<< orphan*/  exit_info_2; } ;
struct TYPE_3__ {TYPE_2__ control; } ;

/* Variables and functions */
 int /*<<< orphan*/  X86_FEATURE_DECODEASSISTS ; 
 int /*<<< orphan*/  __sme_clr (int /*<<< orphan*/ ) ; 
 int kvm_mmu_page_fault (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ static_cpu_has (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_kvm_page_fault (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int npf_interception(struct vcpu_svm *svm)
{
	u64 fault_address = __sme_clr(svm->vmcb->control.exit_info_2);
	u64 error_code = svm->vmcb->control.exit_info_1;

	trace_kvm_page_fault(fault_address, error_code);
	return kvm_mmu_page_fault(&svm->vcpu, fault_address, error_code,
			static_cpu_has(X86_FEATURE_DECODEASSISTS) ?
			svm->vmcb->control.insn_bytes : NULL,
			svm->vmcb->control.insn_len);
}