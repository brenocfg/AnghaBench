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
struct TYPE_2__ {int /*<<< orphan*/  asid_flush_mask; } ;
struct kvm {TYPE_1__ arch; } ;

/* Variables and functions */
 scalar_t__ cpu_has_guestid ; 
 int /*<<< orphan*/  cpumask_setall (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kvm_flush_remote_tlbs (struct kvm*) ; 

__attribute__((used)) static void kvm_vz_flush_shadow_all(struct kvm *kvm)
{
	if (cpu_has_guestid) {
		/* Flush GuestID for each VCPU individually */
		kvm_flush_remote_tlbs(kvm);
	} else {
		/*
		 * For each CPU there is a single GPA ASID used by all VCPUs in
		 * the VM, so it doesn't make sense for the VCPUs to handle
		 * invalidation of these ASIDs individually.
		 *
		 * Instead mark all CPUs as needing ASID invalidation in
		 * asid_flush_mask, and just use kvm_flush_remote_tlbs(kvm) to
		 * kick any running VCPUs so they check asid_flush_mask.
		 */
		cpumask_setall(&kvm->arch.asid_flush_mask);
		kvm_flush_remote_tlbs(kvm);
	}
}