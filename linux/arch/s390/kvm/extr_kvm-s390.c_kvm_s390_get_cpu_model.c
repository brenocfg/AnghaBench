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
struct kvm_device_attr {int attr; } ;
struct kvm {int dummy; } ;

/* Variables and functions */
 int ENXIO ; 
#define  KVM_S390_VM_CPU_MACHINE 133 
#define  KVM_S390_VM_CPU_MACHINE_FEAT 132 
#define  KVM_S390_VM_CPU_MACHINE_SUBFUNC 131 
#define  KVM_S390_VM_CPU_PROCESSOR 130 
#define  KVM_S390_VM_CPU_PROCESSOR_FEAT 129 
#define  KVM_S390_VM_CPU_PROCESSOR_SUBFUNC 128 
 int kvm_s390_get_machine (struct kvm*,struct kvm_device_attr*) ; 
 int kvm_s390_get_machine_feat (struct kvm*,struct kvm_device_attr*) ; 
 int kvm_s390_get_machine_subfunc (struct kvm*,struct kvm_device_attr*) ; 
 int kvm_s390_get_processor (struct kvm*,struct kvm_device_attr*) ; 
 int kvm_s390_get_processor_feat (struct kvm*,struct kvm_device_attr*) ; 
 int kvm_s390_get_processor_subfunc (struct kvm*,struct kvm_device_attr*) ; 

__attribute__((used)) static int kvm_s390_get_cpu_model(struct kvm *kvm, struct kvm_device_attr *attr)
{
	int ret = -ENXIO;

	switch (attr->attr) {
	case KVM_S390_VM_CPU_PROCESSOR:
		ret = kvm_s390_get_processor(kvm, attr);
		break;
	case KVM_S390_VM_CPU_MACHINE:
		ret = kvm_s390_get_machine(kvm, attr);
		break;
	case KVM_S390_VM_CPU_PROCESSOR_FEAT:
		ret = kvm_s390_get_processor_feat(kvm, attr);
		break;
	case KVM_S390_VM_CPU_MACHINE_FEAT:
		ret = kvm_s390_get_machine_feat(kvm, attr);
		break;
	case KVM_S390_VM_CPU_PROCESSOR_SUBFUNC:
		ret = kvm_s390_get_processor_subfunc(kvm, attr);
		break;
	case KVM_S390_VM_CPU_MACHINE_SUBFUNC:
		ret = kvm_s390_get_machine_subfunc(kvm, attr);
		break;
	}
	return ret;
}