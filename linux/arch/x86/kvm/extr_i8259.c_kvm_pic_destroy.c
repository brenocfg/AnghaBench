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
struct kvm_pic {int /*<<< orphan*/  dev_eclr; int /*<<< orphan*/  kvm; int /*<<< orphan*/  dev_slave; int /*<<< orphan*/  dev_master; } ;
struct TYPE_2__ {struct kvm_pic* vpic; } ;
struct kvm {TYPE_1__ arch; int /*<<< orphan*/  slots_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  KVM_PIO_BUS ; 
 int /*<<< orphan*/  kfree (struct kvm_pic*) ; 
 int /*<<< orphan*/  kvm_io_bus_unregister_dev (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

void kvm_pic_destroy(struct kvm *kvm)
{
	struct kvm_pic *vpic = kvm->arch.vpic;

	if (!vpic)
		return;

	mutex_lock(&kvm->slots_lock);
	kvm_io_bus_unregister_dev(vpic->kvm, KVM_PIO_BUS, &vpic->dev_master);
	kvm_io_bus_unregister_dev(vpic->kvm, KVM_PIO_BUS, &vpic->dev_slave);
	kvm_io_bus_unregister_dev(vpic->kvm, KVM_PIO_BUS, &vpic->dev_eclr);
	mutex_unlock(&kvm->slots_lock);

	kvm->arch.vpic = NULL;
	kfree(vpic);
}