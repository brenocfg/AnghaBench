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
struct kvm_vcpu {TYPE_2__* kvm; } ;
struct kvm_ioapic {int /*<<< orphan*/  lock; } ;
struct TYPE_3__ {struct kvm_ioapic* vioapic; } ;
struct TYPE_4__ {TYPE_1__ arch; } ;

/* Variables and functions */
 int /*<<< orphan*/  __rtc_irq_eoi_tracking_restore_one (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

void kvm_rtc_eoi_tracking_restore_one(struct kvm_vcpu *vcpu)
{
	struct kvm_ioapic *ioapic = vcpu->kvm->arch.vioapic;

	spin_lock(&ioapic->lock);
	__rtc_irq_eoi_tracking_restore_one(vcpu);
	spin_unlock(&ioapic->lock);
}