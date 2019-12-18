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
struct kvm_vcpu {int dummy; } ;

/* Variables and functions */
 scalar_t__ kvm_vcpu_apicv_active (struct kvm_vcpu*) ; 
 scalar_t__ pi_inject_timer ; 

bool kvm_can_post_timer_interrupt(struct kvm_vcpu *vcpu)
{
	return pi_inject_timer && kvm_vcpu_apicv_active(vcpu);
}