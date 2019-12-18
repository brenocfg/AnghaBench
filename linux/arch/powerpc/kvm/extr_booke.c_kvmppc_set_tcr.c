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
struct TYPE_2__ {int /*<<< orphan*/  tcr; } ;
struct kvm_vcpu {TYPE_1__ arch; } ;

/* Variables and functions */
 int /*<<< orphan*/  arm_next_watchdog (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  update_timer_ints (struct kvm_vcpu*) ; 

void kvmppc_set_tcr(struct kvm_vcpu *vcpu, u32 new_tcr)
{
	vcpu->arch.tcr = new_tcr;
	arm_next_watchdog(vcpu);
	update_timer_ints(vcpu);
}