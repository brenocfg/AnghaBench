#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct kvm_lapic_irq {int dummy; } ;
struct kvm_kernel_irq_routing_entry {int dummy; } ;
struct kvm {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int kvm_irq_delivery_to_apic (struct kvm*,int /*<<< orphan*/ *,struct kvm_lapic_irq*,int /*<<< orphan*/ *) ; 
 scalar_t__ kvm_msi_route_invalid (struct kvm*,struct kvm_kernel_irq_routing_entry*) ; 
 int /*<<< orphan*/  kvm_set_msi_irq (struct kvm*,struct kvm_kernel_irq_routing_entry*,struct kvm_lapic_irq*) ; 

int kvm_set_msi(struct kvm_kernel_irq_routing_entry *e,
		struct kvm *kvm, int irq_source_id, int level, bool line_status)
{
	struct kvm_lapic_irq irq;

	if (kvm_msi_route_invalid(kvm, e))
		return -EINVAL;

	if (!level)
		return -1;

	kvm_set_msi_irq(kvm, e, &irq);

	return kvm_irq_delivery_to_apic(kvm, NULL, &irq, NULL);
}