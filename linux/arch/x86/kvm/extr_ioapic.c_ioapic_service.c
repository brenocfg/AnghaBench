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
struct TYPE_4__ {scalar_t__ trig_mode; int remote_irr; int delivery_mode; int /*<<< orphan*/  dest_mode; int /*<<< orphan*/  vector; int /*<<< orphan*/  dest_id; scalar_t__ mask; } ;
union kvm_ioapic_redirect_entry {TYPE_2__ fields; } ;
struct kvm_lapic_irq {scalar_t__ trig_mode; int delivery_mode; int level; int msi_redir_hint; scalar_t__ shorthand; int /*<<< orphan*/  dest_mode; int /*<<< orphan*/  vector; int /*<<< orphan*/  dest_id; } ;
struct TYPE_3__ {int pending_eoi; int /*<<< orphan*/  dest_map; } ;
struct kvm_ioapic {int irr_delivered; int /*<<< orphan*/  kvm; TYPE_1__ rtc_status; union kvm_ioapic_redirect_entry* redirtbl; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 scalar_t__ IOAPIC_EDGE_TRIG ; 
 scalar_t__ IOAPIC_LEVEL_TRIG ; 
 int RTC_GSI ; 
 int kvm_irq_delivery_to_apic (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct kvm_lapic_irq*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ioapic_service(struct kvm_ioapic *ioapic, int irq, bool line_status)
{
	union kvm_ioapic_redirect_entry *entry = &ioapic->redirtbl[irq];
	struct kvm_lapic_irq irqe;
	int ret;

	if (entry->fields.mask ||
	    (entry->fields.trig_mode == IOAPIC_LEVEL_TRIG &&
	    entry->fields.remote_irr))
		return -1;

	irqe.dest_id = entry->fields.dest_id;
	irqe.vector = entry->fields.vector;
	irqe.dest_mode = entry->fields.dest_mode;
	irqe.trig_mode = entry->fields.trig_mode;
	irqe.delivery_mode = entry->fields.delivery_mode << 8;
	irqe.level = 1;
	irqe.shorthand = 0;
	irqe.msi_redir_hint = false;

	if (irqe.trig_mode == IOAPIC_EDGE_TRIG)
		ioapic->irr_delivered |= 1 << irq;

	if (irq == RTC_GSI && line_status) {
		/*
		 * pending_eoi cannot ever become negative (see
		 * rtc_status_pending_eoi_check_valid) and the caller
		 * ensures that it is only called if it is >= zero, namely
		 * if rtc_irq_check_coalesced returns false).
		 */
		BUG_ON(ioapic->rtc_status.pending_eoi != 0);
		ret = kvm_irq_delivery_to_apic(ioapic->kvm, NULL, &irqe,
					       &ioapic->rtc_status.dest_map);
		ioapic->rtc_status.pending_eoi = (ret < 0 ? 0 : ret);
	} else
		ret = kvm_irq_delivery_to_apic(ioapic->kvm, NULL, &irqe, NULL);

	if (ret && irqe.trig_mode == IOAPIC_LEVEL_TRIG)
		entry->fields.remote_irr = 1;

	return ret;
}