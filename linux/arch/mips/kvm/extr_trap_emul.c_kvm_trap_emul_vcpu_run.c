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
struct TYPE_3__ {int (* vcpu_run ) (struct kvm_run*,struct kvm_vcpu*) ;int /*<<< orphan*/  cop0; } ;
struct kvm_vcpu {TYPE_1__ arch; } ;
struct kvm_run {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  mm; } ;

/* Variables and functions */
 int /*<<< orphan*/  check_switch_mmu_context (int /*<<< orphan*/ ) ; 
 TYPE_2__* current ; 
 int /*<<< orphan*/  htw_start () ; 
 int /*<<< orphan*/  htw_stop () ; 
 int /*<<< orphan*/  kvm_mips_deliver_interrupts (struct kvm_vcpu*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvm_mips_resume_mm (int) ; 
 int /*<<< orphan*/  kvm_mips_suspend_mm (int) ; 
 int /*<<< orphan*/  kvm_read_c0_guest_cause (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvm_trap_emul_vcpu_reenter (struct kvm_run*,struct kvm_vcpu*) ; 
 int /*<<< orphan*/  pagefault_disable () ; 
 int /*<<< orphan*/  pagefault_enable () ; 
 int smp_processor_id () ; 
 int stub1 (struct kvm_run*,struct kvm_vcpu*) ; 

__attribute__((used)) static int kvm_trap_emul_vcpu_run(struct kvm_run *run, struct kvm_vcpu *vcpu)
{
	int cpu = smp_processor_id();
	int r;

	/* Check if we have any exceptions/interrupts pending */
	kvm_mips_deliver_interrupts(vcpu,
				    kvm_read_c0_guest_cause(vcpu->arch.cop0));

	kvm_trap_emul_vcpu_reenter(run, vcpu);

	/*
	 * We use user accessors to access guest memory, but we don't want to
	 * invoke Linux page faulting.
	 */
	pagefault_disable();

	/* Disable hardware page table walking while in guest */
	htw_stop();

	/*
	 * While in guest context we're in the guest's address space, not the
	 * host process address space, so we need to be careful not to confuse
	 * e.g. cache management IPIs.
	 */
	kvm_mips_suspend_mm(cpu);

	r = vcpu->arch.vcpu_run(run, vcpu);

	/* We may have migrated while handling guest exits */
	cpu = smp_processor_id();

	/* Restore normal Linux process memory map */
	check_switch_mmu_context(current->mm);
	kvm_mips_resume_mm(cpu);

	htw_start();

	pagefault_enable();

	return r;
}