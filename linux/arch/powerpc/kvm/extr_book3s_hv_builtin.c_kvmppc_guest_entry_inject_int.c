#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int msr; } ;
struct TYPE_6__ {int pending_exceptions; unsigned long intr_msr; scalar_t__ doorbell_request; TYPE_2__* vcore; TYPE_1__ shregs; } ;
struct kvm_vcpu {TYPE_3__ arch; } ;
struct TYPE_5__ {int dpdes; } ;

/* Variables and functions */
 unsigned long BOOK3S_INTERRUPT_DECREMENTER ; 
 unsigned long BOOK3S_INTERRUPT_EXTERNAL ; 
 int BOOK3S_IRQPRIO_EXTERNAL ; 
 unsigned long LPCR_LD ; 
 int LPCR_MER_SH ; 
 int MSR_EE ; 
 scalar_t__ MSR_TM_ACTIVE (unsigned long) ; 
 unsigned long MSR_TS_S ; 
 int /*<<< orphan*/  SPRN_DEC ; 
 int /*<<< orphan*/  SPRN_DPDES ; 
 int /*<<< orphan*/  SPRN_LPCR ; 
 int /*<<< orphan*/  isync () ; 
 int /*<<< orphan*/  kvmppc_get_pc (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  kvmppc_set_pc (struct kvm_vcpu*,unsigned long) ; 
 int /*<<< orphan*/  kvmppc_set_srr0 (struct kvm_vcpu*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvmppc_set_srr1 (struct kvm_vcpu*,unsigned long) ; 
 void* mfspr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtspr (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  smp_wmb () ; 

void kvmppc_guest_entry_inject_int(struct kvm_vcpu *vcpu)
{
	int ext;
	unsigned long vec = 0;
	unsigned long lpcr;

	/* Insert EXTERNAL bit into LPCR at the MER bit position */
	ext = (vcpu->arch.pending_exceptions >> BOOK3S_IRQPRIO_EXTERNAL) & 1;
	lpcr = mfspr(SPRN_LPCR);
	lpcr |= ext << LPCR_MER_SH;
	mtspr(SPRN_LPCR, lpcr);
	isync();

	if (vcpu->arch.shregs.msr & MSR_EE) {
		if (ext) {
			vec = BOOK3S_INTERRUPT_EXTERNAL;
		} else {
			long int dec = mfspr(SPRN_DEC);
			if (!(lpcr & LPCR_LD))
				dec = (int) dec;
			if (dec < 0)
				vec = BOOK3S_INTERRUPT_DECREMENTER;
		}
	}
	if (vec) {
		unsigned long msr, old_msr = vcpu->arch.shregs.msr;

		kvmppc_set_srr0(vcpu, kvmppc_get_pc(vcpu));
		kvmppc_set_srr1(vcpu, old_msr);
		kvmppc_set_pc(vcpu, vec);
		msr = vcpu->arch.intr_msr;
		if (MSR_TM_ACTIVE(old_msr))
			msr |= MSR_TS_S;
		vcpu->arch.shregs.msr = msr;
	}

	if (vcpu->arch.doorbell_request) {
		mtspr(SPRN_DPDES, 1);
		vcpu->arch.vcore->dpdes = 1;
		smp_wmb();
		vcpu->arch.doorbell_request = 0;
	}
}