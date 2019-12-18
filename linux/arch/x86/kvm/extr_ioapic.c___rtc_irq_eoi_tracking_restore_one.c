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
struct TYPE_7__ {int /*<<< orphan*/  vector; int /*<<< orphan*/  dest_mode; int /*<<< orphan*/  dest_id; } ;
union kvm_ioapic_redirect_entry {TYPE_3__ fields; } ;
struct kvm_vcpu {size_t vcpu_id; TYPE_2__* kvm; } ;
struct dest_map {int /*<<< orphan*/  map; int /*<<< orphan*/ * vectors; } ;
struct TYPE_8__ {int /*<<< orphan*/  pending_eoi; struct dest_map dest_map; } ;
struct kvm_ioapic {TYPE_4__ rtc_status; union kvm_ioapic_redirect_entry* redirtbl; } ;
struct TYPE_5__ {struct kvm_ioapic* vioapic; } ;
struct TYPE_6__ {TYPE_1__ arch; } ;

/* Variables and functions */
 size_t RTC_GSI ; 
 int /*<<< orphan*/  __clear_bit (size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __set_bit (size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvm_apic_match_dest (struct kvm_vcpu*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int kvm_apic_pending_eoi (struct kvm_vcpu*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtc_status_pending_eoi_check_valid (struct kvm_ioapic*) ; 
 int test_bit (size_t,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void __rtc_irq_eoi_tracking_restore_one(struct kvm_vcpu *vcpu)
{
	bool new_val, old_val;
	struct kvm_ioapic *ioapic = vcpu->kvm->arch.vioapic;
	struct dest_map *dest_map = &ioapic->rtc_status.dest_map;
	union kvm_ioapic_redirect_entry *e;

	e = &ioapic->redirtbl[RTC_GSI];
	if (!kvm_apic_match_dest(vcpu, NULL, 0,	e->fields.dest_id,
				e->fields.dest_mode))
		return;

	new_val = kvm_apic_pending_eoi(vcpu, e->fields.vector);
	old_val = test_bit(vcpu->vcpu_id, dest_map->map);

	if (new_val == old_val)
		return;

	if (new_val) {
		__set_bit(vcpu->vcpu_id, dest_map->map);
		dest_map->vectors[vcpu->vcpu_id] = e->fields.vector;
		ioapic->rtc_status.pending_eoi++;
	} else {
		__clear_bit(vcpu->vcpu_id, dest_map->map);
		ioapic->rtc_status.pending_eoi--;
		rtc_status_pending_eoi_check_valid(ioapic);
	}
}