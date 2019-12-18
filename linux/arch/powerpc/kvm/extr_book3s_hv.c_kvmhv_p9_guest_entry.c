#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_8__ ;
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  void* u64 ;
typedef  scalar_t__ u32 ;
struct lppaca {int pmcregs_in_use; void* yield_count; } ;
struct kvmppc_vcore {int entry_exit_map; int in_guest; } ;
struct TYPE_13__ {int dirty; struct lppaca* pinned_addr; } ;
struct TYPE_11__ {unsigned long dar; unsigned long dsisr; int /*<<< orphan*/  msr; } ;
struct hv_guest_state {unsigned long lpcr; int /*<<< orphan*/  msr; void* hdec_expiry; int /*<<< orphan*/  vcpu_token; int /*<<< orphan*/  lpid; int /*<<< orphan*/  version; } ;
struct TYPE_14__ {unsigned long vrsave; unsigned long dscr; unsigned long iamr; unsigned long pspb; unsigned long fscr; unsigned long tar; unsigned long ebbhr; unsigned long ebbrr; unsigned long bescr; unsigned long wort; unsigned long tid; unsigned long amr; unsigned long uamor; int ctrl; unsigned long dec_expires; unsigned long psscr; int thread_cpu; TYPE_5__ vpa; TYPE_3__ shregs; int /*<<< orphan*/  vr; int /*<<< orphan*/  fp; scalar_t__ slb_max; TYPE_2__* nested; struct hv_guest_state regs; int /*<<< orphan*/  nested_vcpu_id; scalar_t__ ceded; struct kvmppc_vcore* vcore; } ;
struct kvm_vcpu {int cpu; TYPE_7__* kvm; TYPE_6__ arch; int /*<<< orphan*/  vcpu_id; } ;
typedef  int s64 ;
typedef  int s32 ;
struct TYPE_12__ {unsigned long dec_expires; } ;
struct TYPE_16__ {unsigned long sprg_vdso; TYPE_4__ kvm_hstate; } ;
struct TYPE_9__ {int /*<<< orphan*/  lpid; } ;
struct TYPE_15__ {TYPE_1__ arch; } ;
struct TYPE_10__ {int /*<<< orphan*/  shadow_lpid; } ;

