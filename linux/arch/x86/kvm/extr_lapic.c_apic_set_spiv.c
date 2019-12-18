#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct kvm_lapic {int sw_enabled; TYPE_1__* vcpu; } ;
struct TYPE_5__ {int /*<<< orphan*/  key; } ;
struct TYPE_4__ {int /*<<< orphan*/  kvm; } ;

/* Variables and functions */
 int /*<<< orphan*/  APIC_SPIV ; 
 int APIC_SPIV_APIC_ENABLED ; 
 TYPE_2__ apic_sw_disabled ; 
 int /*<<< orphan*/  kvm_lapic_set_reg (struct kvm_lapic*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  recalculate_apic_map (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  static_key_slow_dec_deferred (TYPE_2__*) ; 
 int /*<<< orphan*/  static_key_slow_inc (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void apic_set_spiv(struct kvm_lapic *apic, u32 val)
{
	bool enabled = val & APIC_SPIV_APIC_ENABLED;

	kvm_lapic_set_reg(apic, APIC_SPIV, val);

	if (enabled != apic->sw_enabled) {
		apic->sw_enabled = enabled;
		if (enabled)
			static_key_slow_dec_deferred(&apic_sw_disabled);
		else
			static_key_slow_inc(&apic_sw_disabled.key);

		recalculate_apic_map(apic->vcpu->kvm);
	}
}