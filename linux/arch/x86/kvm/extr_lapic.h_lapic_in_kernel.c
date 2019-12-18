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
struct TYPE_2__ {int apic; } ;
struct kvm_vcpu {TYPE_1__ arch; } ;

/* Variables and functions */
 int /*<<< orphan*/  kvm_no_apic_vcpu ; 
 scalar_t__ static_key_false (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline bool lapic_in_kernel(struct kvm_vcpu *vcpu)
{
	if (static_key_false(&kvm_no_apic_vcpu))
		return vcpu->arch.apic;
	return true;
}