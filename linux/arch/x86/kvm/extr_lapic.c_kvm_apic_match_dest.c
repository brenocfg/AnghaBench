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
struct TYPE_2__ {struct kvm_lapic* apic; } ;
struct kvm_vcpu {TYPE_1__ arch; } ;
struct kvm_lapic {int dummy; } ;

/* Variables and functions */
#define  APIC_DEST_ALLBUT 131 
#define  APIC_DEST_ALLINC 130 
#define  APIC_DEST_NOSHORT 129 
 int APIC_DEST_PHYSICAL ; 
#define  APIC_DEST_SELF 128 
 int /*<<< orphan*/  ASSERT (struct kvm_lapic*) ; 
 int kvm_apic_match_logical_addr (struct kvm_lapic*,int /*<<< orphan*/ ) ; 
 int kvm_apic_match_physical_addr (struct kvm_lapic*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvm_apic_mda (struct kvm_vcpu*,unsigned int,struct kvm_lapic*,struct kvm_lapic*) ; 

bool kvm_apic_match_dest(struct kvm_vcpu *vcpu, struct kvm_lapic *source,
			   int short_hand, unsigned int dest, int dest_mode)
{
	struct kvm_lapic *target = vcpu->arch.apic;
	u32 mda = kvm_apic_mda(vcpu, dest, source, target);

	ASSERT(target);
	switch (short_hand) {
	case APIC_DEST_NOSHORT:
		if (dest_mode == APIC_DEST_PHYSICAL)
			return kvm_apic_match_physical_addr(target, mda);
		else
			return kvm_apic_match_logical_addr(target, mda);
	case APIC_DEST_SELF:
		return target == source;
	case APIC_DEST_ALLINC:
		return true;
	case APIC_DEST_ALLBUT:
		return target != source;
	default:
		return false;
	}
}