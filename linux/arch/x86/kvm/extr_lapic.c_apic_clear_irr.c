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
struct TYPE_3__ {int /*<<< orphan*/  apicv_active; } ;
struct kvm_vcpu {TYPE_1__ arch; } ;
struct kvm_lapic {int irr_pending; scalar_t__ regs; struct kvm_vcpu* vcpu; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* hwapic_irr_update ) (struct kvm_vcpu*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 scalar_t__ APIC_IRR ; 
 int /*<<< orphan*/  apic_find_highest_irr (struct kvm_lapic*) ; 
 int apic_search_irr (struct kvm_lapic*) ; 
 int /*<<< orphan*/  kvm_lapic_clear_vector (int,scalar_t__) ; 
 TYPE_2__* kvm_x86_ops ; 
 int /*<<< orphan*/  stub1 (struct kvm_vcpu*,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void apic_clear_irr(int vec, struct kvm_lapic *apic)
{
	struct kvm_vcpu *vcpu;

	vcpu = apic->vcpu;

	if (unlikely(vcpu->arch.apicv_active)) {
		/* need to update RVI */
		kvm_lapic_clear_vector(vec, apic->regs + APIC_IRR);
		kvm_x86_ops->hwapic_irr_update(vcpu,
				apic_find_highest_irr(apic));
	} else {
		apic->irr_pending = false;
		kvm_lapic_clear_vector(vec, apic->regs + APIC_IRR);
		if (apic_search_irr(apic) != -1)
			apic->irr_pending = true;
	}
}