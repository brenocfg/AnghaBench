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
struct vmcb {int dummy; } ;
struct vcpu_svm {int /*<<< orphan*/  vcpu; TYPE_2__* vmcb; } ;
struct kvm_host_map {struct vmcb* hva; } ;
struct TYPE_3__ {int /*<<< orphan*/  rax; } ;
struct TYPE_4__ {TYPE_1__ save; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  gpa_to_gfn (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvm_inject_gp (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int kvm_skip_emulated_instruction (int /*<<< orphan*/ *) ; 
 int kvm_vcpu_map (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct kvm_host_map*) ; 
 int /*<<< orphan*/  kvm_vcpu_unmap (int /*<<< orphan*/ *,struct kvm_host_map*,int) ; 
 scalar_t__ nested_svm_check_permissions (struct vcpu_svm*) ; 
 int /*<<< orphan*/  nested_svm_vmloadsave (TYPE_2__*,struct vmcb*) ; 

__attribute__((used)) static int vmsave_interception(struct vcpu_svm *svm)
{
	struct vmcb *nested_vmcb;
	struct kvm_host_map map;
	int ret;

	if (nested_svm_check_permissions(svm))
		return 1;

	ret = kvm_vcpu_map(&svm->vcpu, gpa_to_gfn(svm->vmcb->save.rax), &map);
	if (ret) {
		if (ret == -EINVAL)
			kvm_inject_gp(&svm->vcpu, 0);
		return 1;
	}

	nested_vmcb = map.hva;

	ret = kvm_skip_emulated_instruction(&svm->vcpu);

	nested_svm_vmloadsave(svm->vmcb, nested_vmcb);
	kvm_vcpu_unmap(&svm->vcpu, &map, true);

	return ret;
}