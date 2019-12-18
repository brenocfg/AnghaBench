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
typedef  int u64 ;
typedef  scalar_t__ u32 ;
struct TYPE_3__ {int /*<<< orphan*/  virtual_tsc_khz; struct kvm_lapic* apic; } ;
struct kvm_vcpu {TYPE_1__ arch; } ;
struct TYPE_4__ {scalar_t__ timer_advance_ns; } ;
struct kvm_lapic {TYPE_2__ lapic_timer; } ;
typedef  unsigned long long s64 ;

/* Variables and functions */
 scalar_t__ LAPIC_TIMER_ADVANCE_ADJUST_MAX ; 
 scalar_t__ LAPIC_TIMER_ADVANCE_ADJUST_MIN ; 
 int LAPIC_TIMER_ADVANCE_ADJUST_STEP ; 
 scalar_t__ LAPIC_TIMER_ADVANCE_NS_INIT ; 
 scalar_t__ LAPIC_TIMER_ADVANCE_NS_MAX ; 
 scalar_t__ abs (unsigned long long) ; 
 int /*<<< orphan*/  do_div (int,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static inline void adjust_lapic_timer_advance(struct kvm_vcpu *vcpu,
					      s64 advance_expire_delta)
{
	struct kvm_lapic *apic = vcpu->arch.apic;
	u32 timer_advance_ns = apic->lapic_timer.timer_advance_ns;
	u64 ns;

	/* Do not adjust for tiny fluctuations or large random spikes. */
	if (abs(advance_expire_delta) > LAPIC_TIMER_ADVANCE_ADJUST_MAX ||
	    abs(advance_expire_delta) < LAPIC_TIMER_ADVANCE_ADJUST_MIN)
		return;

	/* too early */
	if (advance_expire_delta < 0) {
		ns = -advance_expire_delta * 1000000ULL;
		do_div(ns, vcpu->arch.virtual_tsc_khz);
		timer_advance_ns -= ns/LAPIC_TIMER_ADVANCE_ADJUST_STEP;
	} else {
	/* too late */
		ns = advance_expire_delta * 1000000ULL;
		do_div(ns, vcpu->arch.virtual_tsc_khz);
		timer_advance_ns += ns/LAPIC_TIMER_ADVANCE_ADJUST_STEP;
	}

	if (unlikely(timer_advance_ns > LAPIC_TIMER_ADVANCE_NS_MAX))
		timer_advance_ns = LAPIC_TIMER_ADVANCE_NS_INIT;
	apic->lapic_timer.timer_advance_ns = timer_advance_ns;
}