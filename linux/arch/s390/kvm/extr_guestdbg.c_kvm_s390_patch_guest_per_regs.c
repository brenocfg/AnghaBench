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
struct TYPE_4__ {TYPE_1__* sie_block; } ;
struct kvm_vcpu {TYPE_2__ arch; } ;
struct TYPE_3__ {unsigned long* gcr; } ;

/* Variables and functions */
 unsigned long CR0_CLOCK_COMPARATOR_SUBMASK ; 
 unsigned long PER_EVENT_IFETCH ; 
 int PER_EVENT_NULLIFICATION ; 
 int /*<<< orphan*/  enable_all_hw_bp (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  enable_all_hw_wp (struct kvm_vcpu*) ; 
 scalar_t__ guestdbg_hw_bp_enabled (struct kvm_vcpu*) ; 
 scalar_t__ guestdbg_sstep_enabled (struct kvm_vcpu*) ; 

void kvm_s390_patch_guest_per_regs(struct kvm_vcpu *vcpu)
{
	/*
	 * TODO: if guest psw has per enabled, otherwise 0s!
	 * This reduces the amount of reported events.
	 * Need to intercept all psw changes!
	 */

	if (guestdbg_sstep_enabled(vcpu)) {
		/* disable timer (clock-comparator) interrupts */
		vcpu->arch.sie_block->gcr[0] &= ~CR0_CLOCK_COMPARATOR_SUBMASK;
		vcpu->arch.sie_block->gcr[9] |= PER_EVENT_IFETCH;
		vcpu->arch.sie_block->gcr[10] = 0;
		vcpu->arch.sie_block->gcr[11] = -1UL;
	}

	if (guestdbg_hw_bp_enabled(vcpu)) {
		enable_all_hw_bp(vcpu);
		enable_all_hw_wp(vcpu);
	}

	/* TODO: Instruction-fetching-nullification not allowed for now */
	if (vcpu->arch.sie_block->gcr[9] & PER_EVENT_NULLIFICATION)
		vcpu->arch.sie_block->gcr[9] &= ~PER_EVENT_NULLIFICATION;
}