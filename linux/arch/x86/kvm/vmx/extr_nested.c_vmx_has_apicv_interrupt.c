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
typedef  int u8 ;
struct TYPE_2__ {int /*<<< orphan*/  apic; } ;
struct kvm_vcpu {TYPE_1__ arch; } ;

/* Variables and functions */
 int /*<<< orphan*/  APIC_PROCPRI ; 
 int kvm_lapic_get_reg (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int vmx_get_rvi () ; 

__attribute__((used)) static u8 vmx_has_apicv_interrupt(struct kvm_vcpu *vcpu)
{
	u8 rvi = vmx_get_rvi();
	u8 vppr = kvm_lapic_get_reg(vcpu->arch.apic, APIC_PROCPRI);

	return ((rvi & 0xf0) > (vppr & 0xf0));
}