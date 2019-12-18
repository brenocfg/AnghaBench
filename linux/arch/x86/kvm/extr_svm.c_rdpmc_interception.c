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
struct vcpu_svm {int /*<<< orphan*/  vcpu; } ;

/* Variables and functions */
 int emulate_on_interception (struct vcpu_svm*) ; 
 int kvm_complete_insn_gp (int /*<<< orphan*/ *,int) ; 
 int kvm_rdpmc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nrips ; 

__attribute__((used)) static int rdpmc_interception(struct vcpu_svm *svm)
{
	int err;

	if (!nrips)
		return emulate_on_interception(svm);

	err = kvm_rdpmc(&svm->vcpu);
	return kvm_complete_insn_gp(&svm->vcpu, err);
}