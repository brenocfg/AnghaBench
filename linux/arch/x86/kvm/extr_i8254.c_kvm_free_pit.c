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
struct TYPE_3__ {int /*<<< orphan*/  timer; } ;
struct kvm_pit {int /*<<< orphan*/  irq_source_id; int /*<<< orphan*/  worker; TYPE_1__ pit_state; int /*<<< orphan*/  speaker_dev; int /*<<< orphan*/  dev; } ;
struct TYPE_4__ {struct kvm_pit* vpit; } ;
struct kvm {int /*<<< orphan*/  slots_lock; TYPE_2__ arch; } ;

/* Variables and functions */
 int /*<<< orphan*/  KVM_PIO_BUS ; 
 int /*<<< orphan*/  hrtimer_cancel (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct kvm_pit*) ; 
 int /*<<< orphan*/  kthread_destroy_worker (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvm_free_irq_source_id (struct kvm*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvm_io_bus_unregister_dev (struct kvm*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kvm_pit_set_reinject (struct kvm_pit*,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

void kvm_free_pit(struct kvm *kvm)
{
	struct kvm_pit *pit = kvm->arch.vpit;

	if (pit) {
		mutex_lock(&kvm->slots_lock);
		kvm_io_bus_unregister_dev(kvm, KVM_PIO_BUS, &pit->dev);
		kvm_io_bus_unregister_dev(kvm, KVM_PIO_BUS, &pit->speaker_dev);
		mutex_unlock(&kvm->slots_lock);
		kvm_pit_set_reinject(pit, false);
		hrtimer_cancel(&pit->pit_state.timer);
		kthread_destroy_worker(pit->worker);
		kvm_free_irq_source_id(kvm, pit->irq_source_id);
		kfree(pit);
	}
}