#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u64 ;
typedef  int u32 ;
struct TYPE_7__ {int nip; int ccr; } ;
struct TYPE_6__ {int srr1; int msr; int srr0; } ;
struct TYPE_8__ {int emul_inst; int hfscr; TYPE_3__ regs; TYPE_2__ shregs; TYPE_1__* vcore; int /*<<< orphan*/  cfar; } ;
struct kvm_vcpu {TYPE_4__ arch; } ;
struct TYPE_5__ {int pcr; } ;

/* Variables and functions */
 int BESCR_GE ; 
 int FSCR_EBB ; 
 int HFSCR_EBB ; 
 int HFSCR_TM ; 
 int MSR_LE ; 
 int MSR_PR ; 
 int MSR_TM ; 
 int /*<<< orphan*/  MSR_TM_TRANSACTIONAL (int) ; 
 int MSR_TS_MASK ; 
 int MSR_TS_T ; 
 int PCR_ARCH_206 ; 
#define  PPC_INST_MTMSRD 131 
#define  PPC_INST_RFEBB 130 
#define  PPC_INST_RFID 129 
#define  PPC_INST_TSR 128 
 int /*<<< orphan*/  SPRN_BESCR ; 
 int /*<<< orphan*/  SPRN_EBBRR ; 
 int /*<<< orphan*/  SPRN_FSCR ; 
 int kvmppc_get_gpr (struct kvm_vcpu*,int) ; 
 int mfspr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtspr (int /*<<< orphan*/ ,int) ; 
 int sanitize_msr (int) ; 

int kvmhv_p9_tm_emulation_early(struct kvm_vcpu *vcpu)
{
	u32 instr = vcpu->arch.emul_inst;
	u64 newmsr, msr, bescr;
	int rs;

	switch (instr & 0xfc0007ff) {
	case PPC_INST_RFID:
		/* XXX do we need to check for PR=0 here? */
		newmsr = vcpu->arch.shregs.srr1;
		/* should only get here for Sx -> T1 transition */
		if (!(MSR_TM_TRANSACTIONAL(newmsr) && (newmsr & MSR_TM)))
			return 0;
		newmsr = sanitize_msr(newmsr);
		vcpu->arch.shregs.msr = newmsr;
		vcpu->arch.cfar = vcpu->arch.regs.nip - 4;
		vcpu->arch.regs.nip = vcpu->arch.shregs.srr0;
		return 1;

	case PPC_INST_RFEBB:
		/* check for PR=1 and arch 2.06 bit set in PCR */
		msr = vcpu->arch.shregs.msr;
		if ((msr & MSR_PR) && (vcpu->arch.vcore->pcr & PCR_ARCH_206))
			return 0;
		/* check EBB facility is available */
		if (!(vcpu->arch.hfscr & HFSCR_EBB) ||
		    ((msr & MSR_PR) && !(mfspr(SPRN_FSCR) & FSCR_EBB)))
			return 0;
		bescr = mfspr(SPRN_BESCR);
		/* expect to see a S->T transition requested */
		if (((bescr >> 30) & 3) != 2)
			return 0;
		bescr &= ~BESCR_GE;
		if (instr & (1 << 11))
			bescr |= BESCR_GE;
		mtspr(SPRN_BESCR, bescr);
		msr = (msr & ~MSR_TS_MASK) | MSR_TS_T;
		vcpu->arch.shregs.msr = msr;
		vcpu->arch.cfar = vcpu->arch.regs.nip - 4;
		vcpu->arch.regs.nip = mfspr(SPRN_EBBRR);
		return 1;

	case PPC_INST_MTMSRD:
		/* XXX do we need to check for PR=0 here? */
		rs = (instr >> 21) & 0x1f;
		newmsr = kvmppc_get_gpr(vcpu, rs);
		msr = vcpu->arch.shregs.msr;
		/* check this is a Sx -> T1 transition */
		if (!(MSR_TM_TRANSACTIONAL(newmsr) && (newmsr & MSR_TM)))
			return 0;
		/* mtmsrd doesn't change LE */
		newmsr = (newmsr & ~MSR_LE) | (msr & MSR_LE);
		newmsr = sanitize_msr(newmsr);
		vcpu->arch.shregs.msr = newmsr;
		return 1;

	case PPC_INST_TSR:
		/* we know the MSR has the TS field = S (0b01) here */
		msr = vcpu->arch.shregs.msr;
		/* check for PR=1 and arch 2.06 bit set in PCR */
		if ((msr & MSR_PR) && (vcpu->arch.vcore->pcr & PCR_ARCH_206))
			return 0;
		/* check for TM disabled in the HFSCR or MSR */
		if (!(vcpu->arch.hfscr & HFSCR_TM) || !(msr & MSR_TM))
			return 0;
		/* L=1 => tresume => set TS to T (0b10) */
		if (instr & (1 << 21))
			vcpu->arch.shregs.msr = (msr & ~MSR_TS_MASK) | MSR_TS_T;
		/* Set CR0 to 0b0010 */
		vcpu->arch.regs.ccr = (vcpu->arch.regs.ccr & 0x0fffffff) |
			0x20000000;
		return 1;
	}

	return 0;
}