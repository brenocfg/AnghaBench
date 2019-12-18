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
struct kvm_device_attr {int attr; scalar_t__ flags; } ;
struct kvm {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENXIO ; 
#define  KVM_S390_VM_TOD_EXT 130 
#define  KVM_S390_VM_TOD_HIGH 129 
#define  KVM_S390_VM_TOD_LOW 128 
 int kvm_s390_set_tod_ext (struct kvm*,struct kvm_device_attr*) ; 
 int kvm_s390_set_tod_high (struct kvm*,struct kvm_device_attr*) ; 
 int kvm_s390_set_tod_low (struct kvm*,struct kvm_device_attr*) ; 

__attribute__((used)) static int kvm_s390_set_tod(struct kvm *kvm, struct kvm_device_attr *attr)
{
	int ret;

	if (attr->flags)
		return -EINVAL;

	switch (attr->attr) {
	case KVM_S390_VM_TOD_EXT:
		ret = kvm_s390_set_tod_ext(kvm, attr);
		break;
	case KVM_S390_VM_TOD_HIGH:
		ret = kvm_s390_set_tod_high(kvm, attr);
		break;
	case KVM_S390_VM_TOD_LOW:
		ret = kvm_s390_set_tod_low(kvm, attr);
		break;
	default:
		ret = -ENXIO;
		break;
	}
	return ret;
}