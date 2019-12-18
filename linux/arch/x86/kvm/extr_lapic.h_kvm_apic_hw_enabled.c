#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct kvm_lapic {TYPE_2__* vcpu; } ;
struct TYPE_6__ {int /*<<< orphan*/  key; } ;
struct TYPE_4__ {int apic_base; } ;
struct TYPE_5__ {TYPE_1__ arch; } ;

/* Variables and functions */
 int MSR_IA32_APICBASE_ENABLE ; 
 TYPE_3__ apic_hw_disabled ; 
 scalar_t__ static_key_false (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline int kvm_apic_hw_enabled(struct kvm_lapic *apic)
{
	if (static_key_false(&apic_hw_disabled.key))
		return apic->vcpu->arch.apic_base & MSR_IA32_APICBASE_ENABLE;
	return MSR_IA32_APICBASE_ENABLE;
}