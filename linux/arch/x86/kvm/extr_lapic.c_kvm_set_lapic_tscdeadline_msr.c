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
typedef  int /*<<< orphan*/  u64 ;
struct TYPE_3__ {struct kvm_lapic* apic; } ;
struct kvm_vcpu {TYPE_1__ arch; } ;
struct TYPE_4__ {int /*<<< orphan*/  tscdeadline; int /*<<< orphan*/  timer; } ;
struct kvm_lapic {TYPE_2__ lapic_timer; } ;

/* Variables and functions */
 scalar_t__ apic_lvtt_oneshot (struct kvm_lapic*) ; 
 scalar_t__ apic_lvtt_period (struct kvm_lapic*) ; 
 int /*<<< orphan*/  hrtimer_cancel (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lapic_in_kernel (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  start_apic_timer (struct kvm_lapic*) ; 

void kvm_set_lapic_tscdeadline_msr(struct kvm_vcpu *vcpu, u64 data)
{
	struct kvm_lapic *apic = vcpu->arch.apic;

	if (!lapic_in_kernel(vcpu) || apic_lvtt_oneshot(apic) ||
			apic_lvtt_period(apic))
		return;

	hrtimer_cancel(&apic->lapic_timer.timer);
	apic->lapic_timer.tscdeadline = data;
	start_apic_timer(apic);
}