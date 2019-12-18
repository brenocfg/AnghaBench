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
 scalar_t__ kvm_apic_accept_pic_intr (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  lapic_in_kernel (struct kvm_vcpu*) ; 

__attribute__((used)) static int kvm_cpu_accept_dm_intr(struct kvm_vcpu *vcpu)
{
	return (!lapic_in_kernel(vcpu) ||
		kvm_apic_accept_pic_intr(vcpu));
}