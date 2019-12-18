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
struct TYPE_3__ {int hv_timer_in_use; } ;
struct kvm_lapic {TYPE_1__ lapic_timer; int /*<<< orphan*/  vcpu; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* cancel_hv_timer ) (int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 TYPE_2__* kvm_x86_ops ; 
 int preemptible () ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cancel_hv_timer(struct kvm_lapic *apic)
{
	WARN_ON(preemptible());
	WARN_ON(!apic->lapic_timer.hv_timer_in_use);
	kvm_x86_ops->cancel_hv_timer(apic->vcpu);
	apic->lapic_timer.hv_timer_in_use = false;
}