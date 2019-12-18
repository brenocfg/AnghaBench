#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct vcpu_svm {int nmi_singlestep_guest_rflags; int /*<<< orphan*/  vcpu; int /*<<< orphan*/  nmi_singlestep; } ;

/* Variables and functions */
 unsigned long DR6_BS ; 
 int NESTED_EXIT_DONE ; 
 int NESTED_EXIT_HOST ; 
 int X86_EFLAGS_TF ; 
 int /*<<< orphan*/  disable_nmi_singlestep (struct vcpu_svm*) ; 
 scalar_t__ kvm_get_dr (int /*<<< orphan*/ *,int,unsigned long*) ; 

__attribute__((used)) static int nested_svm_intercept_db(struct vcpu_svm *svm)
{
	unsigned long dr6;

	/* if we're not singlestepping, it's not ours */
	if (!svm->nmi_singlestep)
		return NESTED_EXIT_DONE;

	/* if it's not a singlestep exception, it's not ours */
	if (kvm_get_dr(&svm->vcpu, 6, &dr6))
		return NESTED_EXIT_DONE;
	if (!(dr6 & DR6_BS))
		return NESTED_EXIT_DONE;

	/* if the guest is singlestepping, it should get the vmexit */
	if (svm->nmi_singlestep_guest_rflags & X86_EFLAGS_TF) {
		disable_nmi_singlestep(svm);
		return NESTED_EXIT_DONE;
	}

	/* it's ours, the nested hypervisor must not see this one */
	return NESTED_EXIT_HOST;
}