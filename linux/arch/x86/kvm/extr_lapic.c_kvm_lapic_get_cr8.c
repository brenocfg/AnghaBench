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
typedef  int u64 ;
struct TYPE_2__ {int /*<<< orphan*/  apic; } ;
struct kvm_vcpu {TYPE_1__ arch; } ;

/* Variables and functions */
 int /*<<< orphan*/  APIC_TASKPRI ; 
 scalar_t__ kvm_lapic_get_reg (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

u64 kvm_lapic_get_cr8(struct kvm_vcpu *vcpu)
{
	u64 tpr;

	tpr = (u64) kvm_lapic_get_reg(vcpu->arch.apic, APIC_TASKPRI);

	return (tpr & 0xf0) >> 4;
}