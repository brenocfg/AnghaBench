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
struct kvm {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  irqchip_split (struct kvm*) ; 
 int /*<<< orphan*/  kvm_make_scan_ioapic_request (struct kvm*) ; 

void kvm_arch_post_irq_routing_update(struct kvm *kvm)
{
	if (!irqchip_split(kvm))
		return;
	kvm_make_scan_ioapic_request(kvm);
}