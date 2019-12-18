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
typedef  int /*<<< orphan*/  u64 ;
struct TYPE_2__ {scalar_t__ tscdeadline; int /*<<< orphan*/  target_expiration; int /*<<< orphan*/  period; } ;
struct kvm_lapic {int /*<<< orphan*/  vcpu; TYPE_1__ lapic_timer; } ;
typedef  int /*<<< orphan*/  ktime_t ;

/* Variables and functions */
 int /*<<< orphan*/  ktime_add_ns (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ktime_get () ; 
 int /*<<< orphan*/  ktime_sub (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ kvm_read_l1_tsc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ nsec_to_cycles (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rdtsc () ; 

__attribute__((used)) static void advance_periodic_target_expiration(struct kvm_lapic *apic)
{
	ktime_t now = ktime_get();
	u64 tscl = rdtsc();
	ktime_t delta;

	/*
	 * Synchronize both deadlines to the same time source or
	 * differences in the periods (caused by differences in the
	 * underlying clocks or numerical approximation errors) will
	 * cause the two to drift apart over time as the errors
	 * accumulate.
	 */
	apic->lapic_timer.target_expiration =
		ktime_add_ns(apic->lapic_timer.target_expiration,
				apic->lapic_timer.period);
	delta = ktime_sub(apic->lapic_timer.target_expiration, now);
	apic->lapic_timer.tscdeadline = kvm_read_l1_tsc(apic->vcpu, tscl) +
		nsec_to_cycles(apic->vcpu, delta);
}