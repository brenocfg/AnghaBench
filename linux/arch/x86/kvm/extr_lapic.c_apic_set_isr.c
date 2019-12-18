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
struct kvm_lapic {scalar_t__ isr_count; int highest_isr_cache; struct kvm_vcpu* vcpu; scalar_t__ regs; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* hwapic_isr_update ) (struct kvm_vcpu*,int) ;} ;

/* Variables and functions */
 scalar_t__ APIC_ISR ; 
 int /*<<< orphan*/  BUG_ON (int) ; 
 scalar_t__ MAX_APIC_VECTOR ; 
 scalar_t__ __apic_test_and_set_vector (int,scalar_t__) ; 
 TYPE_2__* kvm_x86_ops ; 
 int /*<<< orphan*/  stub1 (struct kvm_vcpu*,int) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void apic_set_isr(int vec, struct kvm_lapic *apic)
{
	struct kvm_vcpu *vcpu;

	if (__apic_test_and_set_vector(vec, apic->regs + APIC_ISR))
		return;

	vcpu = apic->vcpu;

	/*
	 * With APIC virtualization enabled, all caching is disabled
	 * because the processor can modify ISR under the hood.  Instead
	 * just set SVI.
	 */
	if (unlikely(vcpu->arch.apicv_active))
		kvm_x86_ops->hwapic_isr_update(vcpu, vec);
	else {
		++apic->isr_count;
		BUG_ON(apic->isr_count > MAX_APIC_VECTOR);
		/*
		 * ISR (in service register) bit is set when injecting an interrupt.
		 * The highest vector is injected. Thus the latest bit set matches
		 * the highest bit in ISR.
		 */
		apic->highest_isr_cache = vec;
	}
}