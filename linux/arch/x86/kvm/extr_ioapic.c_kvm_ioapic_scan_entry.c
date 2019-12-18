#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ trig_mode; int /*<<< orphan*/  vector; int /*<<< orphan*/  dest_mode; int /*<<< orphan*/  dest_id; } ;
union kvm_ioapic_redirect_entry {TYPE_4__ fields; } ;
typedef  int /*<<< orphan*/  ulong ;
struct kvm_vcpu {size_t vcpu_id; TYPE_2__* kvm; } ;
struct dest_map {int /*<<< orphan*/ * vectors; int /*<<< orphan*/  map; } ;
struct TYPE_7__ {struct dest_map dest_map; } ;
struct kvm_ioapic {int /*<<< orphan*/  lock; int /*<<< orphan*/  kvm; union kvm_ioapic_redirect_entry* redirtbl; TYPE_3__ rtc_status; } ;
struct TYPE_5__ {struct kvm_ioapic* vioapic; } ;
struct TYPE_6__ {TYPE_1__ arch; } ;

/* Variables and functions */
 scalar_t__ IOAPIC_LEVEL_TRIG ; 
 int IOAPIC_NUM_PINS ; 
 int /*<<< orphan*/  KVM_IRQCHIP_IOAPIC ; 
 int RTC_GSI ; 
 int /*<<< orphan*/  __set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ kvm_apic_match_dest (struct kvm_vcpu*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ kvm_apic_pending_eoi (struct kvm_vcpu*,int /*<<< orphan*/ ) ; 
 scalar_t__ kvm_irq_has_notifier (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (size_t,int /*<<< orphan*/ ) ; 

void kvm_ioapic_scan_entry(struct kvm_vcpu *vcpu, ulong *ioapic_handled_vectors)
{
	struct kvm_ioapic *ioapic = vcpu->kvm->arch.vioapic;
	struct dest_map *dest_map = &ioapic->rtc_status.dest_map;
	union kvm_ioapic_redirect_entry *e;
	int index;

	spin_lock(&ioapic->lock);

	/* Make sure we see any missing RTC EOI */
	if (test_bit(vcpu->vcpu_id, dest_map->map))
		__set_bit(dest_map->vectors[vcpu->vcpu_id],
			  ioapic_handled_vectors);

	for (index = 0; index < IOAPIC_NUM_PINS; index++) {
		e = &ioapic->redirtbl[index];
		if (e->fields.trig_mode == IOAPIC_LEVEL_TRIG ||
		    kvm_irq_has_notifier(ioapic->kvm, KVM_IRQCHIP_IOAPIC, index) ||
		    index == RTC_GSI) {
			if (kvm_apic_match_dest(vcpu, NULL, 0,
			             e->fields.dest_id, e->fields.dest_mode) ||
			    kvm_apic_pending_eoi(vcpu, e->fields.vector))
				__set_bit(e->fields.vector,
					  ioapic_handled_vectors);
		}
	}
	spin_unlock(&ioapic->lock);
}