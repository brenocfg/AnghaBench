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
struct TYPE_2__ {int /*<<< orphan*/  pending; } ;
struct kvm_lapic {TYPE_1__ lapic_timer; } ;

/* Variables and functions */
 scalar_t__ apic_lvtt_oneshot (struct kvm_lapic*) ; 
 scalar_t__ apic_lvtt_period (struct kvm_lapic*) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  restart_apic_timer (struct kvm_lapic*) ; 
 int /*<<< orphan*/  set_target_expiration (struct kvm_lapic*) ; 

__attribute__((used)) static void start_apic_timer(struct kvm_lapic *apic)
{
	atomic_set(&apic->lapic_timer.pending, 0);

	if ((apic_lvtt_period(apic) || apic_lvtt_oneshot(apic))
	    && !set_target_expiration(apic))
		return;

	restart_apic_timer(apic);
}