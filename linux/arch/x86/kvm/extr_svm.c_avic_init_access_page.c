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
struct TYPE_2__ {int apic_access_page_done; } ;
struct kvm {int /*<<< orphan*/  slots_lock; TYPE_1__ arch; } ;

/* Variables and functions */
 int /*<<< orphan*/  APIC_ACCESS_PAGE_PRIVATE_MEMSLOT ; 
 int /*<<< orphan*/  APIC_DEFAULT_PHYS_BASE ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int __x86_set_memory_region (struct kvm*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int avic_init_access_page(struct kvm_vcpu *vcpu)
{
	struct kvm *kvm = vcpu->kvm;
	int ret = 0;

	mutex_lock(&kvm->slots_lock);
	if (kvm->arch.apic_access_page_done)
		goto out;

	ret = __x86_set_memory_region(kvm,
				      APIC_ACCESS_PAGE_PRIVATE_MEMSLOT,
				      APIC_DEFAULT_PHYS_BASE,
				      PAGE_SIZE);
	if (ret)
		goto out;

	kvm->arch.apic_access_page_done = true;
out:
	mutex_unlock(&kvm->slots_lock);
	return ret;
}