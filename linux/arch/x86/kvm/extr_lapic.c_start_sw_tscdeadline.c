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
typedef  unsigned long long u64 ;
struct TYPE_2__ {unsigned long virtual_tsc_khz; } ;
struct kvm_vcpu {TYPE_1__ arch; } ;
struct kvm_timer {unsigned long long tscdeadline; unsigned long long timer_advance_ns; int /*<<< orphan*/  timer; } ;
struct kvm_lapic {struct kvm_timer lapic_timer; struct kvm_vcpu* vcpu; } ;
typedef  int /*<<< orphan*/  ktime_t ;

/* Variables and functions */
 int /*<<< orphan*/  HRTIMER_MODE_ABS_HARD ; 
 int /*<<< orphan*/  apic_timer_expired (struct kvm_lapic*) ; 
 int /*<<< orphan*/  do_div (unsigned long long,unsigned long) ; 
 int /*<<< orphan*/  hrtimer_start (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ktime_add_ns (int /*<<< orphan*/ ,unsigned long long) ; 
 int /*<<< orphan*/  ktime_get () ; 
 int /*<<< orphan*/  ktime_sub_ns (int /*<<< orphan*/ ,unsigned long long) ; 
 unsigned long long kvm_read_l1_tsc (struct kvm_vcpu*,int /*<<< orphan*/ ) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 int /*<<< orphan*/  rdtsc () ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void start_sw_tscdeadline(struct kvm_lapic *apic)
{
	struct kvm_timer *ktimer = &apic->lapic_timer;
	u64 guest_tsc, tscdeadline = ktimer->tscdeadline;
	u64 ns = 0;
	ktime_t expire;
	struct kvm_vcpu *vcpu = apic->vcpu;
	unsigned long this_tsc_khz = vcpu->arch.virtual_tsc_khz;
	unsigned long flags;
	ktime_t now;

	if (unlikely(!tscdeadline || !this_tsc_khz))
		return;

	local_irq_save(flags);

	now = ktime_get();
	guest_tsc = kvm_read_l1_tsc(vcpu, rdtsc());

	ns = (tscdeadline - guest_tsc) * 1000000ULL;
	do_div(ns, this_tsc_khz);

	if (likely(tscdeadline > guest_tsc) &&
	    likely(ns > apic->lapic_timer.timer_advance_ns)) {
		expire = ktime_add_ns(now, ns);
		expire = ktime_sub_ns(expire, ktimer->timer_advance_ns);
		hrtimer_start(&ktimer->timer, expire, HRTIMER_MODE_ABS_HARD);
	} else
		apic_timer_expired(apic);

	local_irq_restore(flags);
}