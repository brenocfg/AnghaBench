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
struct TYPE_2__ {int apic_base; } ;
struct kvm_vcpu {TYPE_1__ arch; } ;

/* Variables and functions */
 int MSR_IA32_APICBASE_BSP ; 

bool kvm_vcpu_is_bsp(struct kvm_vcpu *vcpu)
{
	return (vcpu->arch.apic_base & MSR_IA32_APICBASE_BSP) != 0;
}