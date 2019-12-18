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
struct vcpu_svm {int /*<<< orphan*/  vcpu; TYPE_2__* vmcb; } ;
struct TYPE_3__ {int /*<<< orphan*/  exit_info_1; } ;
struct TYPE_4__ {TYPE_1__ control; } ;

/* Variables and functions */
 int /*<<< orphan*/  X86_FEATURE_DECODEASSISTS ; 
 int kvm_emulate_instruction (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvm_mmu_invlpg (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int kvm_skip_emulated_instruction (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  static_cpu_has (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int invlpg_interception(struct vcpu_svm *svm)
{
	if (!static_cpu_has(X86_FEATURE_DECODEASSISTS))
		return kvm_emulate_instruction(&svm->vcpu, 0);

	kvm_mmu_invlpg(&svm->vcpu, svm->vmcb->control.exit_info_1);
	return kvm_skip_emulated_instruction(&svm->vcpu);
}