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
struct mm_struct {int dummy; } ;
struct TYPE_3__ {struct mm_struct guest_user_mm; struct mm_struct guest_kernel_mm; } ;
struct kvm_vcpu {TYPE_1__ arch; } ;
struct TYPE_4__ {int flags; } ;

/* Variables and functions */
 scalar_t__ KVM_GUEST_KERNEL_MODE (struct kvm_vcpu*) ; 
 int PF_VCPU ; 
 int /*<<< orphan*/  check_switch_mmu_context (struct mm_struct*) ; 
 TYPE_2__* current ; 
 int /*<<< orphan*/  ehb () ; 
 int /*<<< orphan*/  kvm_mips_suspend_mm (int) ; 

__attribute__((used)) static int kvm_trap_emul_vcpu_load(struct kvm_vcpu *vcpu, int cpu)
{
	struct mm_struct *kern_mm = &vcpu->arch.guest_kernel_mm;
	struct mm_struct *user_mm = &vcpu->arch.guest_user_mm;
	struct mm_struct *mm;

	/*
	 * Were we in guest context? If so, restore the appropriate ASID based
	 * on the mode of the Guest (Kernel/User).
	 */
	if (current->flags & PF_VCPU) {
		mm = KVM_GUEST_KERNEL_MODE(vcpu) ? kern_mm : user_mm;
		check_switch_mmu_context(mm);
		kvm_mips_suspend_mm(cpu);
		ehb();
	}

	return 0;
}