#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct kvm_kpit_state {int flags; scalar_t__ period; int is_periodic; int /*<<< orphan*/  timer; } ;
struct kvm_pit {int /*<<< orphan*/  expired; struct kvm* kvm; struct kvm_kpit_state pit_state; } ;
struct kvm {int dummy; } ;
typedef  scalar_t__ s64 ;

/* Variables and functions */
 int /*<<< orphan*/  HRTIMER_MODE_ABS ; 
 int KVM_PIT_FLAGS_HPET_LEGACY ; 
 int /*<<< orphan*/  KVM_PIT_FREQ ; 
 int /*<<< orphan*/  NSEC_PER_SEC ; 
 int /*<<< orphan*/  hrtimer_cancel (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hrtimer_start (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ioapic_in_kernel (struct kvm*) ; 
 int /*<<< orphan*/  kthread_flush_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ktime_add_ns (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  ktime_get () ; 
 int /*<<< orphan*/  kvm_pit_reset_reinject (struct kvm_pit*) ; 
 long long min_timer_period_us ; 
 scalar_t__ mul_u64_u32_div (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*,scalar_t__) ; 
 int /*<<< orphan*/  pr_info_ratelimited (char*,scalar_t__,scalar_t__) ; 

__attribute__((used)) static void create_pit_timer(struct kvm_pit *pit, u32 val, int is_period)
{
	struct kvm_kpit_state *ps = &pit->pit_state;
	struct kvm *kvm = pit->kvm;
	s64 interval;

	if (!ioapic_in_kernel(kvm) ||
	    ps->flags & KVM_PIT_FLAGS_HPET_LEGACY)
		return;

	interval = mul_u64_u32_div(val, NSEC_PER_SEC, KVM_PIT_FREQ);

	pr_debug("create pit timer, interval is %llu nsec\n", interval);

	/* TODO The new value only affected after the retriggered */
	hrtimer_cancel(&ps->timer);
	kthread_flush_work(&pit->expired);
	ps->period = interval;
	ps->is_periodic = is_period;

	kvm_pit_reset_reinject(pit);

	/*
	 * Do not allow the guest to program periodic timers with small
	 * interval, since the hrtimers are not throttled by the host
	 * scheduler.
	 */
	if (ps->is_periodic) {
		s64 min_period = min_timer_period_us * 1000LL;

		if (ps->period < min_period) {
			pr_info_ratelimited(
			    "kvm: requested %lld ns "
			    "i8254 timer period limited to %lld ns\n",
			    ps->period, min_period);
			ps->period = min_period;
		}
	}

	hrtimer_start(&ps->timer, ktime_add_ns(ktime_get(), interval),
		      HRTIMER_MODE_ABS);
}