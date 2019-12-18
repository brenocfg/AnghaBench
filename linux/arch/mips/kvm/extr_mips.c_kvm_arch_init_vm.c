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
struct TYPE_3__ {int /*<<< orphan*/  pgd; } ;
struct TYPE_4__ {TYPE_1__ gpa_mm; } ;
struct kvm {TYPE_2__ arch; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
#define  KVM_VM_MIPS_TE 129 
#define  KVM_VM_MIPS_VZ 128 
 int /*<<< orphan*/  kvm_pgd_alloc () ; 

int kvm_arch_init_vm(struct kvm *kvm, unsigned long type)
{
	switch (type) {
#ifdef CONFIG_KVM_MIPS_VZ
	case KVM_VM_MIPS_VZ:
#else
	case KVM_VM_MIPS_TE:
#endif
		break;
	default:
		/* Unsupported KVM type */
		return -EINVAL;
	};

	/* Allocate page table to map GPA -> RPA */
	kvm->arch.gpa_mm.pgd = kvm_pgd_alloc();
	if (!kvm->arch.gpa_mm.pgd)
		return -ENOMEM;

	return 0;
}