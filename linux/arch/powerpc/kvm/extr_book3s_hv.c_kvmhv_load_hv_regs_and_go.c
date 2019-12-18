#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int u64 ;
struct kvmppc_vcore {int tb_offset; int tb_offset_applied; int pcr; int dpdes; int vtb; } ;
struct TYPE_7__ {int sprg0; int sprg1; int sprg2; int sprg3; int srr0; int srr1; } ;
struct TYPE_8__ {int purr; int spurr; int dawr; int dawrx; int ciabr; int ic; int pid; unsigned long psscr; int hfscr; TYPE_1__ shregs; struct kvmppc_vcore* vcore; } ;
struct kvm_vcpu {TYPE_5__* kvm; TYPE_2__ arch; } ;
typedef  scalar_t__ s64 ;
struct TYPE_9__ {int host_purr; int host_spurr; unsigned long fake_suspend; } ;
struct TYPE_12__ {TYPE_3__ kvm_hstate; } ;
struct TYPE_10__ {int host_lpid; int host_lpcr; } ;
struct TYPE_11__ {TYPE_4__ arch; } ;

/* Variables and functions */
 int BOOK3S_INTERRUPT_HV_DECREMENTER ; 
 int PCR_MASK ; 
 unsigned long PSSCR_EC ; 
 unsigned long PSSCR_FAKE_SUSPEND_LG ; 
 int PSSCR_GUEST_VIS ; 
 int /*<<< orphan*/  SPRN_AMOR ; 
 int /*<<< orphan*/  SPRN_CIABR ; 
 int /*<<< orphan*/  SPRN_DAWR ; 
 int /*<<< orphan*/  SPRN_DAWRX ; 
 int /*<<< orphan*/  SPRN_DPDES ; 
 int /*<<< orphan*/  SPRN_HDEC ; 
 int /*<<< orphan*/  SPRN_HFSCR ; 
 int /*<<< orphan*/  SPRN_IC ; 
 int /*<<< orphan*/  SPRN_LPCR ; 
 int /*<<< orphan*/  SPRN_LPID ; 
 int /*<<< orphan*/  SPRN_PCR ; 
 int /*<<< orphan*/  SPRN_PID ; 
 int /*<<< orphan*/  SPRN_PSSCR ; 
 int /*<<< orphan*/  SPRN_PURR ; 
 int /*<<< orphan*/  SPRN_SPRG0 ; 
 int /*<<< orphan*/  SPRN_SPRG1 ; 
 int /*<<< orphan*/  SPRN_SPRG2 ; 
 int /*<<< orphan*/  SPRN_SPRG3 ; 
 int /*<<< orphan*/  SPRN_SPURR ; 
 int /*<<< orphan*/  SPRN_SRR0 ; 
 int /*<<< orphan*/  SPRN_SRR1 ; 
 int /*<<< orphan*/  SPRN_TBU40 ; 
 int /*<<< orphan*/  SPRN_VTB ; 
 int __kvmhv_vcpu_entry_p9 (struct kvm_vcpu*) ; 
 scalar_t__ dawr_enabled () ; 
 int /*<<< orphan*/  isync () ; 
 int /*<<< orphan*/  kvmppc_xive_push_vcpu (struct kvm_vcpu*) ; 
 TYPE_6__* local_paca ; 
 int mfspr (int /*<<< orphan*/ ) ; 
 int mftb () ; 
 int /*<<< orphan*/  mtspr (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int kvmhv_load_hv_regs_and_go(struct kvm_vcpu *vcpu, u64 time_limit,
				     unsigned long lpcr)
{
	struct kvmppc_vcore *vc = vcpu->arch.vcore;
	s64 hdec;
	u64 tb, purr, spurr;
	int trap;
	unsigned long host_hfscr = mfspr(SPRN_HFSCR);
	unsigned long host_ciabr = mfspr(SPRN_CIABR);
	unsigned long host_dawr = mfspr(SPRN_DAWR);
	unsigned long host_dawrx = mfspr(SPRN_DAWRX);
	unsigned long host_psscr = mfspr(SPRN_PSSCR);
	unsigned long host_pidr = mfspr(SPRN_PID);

	hdec = time_limit - mftb();
	if (hdec < 0)
		return BOOK3S_INTERRUPT_HV_DECREMENTER;
	mtspr(SPRN_HDEC, hdec);

	if (vc->tb_offset) {
		u64 new_tb = mftb() + vc->tb_offset;
		mtspr(SPRN_TBU40, new_tb);
		tb = mftb();
		if ((tb & 0xffffff) < (new_tb & 0xffffff))
			mtspr(SPRN_TBU40, new_tb + 0x1000000);
		vc->tb_offset_applied = vc->tb_offset;
	}

	if (vc->pcr)
		mtspr(SPRN_PCR, vc->pcr | PCR_MASK);
	mtspr(SPRN_DPDES, vc->dpdes);
	mtspr(SPRN_VTB, vc->vtb);

	local_paca->kvm_hstate.host_purr = mfspr(SPRN_PURR);
	local_paca->kvm_hstate.host_spurr = mfspr(SPRN_SPURR);
	mtspr(SPRN_PURR, vcpu->arch.purr);
	mtspr(SPRN_SPURR, vcpu->arch.spurr);

	if (dawr_enabled()) {
		mtspr(SPRN_DAWR, vcpu->arch.dawr);
		mtspr(SPRN_DAWRX, vcpu->arch.dawrx);
	}
	mtspr(SPRN_CIABR, vcpu->arch.ciabr);
	mtspr(SPRN_IC, vcpu->arch.ic);
	mtspr(SPRN_PID, vcpu->arch.pid);

	mtspr(SPRN_PSSCR, vcpu->arch.psscr | PSSCR_EC |
	      (local_paca->kvm_hstate.fake_suspend << PSSCR_FAKE_SUSPEND_LG));

	mtspr(SPRN_HFSCR, vcpu->arch.hfscr);

	mtspr(SPRN_SPRG0, vcpu->arch.shregs.sprg0);
	mtspr(SPRN_SPRG1, vcpu->arch.shregs.sprg1);
	mtspr(SPRN_SPRG2, vcpu->arch.shregs.sprg2);
	mtspr(SPRN_SPRG3, vcpu->arch.shregs.sprg3);

	mtspr(SPRN_AMOR, ~0UL);

	mtspr(SPRN_LPCR, lpcr);
	isync();

	kvmppc_xive_push_vcpu(vcpu);

	mtspr(SPRN_SRR0, vcpu->arch.shregs.srr0);
	mtspr(SPRN_SRR1, vcpu->arch.shregs.srr1);

	trap = __kvmhv_vcpu_entry_p9(vcpu);

	/* Advance host PURR/SPURR by the amount used by guest */
	purr = mfspr(SPRN_PURR);
	spurr = mfspr(SPRN_SPURR);
	mtspr(SPRN_PURR, local_paca->kvm_hstate.host_purr +
	      purr - vcpu->arch.purr);
	mtspr(SPRN_SPURR, local_paca->kvm_hstate.host_spurr +
	      spurr - vcpu->arch.spurr);
	vcpu->arch.purr = purr;
	vcpu->arch.spurr = spurr;

	vcpu->arch.ic = mfspr(SPRN_IC);
	vcpu->arch.pid = mfspr(SPRN_PID);
	vcpu->arch.psscr = mfspr(SPRN_PSSCR) & PSSCR_GUEST_VIS;

	vcpu->arch.shregs.sprg0 = mfspr(SPRN_SPRG0);
	vcpu->arch.shregs.sprg1 = mfspr(SPRN_SPRG1);
	vcpu->arch.shregs.sprg2 = mfspr(SPRN_SPRG2);
	vcpu->arch.shregs.sprg3 = mfspr(SPRN_SPRG3);

	/* Preserve PSSCR[FAKE_SUSPEND] until we've called kvmppc_save_tm_hv */
	mtspr(SPRN_PSSCR, host_psscr |
	      (local_paca->kvm_hstate.fake_suspend << PSSCR_FAKE_SUSPEND_LG));
	mtspr(SPRN_HFSCR, host_hfscr);
	mtspr(SPRN_CIABR, host_ciabr);
	mtspr(SPRN_DAWR, host_dawr);
	mtspr(SPRN_DAWRX, host_dawrx);
	mtspr(SPRN_PID, host_pidr);

	/*
	 * Since this is radix, do a eieio; tlbsync; ptesync sequence in
	 * case we interrupted the guest between a tlbie and a ptesync.
	 */
	asm volatile("eieio; tlbsync; ptesync");

	mtspr(SPRN_LPID, vcpu->kvm->arch.host_lpid);	/* restore host LPID */
	isync();

	vc->dpdes = mfspr(SPRN_DPDES);
	vc->vtb = mfspr(SPRN_VTB);
	mtspr(SPRN_DPDES, 0);
	if (vc->pcr)
		mtspr(SPRN_PCR, PCR_MASK);

	if (vc->tb_offset_applied) {
		u64 new_tb = mftb() - vc->tb_offset_applied;
		mtspr(SPRN_TBU40, new_tb);
		tb = mftb();
		if ((tb & 0xffffff) < (new_tb & 0xffffff))
			mtspr(SPRN_TBU40, new_tb + 0x1000000);
		vc->tb_offset_applied = 0;
	}

	mtspr(SPRN_HDEC, 0x7fffffff);
	mtspr(SPRN_LPCR, vcpu->kvm->arch.host_lpcr);

	return trap;
}