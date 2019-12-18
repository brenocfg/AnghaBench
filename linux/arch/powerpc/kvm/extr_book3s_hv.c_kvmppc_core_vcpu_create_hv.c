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
struct kvmppc_vcore {scalar_t__ first_vcpuid; int /*<<< orphan*/  lock; int /*<<< orphan*/  num_threads; } ;
struct TYPE_4__ {int shared_big_endian; int intr_msr; int hfscr; int thread_cpu; int prev_cpu; int /*<<< orphan*/  cpu_type; scalar_t__ ptid; struct kvmppc_vcore* vcore; int /*<<< orphan*/  cpu_run; int /*<<< orphan*/  state; int /*<<< orphan*/  busy_preempt; int /*<<< orphan*/  tbacct_lock; int /*<<< orphan*/  vpa_update_lock; int /*<<< orphan*/  ctrl; int /*<<< orphan*/ * mmcr; int /*<<< orphan*/  shregs; int /*<<< orphan*/ * shared; } ;
struct kvm_vcpu {TYPE_2__ arch; scalar_t__ vcpu_id; } ;
struct TYPE_3__ {unsigned int emul_smt_mode; int smt_mode; int /*<<< orphan*/  mmu_setup_lock; int /*<<< orphan*/  online_vcores; struct kvmppc_vcore** vcores; } ;
struct kvm {int /*<<< orphan*/  lock; TYPE_1__ arch; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  CPU_FTR_ARCH_300 ; 
 int /*<<< orphan*/  CPU_FTR_HVMODE ; 
 int /*<<< orphan*/  CPU_FTR_P9_TM_HV_ASSIST ; 
 int /*<<< orphan*/  CPU_FTR_TM_COMP ; 
 int /*<<< orphan*/  CTRL_RUNLATCH ; 
 int EINVAL ; 
 int ENOMEM ; 
 struct kvm_vcpu* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int HFSCR_BHRB ; 
 int HFSCR_DSCR ; 
 int HFSCR_EBB ; 
 int HFSCR_FP ; 
 int HFSCR_PM ; 
 int HFSCR_TAR ; 
 int HFSCR_TM ; 
 int HFSCR_VECVSX ; 
 int /*<<< orphan*/  KVMPPC_VCPU_NOTREADY ; 
 int /*<<< orphan*/  KVM_CPU_3S_64 ; 
 int KVM_MAX_VCORES ; 
 unsigned int KVM_MAX_VCPUS ; 
 int /*<<< orphan*/  MMCR0_FC ; 
 int MSR_ME ; 
 int MSR_SF ; 
 int /*<<< orphan*/  SPRN_HFSCR ; 
 int /*<<< orphan*/  SPRN_PVR ; 
 int /*<<< orphan*/  TB_NIL ; 
 scalar_t__ cpu_has_feature (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debugfs_vcpu_init (struct kvm_vcpu*,unsigned int) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kmem_cache_free (int /*<<< orphan*/ ,struct kvm_vcpu*) ; 
 struct kvm_vcpu* kmem_cache_zalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvm_vcpu_cache ; 
 int kvm_vcpu_init (struct kvm_vcpu*,struct kvm*,unsigned int) ; 
 int /*<<< orphan*/  kvmppc_mmu_book3s_hv_init (struct kvm_vcpu*) ; 
 int kvmppc_pack_vcpu_id (struct kvm*,unsigned int) ; 
 int /*<<< orphan*/  kvmppc_sanity_check (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  kvmppc_set_pvr_hv (struct kvm_vcpu*,int) ; 
 struct kvmppc_vcore* kvmppc_vcore_create (struct kvm*,unsigned int) ; 
 int mfspr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_devel (char*,...) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct kvm_vcpu *kvmppc_core_vcpu_create_hv(struct kvm *kvm,
						   unsigned int id)
{
	struct kvm_vcpu *vcpu;
	int err;
	int core;
	struct kvmppc_vcore *vcore;

	err = -ENOMEM;
	vcpu = kmem_cache_zalloc(kvm_vcpu_cache, GFP_KERNEL);
	if (!vcpu)
		goto out;

	err = kvm_vcpu_init(vcpu, kvm, id);
	if (err)
		goto free_vcpu;

	vcpu->arch.shared = &vcpu->arch.shregs;
#ifdef CONFIG_KVM_BOOK3S_PR_POSSIBLE
	/*
	 * The shared struct is never shared on HV,
	 * so we can always use host endianness
	 */
#ifdef __BIG_ENDIAN__
	vcpu->arch.shared_big_endian = true;
#else
	vcpu->arch.shared_big_endian = false;
#endif
#endif
	vcpu->arch.mmcr[0] = MMCR0_FC;
	vcpu->arch.ctrl = CTRL_RUNLATCH;
	/* default to host PVR, since we can't spoof it */
	kvmppc_set_pvr_hv(vcpu, mfspr(SPRN_PVR));
	spin_lock_init(&vcpu->arch.vpa_update_lock);
	spin_lock_init(&vcpu->arch.tbacct_lock);
	vcpu->arch.busy_preempt = TB_NIL;
	vcpu->arch.intr_msr = MSR_SF | MSR_ME;

	/*
	 * Set the default HFSCR for the guest from the host value.
	 * This value is only used on POWER9.
	 * On POWER9, we want to virtualize the doorbell facility, so we
	 * don't set the HFSCR_MSGP bit, and that causes those instructions
	 * to trap and then we emulate them.
	 */
	vcpu->arch.hfscr = HFSCR_TAR | HFSCR_EBB | HFSCR_PM | HFSCR_BHRB |
		HFSCR_DSCR | HFSCR_VECVSX | HFSCR_FP;
	if (cpu_has_feature(CPU_FTR_HVMODE)) {
		vcpu->arch.hfscr &= mfspr(SPRN_HFSCR);
		if (cpu_has_feature(CPU_FTR_P9_TM_HV_ASSIST))
			vcpu->arch.hfscr |= HFSCR_TM;
	}
	if (cpu_has_feature(CPU_FTR_TM_COMP))
		vcpu->arch.hfscr |= HFSCR_TM;

	kvmppc_mmu_book3s_hv_init(vcpu);

	vcpu->arch.state = KVMPPC_VCPU_NOTREADY;

	init_waitqueue_head(&vcpu->arch.cpu_run);

	mutex_lock(&kvm->lock);
	vcore = NULL;
	err = -EINVAL;
	if (cpu_has_feature(CPU_FTR_ARCH_300)) {
		if (id >= (KVM_MAX_VCPUS * kvm->arch.emul_smt_mode)) {
			pr_devel("KVM: VCPU ID too high\n");
			core = KVM_MAX_VCORES;
		} else {
			BUG_ON(kvm->arch.smt_mode != 1);
			core = kvmppc_pack_vcpu_id(kvm, id);
		}
	} else {
		core = id / kvm->arch.smt_mode;
	}
	if (core < KVM_MAX_VCORES) {
		vcore = kvm->arch.vcores[core];
		if (vcore && cpu_has_feature(CPU_FTR_ARCH_300)) {
			pr_devel("KVM: collision on id %u", id);
			vcore = NULL;
		} else if (!vcore) {
			/*
			 * Take mmu_setup_lock for mutual exclusion
			 * with kvmppc_update_lpcr().
			 */
			err = -ENOMEM;
			vcore = kvmppc_vcore_create(kvm,
					id & ~(kvm->arch.smt_mode - 1));
			mutex_lock(&kvm->arch.mmu_setup_lock);
			kvm->arch.vcores[core] = vcore;
			kvm->arch.online_vcores++;
			mutex_unlock(&kvm->arch.mmu_setup_lock);
		}
	}
	mutex_unlock(&kvm->lock);

	if (!vcore)
		goto free_vcpu;

	spin_lock(&vcore->lock);
	++vcore->num_threads;
	spin_unlock(&vcore->lock);
	vcpu->arch.vcore = vcore;
	vcpu->arch.ptid = vcpu->vcpu_id - vcore->first_vcpuid;
	vcpu->arch.thread_cpu = -1;
	vcpu->arch.prev_cpu = -1;

	vcpu->arch.cpu_type = KVM_CPU_3S_64;
	kvmppc_sanity_check(vcpu);

	debugfs_vcpu_init(vcpu, id);

	return vcpu;

free_vcpu:
	kmem_cache_free(kvm_vcpu_cache, vcpu);
out:
	return ERR_PTR(err);
}