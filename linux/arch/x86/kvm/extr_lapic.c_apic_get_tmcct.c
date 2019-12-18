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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {int /*<<< orphan*/  period; int /*<<< orphan*/  target_expiration; } ;
struct kvm_lapic {int divide_count; TYPE_1__ lapic_timer; } ;
typedef  int /*<<< orphan*/  s64 ;
typedef  scalar_t__ ktime_t ;

/* Variables and functions */
 int APIC_BUS_CYCLE_NS ; 
 int /*<<< orphan*/  APIC_TMICT ; 
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  div64_u64 (int /*<<< orphan*/ ,int) ; 
 scalar_t__ ktime_get () ; 
 scalar_t__ ktime_sub (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ ktime_to_ns (scalar_t__) ; 
 scalar_t__ kvm_lapic_get_reg (struct kvm_lapic*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mod_64 (scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u32 apic_get_tmcct(struct kvm_lapic *apic)
{
	ktime_t remaining, now;
	s64 ns;
	u32 tmcct;

	ASSERT(apic != NULL);

	/* if initial count is 0, current count should also be 0 */
	if (kvm_lapic_get_reg(apic, APIC_TMICT) == 0 ||
		apic->lapic_timer.period == 0)
		return 0;

	now = ktime_get();
	remaining = ktime_sub(apic->lapic_timer.target_expiration, now);
	if (ktime_to_ns(remaining) < 0)
		remaining = 0;

	ns = mod_64(ktime_to_ns(remaining), apic->lapic_timer.period);
	tmcct = div64_u64(ns,
			 (APIC_BUS_CYCLE_NS * apic->divide_count));

	return tmcct;
}