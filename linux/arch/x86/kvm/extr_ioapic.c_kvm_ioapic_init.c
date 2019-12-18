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
struct kvm_ioapic {int /*<<< orphan*/  dev; int /*<<< orphan*/  base_address; struct kvm* kvm; int /*<<< orphan*/  eoi_inject; int /*<<< orphan*/  lock; } ;
struct TYPE_2__ {struct kvm_ioapic* vioapic; } ;
struct kvm {TYPE_1__ arch; int /*<<< orphan*/  slots_lock; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL_ACCOUNT ; 
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IOAPIC_MEM_LENGTH ; 
 int /*<<< orphan*/  KVM_MMIO_BUS ; 
 int /*<<< orphan*/  ioapic_mmio_ops ; 
 int /*<<< orphan*/  kfree (struct kvm_ioapic*) ; 
 int kvm_io_bus_register_dev (struct kvm*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kvm_ioapic_eoi_inject_work ; 
 int /*<<< orphan*/  kvm_ioapic_reset (struct kvm_ioapic*) ; 
 int /*<<< orphan*/  kvm_iodevice_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct kvm_ioapic* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

int kvm_ioapic_init(struct kvm *kvm)
{
	struct kvm_ioapic *ioapic;
	int ret;

	ioapic = kzalloc(sizeof(struct kvm_ioapic), GFP_KERNEL_ACCOUNT);
	if (!ioapic)
		return -ENOMEM;
	spin_lock_init(&ioapic->lock);
	INIT_DELAYED_WORK(&ioapic->eoi_inject, kvm_ioapic_eoi_inject_work);
	kvm->arch.vioapic = ioapic;
	kvm_ioapic_reset(ioapic);
	kvm_iodevice_init(&ioapic->dev, &ioapic_mmio_ops);
	ioapic->kvm = kvm;
	mutex_lock(&kvm->slots_lock);
	ret = kvm_io_bus_register_dev(kvm, KVM_MMIO_BUS, ioapic->base_address,
				      IOAPIC_MEM_LENGTH, &ioapic->dev);
	mutex_unlock(&kvm->slots_lock);
	if (ret < 0) {
		kvm->arch.vioapic = NULL;
		kfree(ioapic);
	}

	return ret;
}