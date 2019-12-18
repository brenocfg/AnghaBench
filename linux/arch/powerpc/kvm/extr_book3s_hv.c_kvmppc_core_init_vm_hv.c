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
struct TYPE_3__ {unsigned long lpid; unsigned long host_lpcr; int vrma_slb_v; int radix; int mmu_ready; unsigned long lpcr; int threads_indep; int smt_mode; int emul_smt_mode; int /*<<< orphan*/  debugfs_dir; int /*<<< orphan*/  tlb_sets; int /*<<< orphan*/ * resize_hpt; void* host_lpid; void* host_sdr1; int /*<<< orphan*/  enabled_hcalls; int /*<<< orphan*/  need_tlb_flush; int /*<<< orphan*/  mmu_setup_lock; } ;
struct kvm {TYPE_1__ arch; } ;
typedef  int /*<<< orphan*/  buf ;
struct TYPE_4__ {int pid; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPU_FTR_ARCH_207S ; 
 int /*<<< orphan*/  CPU_FTR_ARCH_300 ; 
 int /*<<< orphan*/  CPU_FTR_HVMODE ; 
 int ENOMEM ; 
 unsigned long LPCR_DPFD_SH ; 
 unsigned long LPCR_GTSE ; 
 unsigned long LPCR_HDICE ; 
 unsigned long LPCR_HEIC ; 
 unsigned long LPCR_HR ; 
 unsigned long LPCR_HVICE ; 
 unsigned long LPCR_LPES ; 
 unsigned long LPCR_ONL ; 
 unsigned long LPCR_PECE ; 
 unsigned long LPCR_UPRT ; 
 unsigned long LPCR_VPM0 ; 
 unsigned long LPCR_VPM1 ; 
 int /*<<< orphan*/  POWER7_TLB_SETS ; 
 int /*<<< orphan*/  POWER8_TLB_SETS ; 
 int /*<<< orphan*/  POWER9_TLB_SETS_HASH ; 
 int /*<<< orphan*/  POWER9_TLB_SETS_RADIX ; 
 int SLB_VSID_B_1T ; 
 int SLB_VSID_SHIFT_1T ; 
 int /*<<< orphan*/  SPRN_LPCR ; 
 int /*<<< orphan*/  SPRN_LPID ; 
 int /*<<< orphan*/  SPRN_SDR1 ; 
 int VRMA_VSID ; 
 scalar_t__ cpu_has_feature (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpumask_setall (int /*<<< orphan*/ *) ; 
 TYPE_2__* current ; 
 int /*<<< orphan*/  debugfs_create_dir (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  default_enabled_hcalls ; 
 int indep_threads_mode ; 
 int /*<<< orphan*/  kvm_debugfs_dir ; 
 int /*<<< orphan*/  kvm_hv_vm_activated () ; 
 int /*<<< orphan*/  kvmhv_radix_debugfs_init (struct kvm*) ; 
 int /*<<< orphan*/  kvmhv_vm_nested_init (struct kvm*) ; 
 int /*<<< orphan*/  kvmppc_alloc_host_rm_ops () ; 
 unsigned long kvmppc_alloc_lpid () ; 
 int /*<<< orphan*/  kvmppc_free_lpid (unsigned long) ; 
 int kvmppc_init_vm_radix (struct kvm*) ; 
 int /*<<< orphan*/  kvmppc_mmu_debugfs_init (struct kvm*) ; 
 int /*<<< orphan*/  kvmppc_setup_partition_table (struct kvm*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 void* mfspr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_warn (char*) ; 
 scalar_t__ radix_enabled () ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 
 int threads_per_subcore ; 
 scalar_t__ xics_on_xive () ; 

__attribute__((used)) static int kvmppc_core_init_vm_hv(struct kvm *kvm)
{
	unsigned long lpcr, lpid;
	char buf[32];
	int ret;

	mutex_init(&kvm->arch.mmu_setup_lock);

	/* Allocate the guest's logical partition ID */

	lpid = kvmppc_alloc_lpid();
	if ((long)lpid < 0)
		return -ENOMEM;
	kvm->arch.lpid = lpid;

	kvmppc_alloc_host_rm_ops();

	kvmhv_vm_nested_init(kvm);

	/*
	 * Since we don't flush the TLB when tearing down a VM,
	 * and this lpid might have previously been used,
	 * make sure we flush on each core before running the new VM.
	 * On POWER9, the tlbie in mmu_partition_table_set_entry()
	 * does this flush for us.
	 */
	if (!cpu_has_feature(CPU_FTR_ARCH_300))
		cpumask_setall(&kvm->arch.need_tlb_flush);

	/* Start out with the default set of hcalls enabled */
	memcpy(kvm->arch.enabled_hcalls, default_enabled_hcalls,
	       sizeof(kvm->arch.enabled_hcalls));

	if (!cpu_has_feature(CPU_FTR_ARCH_300))
		kvm->arch.host_sdr1 = mfspr(SPRN_SDR1);

	/* Init LPCR for virtual RMA mode */
	if (cpu_has_feature(CPU_FTR_HVMODE)) {
		kvm->arch.host_lpid = mfspr(SPRN_LPID);
		kvm->arch.host_lpcr = lpcr = mfspr(SPRN_LPCR);
		lpcr &= LPCR_PECE | LPCR_LPES;
	} else {
		lpcr = 0;
	}
	lpcr |= (4UL << LPCR_DPFD_SH) | LPCR_HDICE |
		LPCR_VPM0 | LPCR_VPM1;
	kvm->arch.vrma_slb_v = SLB_VSID_B_1T |
		(VRMA_VSID << SLB_VSID_SHIFT_1T);
	/* On POWER8 turn on online bit to enable PURR/SPURR */
	if (cpu_has_feature(CPU_FTR_ARCH_207S))
		lpcr |= LPCR_ONL;
	/*
	 * On POWER9, VPM0 bit is reserved (VPM0=1 behaviour is assumed)
	 * Set HVICE bit to enable hypervisor virtualization interrupts.
	 * Set HEIC to prevent OS interrupts to go to hypervisor (should
	 * be unnecessary but better safe than sorry in case we re-enable
	 * EE in HV mode with this LPCR still set)
	 */
	if (cpu_has_feature(CPU_FTR_ARCH_300)) {
		lpcr &= ~LPCR_VPM0;
		lpcr |= LPCR_HVICE | LPCR_HEIC;

		/*
		 * If xive is enabled, we route 0x500 interrupts directly
		 * to the guest.
		 */
		if (xics_on_xive())
			lpcr |= LPCR_LPES;
	}

	/*
	 * If the host uses radix, the guest starts out as radix.
	 */
	if (radix_enabled()) {
		kvm->arch.radix = 1;
		kvm->arch.mmu_ready = 1;
		lpcr &= ~LPCR_VPM1;
		lpcr |= LPCR_UPRT | LPCR_GTSE | LPCR_HR;
		ret = kvmppc_init_vm_radix(kvm);
		if (ret) {
			kvmppc_free_lpid(kvm->arch.lpid);
			return ret;
		}
		kvmppc_setup_partition_table(kvm);
	}

	kvm->arch.lpcr = lpcr;

	/* Initialization for future HPT resizes */
	kvm->arch.resize_hpt = NULL;

	/*
	 * Work out how many sets the TLB has, for the use of
	 * the TLB invalidation loop in book3s_hv_rmhandlers.S.
	 */
	if (radix_enabled())
		kvm->arch.tlb_sets = POWER9_TLB_SETS_RADIX;	/* 128 */
	else if (cpu_has_feature(CPU_FTR_ARCH_300))
		kvm->arch.tlb_sets = POWER9_TLB_SETS_HASH;	/* 256 */
	else if (cpu_has_feature(CPU_FTR_ARCH_207S))
		kvm->arch.tlb_sets = POWER8_TLB_SETS;		/* 512 */
	else
		kvm->arch.tlb_sets = POWER7_TLB_SETS;		/* 128 */

	/*
	 * Track that we now have a HV mode VM active. This blocks secondary
	 * CPU threads from coming online.
	 * On POWER9, we only need to do this if the "indep_threads_mode"
	 * module parameter has been set to N.
	 */
	if (cpu_has_feature(CPU_FTR_ARCH_300)) {
		if (!indep_threads_mode && !cpu_has_feature(CPU_FTR_HVMODE)) {
			pr_warn("KVM: Ignoring indep_threads_mode=N in nested hypervisor\n");
			kvm->arch.threads_indep = true;
		} else {
			kvm->arch.threads_indep = indep_threads_mode;
		}
	}
	if (!kvm->arch.threads_indep)
		kvm_hv_vm_activated();

	/*
	 * Initialize smt_mode depending on processor.
	 * POWER8 and earlier have to use "strict" threading, where
	 * all vCPUs in a vcore have to run on the same (sub)core,
	 * whereas on POWER9 the threads can each run a different
	 * guest.
	 */
	if (!cpu_has_feature(CPU_FTR_ARCH_300))
		kvm->arch.smt_mode = threads_per_subcore;
	else
		kvm->arch.smt_mode = 1;
	kvm->arch.emul_smt_mode = 1;

	/*
	 * Create a debugfs directory for the VM
	 */
	snprintf(buf, sizeof(buf), "vm%d", current->pid);
	kvm->arch.debugfs_dir = debugfs_create_dir(buf, kvm_debugfs_dir);
	kvmppc_mmu_debugfs_init(kvm);
	if (radix_enabled())
		kvmhv_radix_debugfs_init(kvm);

	return 0;
}