/* Variables and functions */
 int BOOK3S_INTERRUPT_HV_DECREMENTER ; 
 int BOOK3S_INTERRUPT_SYSCALL ; 
 int /*<<< orphan*/  CPU_FTR_P9_TM_HV_ASSIST ; 
 int /*<<< orphan*/  CPU_FTR_TM ; 
 int /*<<< orphan*/  HV_GUEST_STATE_VERSION ; 
 scalar_t__ H_CEDE ; 
 int /*<<< orphan*/  H_ENTER_NESTED ; 
 unsigned long LPCR_LD ; 
 int MSR_FP ; 
 int MSR_VEC ; 
 int MSR_VSX ; 
 int /*<<< orphan*/  SPRN_AMR ; 
 int /*<<< orphan*/  SPRN_BESCR ; 
 int /*<<< orphan*/  SPRN_CTRLF ; 
 int /*<<< orphan*/  SPRN_CTRLT ; 
 int /*<<< orphan*/  SPRN_DAR ; 
 int /*<<< orphan*/  SPRN_DEC ; 
 int /*<<< orphan*/  SPRN_DSCR ; 
 int /*<<< orphan*/  SPRN_DSISR ; 
 int /*<<< orphan*/  SPRN_EBBHR ; 
 int /*<<< orphan*/  SPRN_EBBRR ; 
 int /*<<< orphan*/  SPRN_FSCR ; 
 int /*<<< orphan*/  SPRN_IAMR ; 
 int /*<<< orphan*/  SPRN_PSPB ; 
 int /*<<< orphan*/  SPRN_PSSCR_PR ; 
 int /*<<< orphan*/  SPRN_SPRG_VDSO_WRITE ; 
 int /*<<< orphan*/  SPRN_TAR ; 
 int /*<<< orphan*/  SPRN_TIDR ; 
 int /*<<< orphan*/  SPRN_UAMOR ; 
 int /*<<< orphan*/  SPRN_VRSAVE ; 
 int /*<<< orphan*/  SPRN_WORT ; 
 int /*<<< orphan*/  __pa (struct hv_guest_state*) ; 
 scalar_t__ be32_to_cpu (void*) ; 
 scalar_t__ cpu_has_feature (int /*<<< orphan*/ ) ; 
 void* cpu_to_be32 (scalar_t__) ; 
 int /*<<< orphan*/  kvmhv_load_guest_pmu (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  kvmhv_load_host_pmu () ; 
 int kvmhv_load_hv_regs_and_go (struct kvm_vcpu*,void*,unsigned long) ; 
 scalar_t__ kvmhv_on_pseries () ; 
 int /*<<< orphan*/  kvmhv_restore_hv_return_state (struct kvm_vcpu*,struct hv_guest_state*) ; 
 int /*<<< orphan*/  kvmhv_save_guest_pmu (struct kvm_vcpu*,int) ; 
 int /*<<< orphan*/  kvmhv_save_host_pmu () ; 
 int /*<<< orphan*/  kvmhv_save_hv_regs (struct kvm_vcpu*,struct hv_guest_state*) ; 
 scalar_t__ kvmppc_get_gpr (struct kvm_vcpu*,int) ; 
 int /*<<< orphan*/  kvmppc_nested_cede (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  kvmppc_restore_tm_hv (struct kvm_vcpu*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  kvmppc_save_tm_hv (struct kvm_vcpu*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  kvmppc_subcore_enter_guest () ; 
 int /*<<< orphan*/  kvmppc_subcore_exit_guest () ; 
 int /*<<< orphan*/  load_fp_state (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  load_vr_state (int /*<<< orphan*/ *) ; 
 TYPE_8__* local_paca ; 
 int mfspr (int /*<<< orphan*/ ) ; 
 unsigned long mftb () ; 
 int /*<<< orphan*/  msr_check_and_set (int) ; 
 int /*<<< orphan*/  mtspr (int /*<<< orphan*/ ,unsigned long) ; 
 int nesting_enabled (TYPE_7__*) ; 
 int plpar_hcall_norets (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  store_fp_state (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  store_vr_state (int /*<<< orphan*/ *) ; 

int kvmhv_p9_guest_entry(struct kvm_vcpu *vcpu, u64 time_limit,
			 unsigned long lpcr)
{
	struct kvmppc_vcore *vc = vcpu->arch.vcore;
	unsigned long host_dscr = mfspr(SPRN_DSCR);
	unsigned long host_tidr = mfspr(SPRN_TIDR);
	unsigned long host_iamr = mfspr(SPRN_IAMR);
	unsigned long host_amr = mfspr(SPRN_AMR);
	s64 dec;
	u64 tb;
	int trap, save_pmu;

	dec = mfspr(SPRN_DEC);
	tb = mftb();
	if (dec < 512)
		return BOOK3S_INTERRUPT_HV_DECREMENTER;
	local_paca->kvm_hstate.dec_expires = dec + tb;
	if (local_paca->kvm_hstate.dec_expires < time_limit)
		time_limit = local_paca->kvm_hstate.dec_expires;

	vcpu->arch.ceded = 0;

	kvmhv_save_host_pmu();		/* saves it to PACA kvm_hstate */

	kvmppc_subcore_enter_guest();

	vc->entry_exit_map = 1;
	vc->in_guest = 1;

	if (vcpu->arch.vpa.pinned_addr) {
		struct lppaca *lp = vcpu->arch.vpa.pinned_addr;
		u32 yield_count = be32_to_cpu(lp->yield_count) + 1;
		lp->yield_count = cpu_to_be32(yield_count);
		vcpu->arch.vpa.dirty = 1;
	}

	if (cpu_has_feature(CPU_FTR_TM) ||
	    cpu_has_feature(CPU_FTR_P9_TM_HV_ASSIST))
		kvmppc_restore_tm_hv(vcpu, vcpu->arch.shregs.msr, true);

	kvmhv_load_guest_pmu(vcpu);

	msr_check_and_set(MSR_FP | MSR_VEC | MSR_VSX);
	load_fp_state(&vcpu->arch.fp);
#ifdef CONFIG_ALTIVEC
	load_vr_state(&vcpu->arch.vr);
#endif
	mtspr(SPRN_VRSAVE, vcpu->arch.vrsave);

	mtspr(SPRN_DSCR, vcpu->arch.dscr);
	mtspr(SPRN_IAMR, vcpu->arch.iamr);
	mtspr(SPRN_PSPB, vcpu->arch.pspb);
	mtspr(SPRN_FSCR, vcpu->arch.fscr);
	mtspr(SPRN_TAR, vcpu->arch.tar);
	mtspr(SPRN_EBBHR, vcpu->arch.ebbhr);
	mtspr(SPRN_EBBRR, vcpu->arch.ebbrr);
	mtspr(SPRN_BESCR, vcpu->arch.bescr);
	mtspr(SPRN_WORT, vcpu->arch.wort);
	mtspr(SPRN_TIDR, vcpu->arch.tid);
	mtspr(SPRN_DAR, vcpu->arch.shregs.dar);
	mtspr(SPRN_DSISR, vcpu->arch.shregs.dsisr);
	mtspr(SPRN_AMR, vcpu->arch.amr);
	mtspr(SPRN_UAMOR, vcpu->arch.uamor);

	if (!(vcpu->arch.ctrl & 1))
		mtspr(SPRN_CTRLT, mfspr(SPRN_CTRLF) & ~1);

	mtspr(SPRN_DEC, vcpu->arch.dec_expires - mftb());

	if (kvmhv_on_pseries()) {
		/*
		 * We need to save and restore the guest visible part of the
		 * psscr (i.e. using SPRN_PSSCR_PR) since the hypervisor
		 * doesn't do this for us. Note only required if pseries since
		 * this is done in kvmhv_load_hv_regs_and_go() below otherwise.
		 */
		unsigned long host_psscr;
		/* call our hypervisor to load up HV regs and go */
		struct hv_guest_state hvregs;

		host_psscr = mfspr(SPRN_PSSCR_PR);
		mtspr(SPRN_PSSCR_PR, vcpu->arch.psscr);
		kvmhv_save_hv_regs(vcpu, &hvregs);
		hvregs.lpcr = lpcr;
		vcpu->arch.regs.msr = vcpu->arch.shregs.msr;
		hvregs.version = HV_GUEST_STATE_VERSION;
		if (vcpu->arch.nested) {
			hvregs.lpid = vcpu->arch.nested->shadow_lpid;
			hvregs.vcpu_token = vcpu->arch.nested_vcpu_id;
		} else {
			hvregs.lpid = vcpu->kvm->arch.lpid;
			hvregs.vcpu_token = vcpu->vcpu_id;
		}
		hvregs.hdec_expiry = time_limit;
		trap = plpar_hcall_norets(H_ENTER_NESTED, __pa(&hvregs),
					  __pa(&vcpu->arch.regs));
		kvmhv_restore_hv_return_state(vcpu, &hvregs);
		vcpu->arch.shregs.msr = vcpu->arch.regs.msr;
		vcpu->arch.shregs.dar = mfspr(SPRN_DAR);
		vcpu->arch.shregs.dsisr = mfspr(SPRN_DSISR);
		vcpu->arch.psscr = mfspr(SPRN_PSSCR_PR);
		mtspr(SPRN_PSSCR_PR, host_psscr);

		/* H_CEDE has to be handled now, not later */
		if (trap == BOOK3S_INTERRUPT_SYSCALL && !vcpu->arch.nested &&
		    kvmppc_get_gpr(vcpu, 3) == H_CEDE) {
			kvmppc_nested_cede(vcpu);
			trap = 0;
		}
	} else {
		trap = kvmhv_load_hv_regs_and_go(vcpu, time_limit, lpcr);
	}

	vcpu->arch.slb_max = 0;
	dec = mfspr(SPRN_DEC);
	if (!(lpcr & LPCR_LD)) /* Sign extend if not using large decrementer */
		dec = (s32) dec;
	tb = mftb();
	vcpu->arch.dec_expires = dec + tb;
	vcpu->cpu = -1;
	vcpu->arch.thread_cpu = -1;
	vcpu->arch.ctrl = mfspr(SPRN_CTRLF);

	vcpu->arch.iamr = mfspr(SPRN_IAMR);
	vcpu->arch.pspb = mfspr(SPRN_PSPB);
	vcpu->arch.fscr = mfspr(SPRN_FSCR);
	vcpu->arch.tar = mfspr(SPRN_TAR);
	vcpu->arch.ebbhr = mfspr(SPRN_EBBHR);
	vcpu->arch.ebbrr = mfspr(SPRN_EBBRR);
	vcpu->arch.bescr = mfspr(SPRN_BESCR);
	vcpu->arch.wort = mfspr(SPRN_WORT);
	vcpu->arch.tid = mfspr(SPRN_TIDR);
	vcpu->arch.amr = mfspr(SPRN_AMR);
	vcpu->arch.uamor = mfspr(SPRN_UAMOR);
	vcpu->arch.dscr = mfspr(SPRN_DSCR);

	mtspr(SPRN_PSPB, 0);
	mtspr(SPRN_WORT, 0);
	mtspr(SPRN_UAMOR, 0);
	mtspr(SPRN_DSCR, host_dscr);
	mtspr(SPRN_TIDR, host_tidr);
	mtspr(SPRN_IAMR, host_iamr);
	mtspr(SPRN_PSPB, 0);

	if (host_amr != vcpu->arch.amr)
		mtspr(SPRN_AMR, host_amr);

	msr_check_and_set(MSR_FP | MSR_VEC | MSR_VSX);
	store_fp_state(&vcpu->arch.fp);
#ifdef CONFIG_ALTIVEC
	store_vr_state(&vcpu->arch.vr);
#endif
	vcpu->arch.vrsave = mfspr(SPRN_VRSAVE);

	if (cpu_has_feature(CPU_FTR_TM) ||
	    cpu_has_feature(CPU_FTR_P9_TM_HV_ASSIST))
		kvmppc_save_tm_hv(vcpu, vcpu->arch.shregs.msr, true);

	save_pmu = 1;
	if (vcpu->arch.vpa.pinned_addr) {
		struct lppaca *lp = vcpu->arch.vpa.pinned_addr;
		u32 yield_count = be32_to_cpu(lp->yield_count) + 1;
		lp->yield_count = cpu_to_be32(yield_count);
		vcpu->arch.vpa.dirty = 1;
		save_pmu = lp->pmcregs_in_use;
	}
	/* Must save pmu if this guest is capable of running nested guests */
	save_pmu |= nesting_enabled(vcpu->kvm);

	kvmhv_save_guest_pmu(vcpu, save_pmu);

	vc->entry_exit_map = 0x101;
	vc->in_guest = 0;

	mtspr(SPRN_DEC, local_paca->kvm_hstate.dec_expires - mftb());
	mtspr(SPRN_SPRG_VDSO_WRITE, local_paca->sprg_vdso);

	kvmhv_load_host_pmu();

	kvmppc_subcore_exit_guest();

	return trap;
}