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
struct kvm_vcpu {int dummy; } ;
struct TYPE_2__ {scalar_t__ (* guest_apic_has_interrupt ) (struct kvm_vcpu*) ;} ;

/* Variables and functions */
 scalar_t__ is_guest_mode (struct kvm_vcpu*) ; 
 TYPE_1__* kvm_x86_ops ; 
 scalar_t__ stub1 (struct kvm_vcpu*) ; 

__attribute__((used)) static inline bool kvm_guest_apic_has_interrupt(struct kvm_vcpu *vcpu)
{
	return (is_guest_mode(vcpu) &&
			kvm_x86_ops->guest_apic_has_interrupt &&
			kvm_x86_ops->guest_apic_has_interrupt(vcpu));
}