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
struct kvm_vcpu {struct kvm* kvm; } ;
struct kvm_nested_guest {int dummy; } ;
struct TYPE_2__ {int max_nested_lpid; struct kvm_nested_guest** nested_guests; } ;
struct kvm {int /*<<< orphan*/  mmu_lock; TYPE_1__ arch; } ;

/* Variables and functions */
 int /*<<< orphan*/  kvmhv_emulate_tlbie_lpid (struct kvm_vcpu*,struct kvm_nested_guest*,int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void kvmhv_emulate_tlbie_all_lpid(struct kvm_vcpu *vcpu, int ric)
{
	struct kvm *kvm = vcpu->kvm;
	struct kvm_nested_guest *gp;
	int i;

	spin_lock(&kvm->mmu_lock);
	for (i = 0; i <= kvm->arch.max_nested_lpid; i++) {
		gp = kvm->arch.nested_guests[i];
		if (gp) {
			spin_unlock(&kvm->mmu_lock);
			kvmhv_emulate_tlbie_lpid(vcpu, gp, ric);
			spin_lock(&kvm->mmu_lock);
		}
	}
	spin_unlock(&kvm->mmu_lock);
}