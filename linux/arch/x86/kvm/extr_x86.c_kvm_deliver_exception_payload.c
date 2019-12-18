#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {unsigned int nr; int has_payload; unsigned long payload; } ;
struct TYPE_4__ {unsigned long dr6; unsigned long cr2; TYPE_1__ exception; } ;
struct kvm_vcpu {TYPE_2__ arch; } ;

/* Variables and functions */
#define  DB_VECTOR 129 
 unsigned long DR6_RTM ; 
 unsigned long DR_TRAP_BITS ; 
#define  PF_VECTOR 128 

void kvm_deliver_exception_payload(struct kvm_vcpu *vcpu)
{
	unsigned nr = vcpu->arch.exception.nr;
	bool has_payload = vcpu->arch.exception.has_payload;
	unsigned long payload = vcpu->arch.exception.payload;

	if (!has_payload)
		return;

	switch (nr) {
	case DB_VECTOR:
		/*
		 * "Certain debug exceptions may clear bit 0-3.  The
		 * remaining contents of the DR6 register are never
		 * cleared by the processor".
		 */
		vcpu->arch.dr6 &= ~DR_TRAP_BITS;
		/*
		 * DR6.RTM is set by all #DB exceptions that don't clear it.
		 */
		vcpu->arch.dr6 |= DR6_RTM;
		vcpu->arch.dr6 |= payload;
		/*
		 * Bit 16 should be set in the payload whenever the #DB
		 * exception should clear DR6.RTM. This makes the payload
		 * compatible with the pending debug exceptions under VMX.
		 * Though not currently documented in the SDM, this also
		 * makes the payload compatible with the exit qualification
		 * for #DB exceptions under VMX.
		 */
		vcpu->arch.dr6 ^= payload & DR6_RTM;
		break;
	case PF_VECTOR:
		vcpu->arch.cr2 = payload;
		break;
	}

	vcpu->arch.exception.has_payload = false;
	vcpu->arch.exception.payload = 0;
}