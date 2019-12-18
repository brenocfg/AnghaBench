#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {struct kvm_nested_guest* nested; } ;
struct kvm_vcpu {TYPE_1__ arch; } ;
struct kvm_run {int dummy; } ;
struct kvm_nested_guest {int /*<<< orphan*/  tlb_lock; } ;

/* Variables and functions */
 long __kvmhv_nested_page_fault (struct kvm_run*,struct kvm_vcpu*,struct kvm_nested_guest*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

long int kvmhv_nested_page_fault(struct kvm_run *run, struct kvm_vcpu *vcpu)
{
	struct kvm_nested_guest *gp = vcpu->arch.nested;
	long int ret;

	mutex_lock(&gp->tlb_lock);
	ret = __kvmhv_nested_page_fault(run, vcpu, gp);
	mutex_unlock(&gp->tlb_lock);
	return ret;
}