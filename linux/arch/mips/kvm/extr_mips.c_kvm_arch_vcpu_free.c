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
struct TYPE_2__ {struct kvm_vcpu* kseg0_commpage; struct kvm_vcpu* guest_ebase; int /*<<< orphan*/  comparecount_timer; } ;
struct kvm_vcpu {TYPE_1__ arch; } ;

/* Variables and functions */
 int /*<<< orphan*/  hrtimer_cancel (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  kvm_mips_dump_stats (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  kvm_mmu_free_memory_caches (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  kvm_vcpu_uninit (struct kvm_vcpu*) ; 

void kvm_arch_vcpu_free(struct kvm_vcpu *vcpu)
{
	hrtimer_cancel(&vcpu->arch.comparecount_timer);

	kvm_vcpu_uninit(vcpu);

	kvm_mips_dump_stats(vcpu);

	kvm_mmu_free_memory_caches(vcpu);
	kfree(vcpu->arch.guest_ebase);
	kfree(vcpu->arch.kseg0_commpage);
	kfree(vcpu);
}