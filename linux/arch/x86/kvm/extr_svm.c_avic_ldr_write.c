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
typedef  int u32 ;
struct TYPE_2__ {int /*<<< orphan*/  apic; } ;
struct kvm_vcpu {TYPE_1__ arch; } ;

/* Variables and functions */
 int /*<<< orphan*/  APIC_DFR ; 
 scalar_t__ APIC_DFR_FLAT ; 
 int AVIC_LOGICAL_ID_ENTRY_GUEST_PHYSICAL_ID_MASK ; 
 int AVIC_LOGICAL_ID_ENTRY_VALID_MASK ; 
 int EINVAL ; 
 int READ_ONCE (int) ; 
 int /*<<< orphan*/  WRITE_ONCE (int,int) ; 
 int* avic_get_logical_id_entry (struct kvm_vcpu*,int,int) ; 
 scalar_t__ kvm_lapic_get_reg (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int avic_ldr_write(struct kvm_vcpu *vcpu, u8 g_physical_id, u32 ldr)
{
	bool flat;
	u32 *entry, new_entry;

	flat = kvm_lapic_get_reg(vcpu->arch.apic, APIC_DFR) == APIC_DFR_FLAT;
	entry = avic_get_logical_id_entry(vcpu, ldr, flat);
	if (!entry)
		return -EINVAL;

	new_entry = READ_ONCE(*entry);
	new_entry &= ~AVIC_LOGICAL_ID_ENTRY_GUEST_PHYSICAL_ID_MASK;
	new_entry |= (g_physical_id & AVIC_LOGICAL_ID_ENTRY_GUEST_PHYSICAL_ID_MASK);
	new_entry |= AVIC_LOGICAL_ID_ENTRY_VALID_MASK;
	WRITE_ONCE(*entry, new_entry);

	return 0;
}