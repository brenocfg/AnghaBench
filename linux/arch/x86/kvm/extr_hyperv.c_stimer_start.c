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
typedef  scalar_t__ u64 ;
struct TYPE_3__ {scalar_t__ periodic; } ;
struct kvm_vcpu_hv_stimer {scalar_t__ exp_time; scalar_t__ count; int /*<<< orphan*/  timer; int /*<<< orphan*/  index; TYPE_1__ config; } ;
typedef  int /*<<< orphan*/  ktime_t ;
struct TYPE_4__ {int /*<<< orphan*/  vcpu_id; int /*<<< orphan*/  kvm; } ;

/* Variables and functions */
 int /*<<< orphan*/  HRTIMER_MODE_ABS ; 
 int /*<<< orphan*/  div64_u64_rem (scalar_t__,scalar_t__,scalar_t__*) ; 
 scalar_t__ get_time_ref_counter (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hrtimer_start (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ktime_add_ns (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ktime_get () ; 
 int /*<<< orphan*/  stimer_mark_pending (struct kvm_vcpu_hv_stimer*,int) ; 
 TYPE_2__* stimer_to_vcpu (struct kvm_vcpu_hv_stimer*) ; 
 int /*<<< orphan*/  trace_kvm_hv_stimer_start_one_shot (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  trace_kvm_hv_stimer_start_periodic (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 

__attribute__((used)) static int stimer_start(struct kvm_vcpu_hv_stimer *stimer)
{
	u64 time_now;
	ktime_t ktime_now;

	time_now = get_time_ref_counter(stimer_to_vcpu(stimer)->kvm);
	ktime_now = ktime_get();

	if (stimer->config.periodic) {
		if (stimer->exp_time) {
			if (time_now >= stimer->exp_time) {
				u64 remainder;

				div64_u64_rem(time_now - stimer->exp_time,
					      stimer->count, &remainder);
				stimer->exp_time =
					time_now + (stimer->count - remainder);
			}
		} else
			stimer->exp_time = time_now + stimer->count;

		trace_kvm_hv_stimer_start_periodic(
					stimer_to_vcpu(stimer)->vcpu_id,
					stimer->index,
					time_now, stimer->exp_time);

		hrtimer_start(&stimer->timer,
			      ktime_add_ns(ktime_now,
					   100 * (stimer->exp_time - time_now)),
			      HRTIMER_MODE_ABS);
		return 0;
	}
	stimer->exp_time = stimer->count;
	if (time_now >= stimer->count) {
		/*
		 * Expire timer according to Hypervisor Top-Level Functional
		 * specification v4(15.3.1):
		 * "If a one shot is enabled and the specified count is in
		 * the past, it will expire immediately."
		 */
		stimer_mark_pending(stimer, false);
		return 0;
	}

	trace_kvm_hv_stimer_start_one_shot(stimer_to_vcpu(stimer)->vcpu_id,
					   stimer->index,
					   time_now, stimer->count);

	hrtimer_start(&stimer->timer,
		      ktime_add_ns(ktime_now, 100 * (stimer->count - time_now)),
		      HRTIMER_MODE_ABS);
	return 0;
}