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
struct TYPE_2__ {int /*<<< orphan*/  guest_mmu; int /*<<< orphan*/  root_mmu; } ;
struct kvm_vcpu {TYPE_1__ arch; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_mmu_pages (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kvm_mmu_unload (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  mmu_free_memory_caches (struct kvm_vcpu*) ; 

void kvm_mmu_destroy(struct kvm_vcpu *vcpu)
{
	kvm_mmu_unload(vcpu);
	free_mmu_pages(&vcpu->arch.root_mmu);
	free_mmu_pages(&vcpu->arch.guest_mmu);
	mmu_free_memory_caches(vcpu);
}