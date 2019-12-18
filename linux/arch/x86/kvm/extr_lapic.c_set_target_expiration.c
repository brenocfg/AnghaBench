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
typedef  int u64 ;
struct TYPE_2__ {int period; int /*<<< orphan*/  target_expiration; scalar_t__ tscdeadline; } ;
struct kvm_lapic {int divide_count; TYPE_1__ lapic_timer; int /*<<< orphan*/  vcpu; } ;
typedef  int /*<<< orphan*/  ktime_t ;

/* Variables and functions */
 int APIC_BUS_CYCLE_NS ; 
 int /*<<< orphan*/  APIC_TMICT ; 
 int /*<<< orphan*/  ktime_add_ns (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ktime_get () ; 
 scalar_t__ kvm_lapic_get_reg (struct kvm_lapic*,int /*<<< orphan*/ ) ; 
 scalar_t__ kvm_read_l1_tsc (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  limit_periodic_timer_frequency (struct kvm_lapic*) ; 
 scalar_t__ nsec_to_cycles (int /*<<< orphan*/ ,int) ; 
 int rdtsc () ; 

__attribute__((used)) static bool set_target_expiration(struct kvm_lapic *apic)
{
	ktime_t now;
	u64 tscl = rdtsc();

	now = ktime_get();
	apic->lapic_timer.period = (u64)kvm_lapic_get_reg(apic, APIC_TMICT)
		* APIC_BUS_CYCLE_NS * apic->divide_count;

	if (!apic->lapic_timer.period) {
		apic->lapic_timer.tscdeadline = 0;
		return false;
	}

	limit_periodic_timer_frequency(apic);

	apic->lapic_timer.tscdeadline = kvm_read_l1_tsc(apic->vcpu, tscl) +
		nsec_to_cycles(apic->vcpu, apic->lapic_timer.period);
	apic->lapic_timer.target_expiration = ktime_add_ns(now, apic->lapic_timer.period);

	return true;
}