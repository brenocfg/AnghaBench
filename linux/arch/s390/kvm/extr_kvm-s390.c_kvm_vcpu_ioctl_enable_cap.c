#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct kvm_vcpu {TYPE_2__* kvm; } ;
struct kvm_enable_cap {int cap; scalar_t__ flags; } ;
struct TYPE_4__ {int css_support; } ;
struct TYPE_5__ {TYPE_1__ arch; } ;

/* Variables and functions */
 int EINVAL ; 
#define  KVM_CAP_S390_CSS_SUPPORT 128 
 int /*<<< orphan*/  VM_EVENT (TYPE_2__*,int,char*,char*) ; 
 int /*<<< orphan*/  trace_kvm_s390_enable_css (TYPE_2__*) ; 

__attribute__((used)) static int kvm_vcpu_ioctl_enable_cap(struct kvm_vcpu *vcpu,
				     struct kvm_enable_cap *cap)
{
	int r;

	if (cap->flags)
		return -EINVAL;

	switch (cap->cap) {
	case KVM_CAP_S390_CSS_SUPPORT:
		if (!vcpu->kvm->arch.css_support) {
			vcpu->kvm->arch.css_support = 1;
			VM_EVENT(vcpu->kvm, 3, "%s", "ENABLE: CSS support");
			trace_kvm_s390_enable_css(vcpu->kvm);
		}
		r = 0;
		break;
	default:
		r = -EINVAL;
		break;
	}
	return r;
}