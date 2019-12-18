#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_13__ {int exit_required; } ;
struct TYPE_9__ {int /*<<< orphan*/  payload; scalar_t__ has_payload; scalar_t__ nested_apf; } ;
struct TYPE_8__ {int /*<<< orphan*/  nested_apf_token; } ;
struct TYPE_12__ {int /*<<< orphan*/  cr2; TYPE_2__ exception; TYPE_1__ apf; } ;
struct TYPE_14__ {TYPE_5__ arch; } ;
struct vcpu_svm {TYPE_6__ nested; TYPE_7__ vcpu; TYPE_4__* vmcb; } ;
struct TYPE_10__ {unsigned int exit_code; int /*<<< orphan*/  exit_info_2; int /*<<< orphan*/  exit_info_1; scalar_t__ exit_code_hi; } ;
struct TYPE_11__ {TYPE_3__ control; } ;

/* Variables and functions */
 int NESTED_EXIT_DONE ; 
 unsigned int SVM_EXIT_EXCP_BASE ; 
 int /*<<< orphan*/  is_guest_mode (TYPE_7__*) ; 
 int nested_svm_intercept (struct vcpu_svm*) ; 

__attribute__((used)) static int nested_svm_check_exception(struct vcpu_svm *svm, unsigned nr,
				      bool has_error_code, u32 error_code)
{
	int vmexit;

	if (!is_guest_mode(&svm->vcpu))
		return 0;

	vmexit = nested_svm_intercept(svm);
	if (vmexit != NESTED_EXIT_DONE)
		return 0;

	svm->vmcb->control.exit_code = SVM_EXIT_EXCP_BASE + nr;
	svm->vmcb->control.exit_code_hi = 0;
	svm->vmcb->control.exit_info_1 = error_code;

	/*
	 * EXITINFO2 is undefined for all exception intercepts other
	 * than #PF.
	 */
	if (svm->vcpu.arch.exception.nested_apf)
		svm->vmcb->control.exit_info_2 = svm->vcpu.arch.apf.nested_apf_token;
	else if (svm->vcpu.arch.exception.has_payload)
		svm->vmcb->control.exit_info_2 = svm->vcpu.arch.exception.payload;
	else
		svm->vmcb->control.exit_info_2 = svm->vcpu.arch.cr2;

	svm->nested.exit_required = true;
	return vmexit;
}