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
typedef  int u32 ;
struct TYPE_2__ {int /*<<< orphan*/  apic; } ;
struct kvm_vcpu {TYPE_1__ arch; } ;

/* Variables and functions */
 int /*<<< orphan*/  kvm_lapic_reg_read (int /*<<< orphan*/ ,int,int,int*) ; 
 int /*<<< orphan*/  kvm_lapic_reg_write (int /*<<< orphan*/ ,int,int) ; 

void kvm_apic_write_nodecode(struct kvm_vcpu *vcpu, u32 offset)
{
	u32 val = 0;

	/* hw has done the conditional check and inst decode */
	offset &= 0xff0;

	kvm_lapic_reg_read(vcpu->arch.apic, offset, 4, &val);

	/* TODO: optimize to just emulate side effect w/o one more write */
	kvm_lapic_reg_write(vcpu->arch.apic, offset, val);
}