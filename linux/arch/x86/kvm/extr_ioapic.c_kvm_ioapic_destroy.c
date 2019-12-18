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
struct kvm_ioapic {int /*<<< orphan*/  dev; int /*<<< orphan*/  eoi_inject; } ;
struct TYPE_2__ {struct kvm_ioapic* vioapic; } ;
struct kvm {TYPE_1__ arch; int /*<<< orphan*/  slots_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  KVM_MMIO_BUS ; 
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct kvm_ioapic*) ; 
 int /*<<< orphan*/  kvm_io_bus_unregister_dev (struct kvm*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

void kvm_ioapic_destroy(struct kvm *kvm)
{
	struct kvm_ioapic *ioapic = kvm->arch.vioapic;

	if (!ioapic)
		return;

	cancel_delayed_work_sync(&ioapic->eoi_inject);
	mutex_lock(&kvm->slots_lock);
	kvm_io_bus_unregister_dev(kvm, KVM_MMIO_BUS, &ioapic->dev);
	mutex_unlock(&kvm->slots_lock);
	kvm->arch.vioapic = NULL;
	kfree(ioapic);
}