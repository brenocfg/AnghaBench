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
struct vcpu_svm {TYPE_2__* vmcb; } ;
struct kvm_vcpu {int dummy; } ;
struct TYPE_3__ {unsigned long dr6; } ;
struct TYPE_4__ {TYPE_1__ save; } ;

/* Variables and functions */
 int /*<<< orphan*/  VMCB_DR ; 
 int /*<<< orphan*/  mark_dirty (TYPE_2__*,int /*<<< orphan*/ ) ; 
 struct vcpu_svm* to_svm (struct kvm_vcpu*) ; 

__attribute__((used)) static void svm_set_dr6(struct kvm_vcpu *vcpu, unsigned long value)
{
	struct vcpu_svm *svm = to_svm(vcpu);

	svm->vmcb->save.dr6 = value;
	mark_dirty(svm->vmcb, VMCB_DR);
}