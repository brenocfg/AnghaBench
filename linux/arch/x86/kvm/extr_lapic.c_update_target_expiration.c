#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int u64 ;
struct TYPE_2__ {int period; int /*<<< orphan*/  target_expiration; int /*<<< orphan*/  tscdeadline; } ;
struct kvm_lapic {int divide_count; TYPE_1__ lapic_timer; int /*<<< orphan*/  vcpu; } ;
typedef  scalar_t__ ktime_t ;

/* Variables and functions */
 int APIC_BUS_CYCLE_NS ; 
 int /*<<< orphan*/  APIC_TMICT ; 
 int /*<<< orphan*/  ktime_add_ns (scalar_t__,int) ; 
 scalar_t__ ktime_get () ; 
 scalar_t__ ktime_sub (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ ktime_to_ns (scalar_t__) ; 
 scalar_t__ kvm_lapic_get_reg (struct kvm_lapic*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  limit_periodic_timer_frequency (struct kvm_lapic*) ; 
 int mul_u64_u32_div (int,int,int /*<<< orphan*/ ) ; 
 scalar_t__ nsec_to_cycles (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void update_target_expiration(struct kvm_lapic *apic, uint32_t old_divisor)
{
	ktime_t now, remaining;
	u64 ns_remaining_old, ns_remaining_new;

	apic->lapic_timer.period = (u64)kvm_lapic_get_reg(apic, APIC_TMICT)
		* APIC_BUS_CYCLE_NS * apic->divide_count;
	limit_periodic_timer_frequency(apic);

	now = ktime_get();
	remaining = ktime_sub(apic->lapic_timer.target_expiration, now);
	if (ktime_to_ns(remaining) < 0)
		remaining = 0;

	ns_remaining_old = ktime_to_ns(remaining);
	ns_remaining_new = mul_u64_u32_div(ns_remaining_old,
	                                   apic->divide_count, old_divisor);

	apic->lapic_timer.tscdeadline +=
		nsec_to_cycles(apic->vcpu, ns_remaining_new) -
		nsec_to_cycles(apic->vcpu, ns_remaining_old);
	apic->lapic_timer.target_expiration = ktime_add_ns(now, ns_remaining_new);
}