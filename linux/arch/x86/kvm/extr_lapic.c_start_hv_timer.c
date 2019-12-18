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
struct kvm_vcpu {int /*<<< orphan*/  vcpu_id; } ;
struct kvm_timer {int hv_timer_in_use; int /*<<< orphan*/  pending; int /*<<< orphan*/  timer; int /*<<< orphan*/  tscdeadline; } ;
struct kvm_lapic {struct kvm_vcpu* vcpu; struct kvm_timer lapic_timer; } ;
struct TYPE_2__ {scalar_t__ (* set_hv_timer ) (struct kvm_vcpu*,int /*<<< orphan*/ ,int*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  apic_lvtt_period (struct kvm_lapic*) ; 
 int /*<<< orphan*/  apic_timer_expired (struct kvm_lapic*) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cancel_hv_timer (struct kvm_lapic*) ; 
 int /*<<< orphan*/  hrtimer_cancel (int /*<<< orphan*/ *) ; 
 TYPE_1__* kvm_x86_ops ; 
 int /*<<< orphan*/  preemptible () ; 
 scalar_t__ stub1 (struct kvm_vcpu*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  trace_kvm_hv_timer_state (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static bool start_hv_timer(struct kvm_lapic *apic)
{
	struct kvm_timer *ktimer = &apic->lapic_timer;
	struct kvm_vcpu *vcpu = apic->vcpu;
	bool expired;

	WARN_ON(preemptible());
	if (!kvm_x86_ops->set_hv_timer)
		return false;

	if (!ktimer->tscdeadline)
		return false;

	if (kvm_x86_ops->set_hv_timer(vcpu, ktimer->tscdeadline, &expired))
		return false;

	ktimer->hv_timer_in_use = true;
	hrtimer_cancel(&ktimer->timer);

	/*
	 * To simplify handling the periodic timer, leave the hv timer running
	 * even if the deadline timer has expired, i.e. rely on the resulting
	 * VM-Exit to recompute the periodic timer's target expiration.
	 */
	if (!apic_lvtt_period(apic)) {
		/*
		 * Cancel the hv timer if the sw timer fired while the hv timer
		 * was being programmed, or if the hv timer itself expired.
		 */
		if (atomic_read(&ktimer->pending)) {
			cancel_hv_timer(apic);
		} else if (expired) {
			apic_timer_expired(apic);
			cancel_hv_timer(apic);
		}
	}

	trace_kvm_hv_timer_state(vcpu->vcpu_id, ktimer->hv_timer_in_use);

	return true;
}