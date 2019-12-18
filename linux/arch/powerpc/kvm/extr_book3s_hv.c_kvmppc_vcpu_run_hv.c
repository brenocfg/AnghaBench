#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_9__ ;
typedef  struct TYPE_19__   TYPE_8__ ;
typedef  struct TYPE_18__   TYPE_7__ ;
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u64 ;
struct TYPE_16__ {int msr; } ;
struct TYPE_18__ {int online; int /*<<< orphan*/  state; int /*<<< orphan*/  fault_dsisr; int /*<<< orphan*/  fault_dar; TYPE_5__ shregs; TYPE_4__* vcore; int /*<<< orphan*/  pgdir; int /*<<< orphan*/ * wqp; int /*<<< orphan*/  sane; } ;
struct kvm_vcpu {TYPE_7__ arch; struct kvm* kvm; } ;
struct TYPE_12__ {scalar_t__ hardware_entry_failure_reason; } ;
struct kvm_run {scalar_t__ exit_reason; TYPE_1__ fail_entry; } ;
struct TYPE_19__ {int /*<<< orphan*/  vcpus_running; scalar_t__ threads_indep; } ;
struct kvm {TYPE_8__ arch; int /*<<< orphan*/  srcu; } ;
struct TYPE_17__ {unsigned int fscr; TYPE_2__* regs; void* tm_texasr; void* tm_tfiar; void* tm_tfhar; } ;
struct TYPE_20__ {TYPE_6__ thread; TYPE_3__* mm; } ;
struct TYPE_15__ {int /*<<< orphan*/  lpcr; int /*<<< orphan*/  wq; int /*<<< orphan*/  online_count; } ;
struct TYPE_14__ {int /*<<< orphan*/  pgd; } ;
struct TYPE_13__ {int msr; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPU_FTR_ARCH_207S ; 
 int /*<<< orphan*/  CPU_FTR_TM ; 
 int EINTR ; 
 int EINVAL ; 
 int H_SUCCESS ; 
 int /*<<< orphan*/  KVMPPC_VCPU_BUSY_IN_HOST ; 
 int /*<<< orphan*/  KVMPPC_VCPU_NOTREADY ; 
 scalar_t__ KVM_EXIT_FAIL_ENTRY ; 
 scalar_t__ KVM_EXIT_INTERNAL_ERROR ; 
 scalar_t__ KVM_EXIT_INTR ; 
 scalar_t__ KVM_EXIT_PAPR_HCALL ; 
 int MSR_PR ; 
 int MSR_TM ; 
 scalar_t__ MSR_TM_ACTIVE (int) ; 
 int RESUME_PAGE_FAULT ; 
 int RESUME_PASSTHROUGH ; 
 int /*<<< orphan*/  SPRN_BESCR ; 
 int /*<<< orphan*/  SPRN_EBBHR ; 
 int /*<<< orphan*/  SPRN_EBBRR ; 
 int /*<<< orphan*/  SPRN_FSCR ; 
 int /*<<< orphan*/  SPRN_TAR ; 
 int /*<<< orphan*/  SPRN_TEXASR ; 
 int /*<<< orphan*/  SPRN_TFHAR ; 
 int /*<<< orphan*/  SPRN_TFIAR ; 
 int /*<<< orphan*/  SPRN_VRSAVE ; 
 scalar_t__ WARN_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 scalar_t__ cpu_has_feature (int /*<<< orphan*/ ) ; 
 TYPE_9__* current ; 
 int /*<<< orphan*/  flush_all_to_thread (TYPE_9__*) ; 
 scalar_t__ is_kvmppc_resume_guest (int) ; 
 scalar_t__ kvm_is_radix (struct kvm*) ; 
 int kvmhv_run_single_vcpu (struct kvm_run*,struct kvm_vcpu*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int kvmppc_book3s_hv_page_fault (struct kvm_run*,struct kvm_vcpu*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvmppc_core_prepare_to_enter (struct kvm_vcpu*) ; 
 int kvmppc_pseries_do_hcall (struct kvm_vcpu*) ; 
 int kvmppc_run_vcpu (struct kvm_run*,struct kvm_vcpu*) ; 
 int kvmppc_xics_rm_complete (struct kvm_vcpu*,int /*<<< orphan*/ ) ; 
 int mfmsr () ; 
 void* mfspr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtmsr (int) ; 
 int /*<<< orphan*/  mtspr (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  no_mixing_hpt_and_radix ; 
 scalar_t__ signal_pending (TYPE_9__*) ; 
 int /*<<< orphan*/  smp_mb () ; 
 int srcu_read_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  srcu_read_unlock (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  trace_kvm_hcall_enter (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  trace_kvm_hcall_exit (struct kvm_vcpu*,int) ; 
 int /*<<< orphan*/  xics_on_xive () ; 

__attribute__((used)) static int kvmppc_vcpu_run_hv(struct kvm_run *run, struct kvm_vcpu *vcpu)
{
	int r;
	int srcu_idx;
	unsigned long ebb_regs[3] = {};	/* shut up GCC */
	unsigned long user_tar = 0;
	unsigned int user_vrsave;
	struct kvm *kvm;

	if (!vcpu->arch.sane) {
		run->exit_reason = KVM_EXIT_INTERNAL_ERROR;
		return -EINVAL;
	}

	/*
	 * Don't allow entry with a suspended transaction, because
	 * the guest entry/exit code will lose it.
	 * If the guest has TM enabled, save away their TM-related SPRs
	 * (they will get restored by the TM unavailable interrupt).
	 */
#ifdef CONFIG_PPC_TRANSACTIONAL_MEM
	if (cpu_has_feature(CPU_FTR_TM) && current->thread.regs &&
	    (current->thread.regs->msr & MSR_TM)) {
		if (MSR_TM_ACTIVE(current->thread.regs->msr)) {
			run->exit_reason = KVM_EXIT_FAIL_ENTRY;
			run->fail_entry.hardware_entry_failure_reason = 0;
			return -EINVAL;
		}
		/* Enable TM so we can read the TM SPRs */
		mtmsr(mfmsr() | MSR_TM);
		current->thread.tm_tfhar = mfspr(SPRN_TFHAR);
		current->thread.tm_tfiar = mfspr(SPRN_TFIAR);
		current->thread.tm_texasr = mfspr(SPRN_TEXASR);
		current->thread.regs->msr &= ~MSR_TM;
	}
#endif

	/*
	 * Force online to 1 for the sake of old userspace which doesn't
	 * set it.
	 */
	if (!vcpu->arch.online) {
		atomic_inc(&vcpu->arch.vcore->online_count);
		vcpu->arch.online = 1;
	}

	kvmppc_core_prepare_to_enter(vcpu);

	/* No need to go into the guest when all we'll do is come back out */
	if (signal_pending(current)) {
		run->exit_reason = KVM_EXIT_INTR;
		return -EINTR;
	}

	kvm = vcpu->kvm;
	atomic_inc(&kvm->arch.vcpus_running);
	/* Order vcpus_running vs. mmu_ready, see kvmppc_alloc_reset_hpt */
	smp_mb();

	flush_all_to_thread(current);

	/* Save userspace EBB and other register values */
	if (cpu_has_feature(CPU_FTR_ARCH_207S)) {
		ebb_regs[0] = mfspr(SPRN_EBBHR);
		ebb_regs[1] = mfspr(SPRN_EBBRR);
		ebb_regs[2] = mfspr(SPRN_BESCR);
		user_tar = mfspr(SPRN_TAR);
	}
	user_vrsave = mfspr(SPRN_VRSAVE);

	vcpu->arch.wqp = &vcpu->arch.vcore->wq;
	vcpu->arch.pgdir = current->mm->pgd;
	vcpu->arch.state = KVMPPC_VCPU_BUSY_IN_HOST;

	do {
		/*
		 * The early POWER9 chips that can't mix radix and HPT threads
		 * on the same core also need the workaround for the problem
		 * where the TLB would prefetch entries in the guest exit path
		 * for radix guests using the guest PIDR value and LPID 0.
		 * The workaround is in the old path (kvmppc_run_vcpu())
		 * but not the new path (kvmhv_run_single_vcpu()).
		 */
		if (kvm->arch.threads_indep && kvm_is_radix(kvm) &&
		    !no_mixing_hpt_and_radix)
			r = kvmhv_run_single_vcpu(run, vcpu, ~(u64)0,
						  vcpu->arch.vcore->lpcr);
		else
			r = kvmppc_run_vcpu(run, vcpu);

		if (run->exit_reason == KVM_EXIT_PAPR_HCALL &&
		    !(vcpu->arch.shregs.msr & MSR_PR)) {
			trace_kvm_hcall_enter(vcpu);
			r = kvmppc_pseries_do_hcall(vcpu);
			trace_kvm_hcall_exit(vcpu, r);
			kvmppc_core_prepare_to_enter(vcpu);
		} else if (r == RESUME_PAGE_FAULT) {
			srcu_idx = srcu_read_lock(&kvm->srcu);
			r = kvmppc_book3s_hv_page_fault(run, vcpu,
				vcpu->arch.fault_dar, vcpu->arch.fault_dsisr);
			srcu_read_unlock(&kvm->srcu, srcu_idx);
		} else if (r == RESUME_PASSTHROUGH) {
			if (WARN_ON(xics_on_xive()))
				r = H_SUCCESS;
			else
				r = kvmppc_xics_rm_complete(vcpu, 0);
		}
	} while (is_kvmppc_resume_guest(r));

	/* Restore userspace EBB and other register values */
	if (cpu_has_feature(CPU_FTR_ARCH_207S)) {
		mtspr(SPRN_EBBHR, ebb_regs[0]);
		mtspr(SPRN_EBBRR, ebb_regs[1]);
		mtspr(SPRN_BESCR, ebb_regs[2]);
		mtspr(SPRN_TAR, user_tar);
		mtspr(SPRN_FSCR, current->thread.fscr);
	}
	mtspr(SPRN_VRSAVE, user_vrsave);

	vcpu->arch.state = KVMPPC_VCPU_NOTREADY;
	atomic_dec(&kvm->arch.vcpus_running);
	return r;
}