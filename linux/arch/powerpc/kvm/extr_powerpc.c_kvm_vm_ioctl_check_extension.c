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
struct TYPE_4__ {int emul_smt_mode; int smt_mode; } ;
struct kvm {TYPE_1__ arch; } ;
struct TYPE_6__ {int cpu_user_features2; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* enable_nested ) (int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  CPU_FTR_ARCH_300 ; 
 int /*<<< orphan*/  CPU_FTR_HVMODE ; 
 int /*<<< orphan*/  CPU_FTR_P9_TM_HV_ASSIST ; 
#define  KVM_CAP_DEVICE_CTRL 172 
#define  KVM_CAP_ENABLE_CAP 171 
#define  KVM_CAP_IMMEDIATE_EXIT 170 
#define  KVM_CAP_IOEVENTFD 169 
#define  KVM_CAP_IRQ_MPIC 168 
#define  KVM_CAP_IRQ_XICS 167 
#define  KVM_CAP_MAX_VCPUS 166 
#define  KVM_CAP_MAX_VCPU_ID 165 
#define  KVM_CAP_NR_VCPUS 164 
#define  KVM_CAP_ONE_REG 163 
#define  KVM_CAP_PPC_ALLOC_HTAB 162 
#define  KVM_CAP_PPC_BOOKE_SREGS 161 
#define  KVM_CAP_PPC_BOOKE_WATCHDOG 160 
#define  KVM_CAP_PPC_ENABLE_HCALL 159 
#define  KVM_CAP_PPC_EPR 158 
#define  KVM_CAP_PPC_FIXUP_HCALL 157 
#define  KVM_CAP_PPC_FWNMI 156 
#define  KVM_CAP_PPC_GET_CPU_CHAR 155 
#define  KVM_CAP_PPC_GET_PVINFO 154 
#define  KVM_CAP_PPC_GET_SMMU_INFO 153 
#define  KVM_CAP_PPC_HIOR 152 
#define  KVM_CAP_PPC_HTAB_FD 151 
#define  KVM_CAP_PPC_HTM 150 
#define  KVM_CAP_PPC_HWRNG 149 
#define  KVM_CAP_PPC_IRQ_LEVEL 148 
#define  KVM_CAP_PPC_IRQ_XIVE 147 
#define  KVM_CAP_PPC_MMU_HASH_V3 146 
#define  KVM_CAP_PPC_MMU_RADIX 145 
#define  KVM_CAP_PPC_NESTED_HV 144 
#define  KVM_CAP_PPC_OSI 143 
#define  KVM_CAP_PPC_PAIRED_SINGLES 142 
#define  KVM_CAP_PPC_PAPR 141 
#define  KVM_CAP_PPC_RMA 140 
#define  KVM_CAP_PPC_RTAS 139 
#define  KVM_CAP_PPC_SEGSTATE 138 
#define  KVM_CAP_PPC_SMT 137 
#define  KVM_CAP_PPC_SMT_POSSIBLE 136 
#define  KVM_CAP_PPC_UNSET_IRQ 135 
#define  KVM_CAP_SPAPR_MULTITCE 134 
#define  KVM_CAP_SPAPR_RESIZE_HPT 133 
#define  KVM_CAP_SPAPR_TCE 132 
#define  KVM_CAP_SPAPR_TCE_64 131 
#define  KVM_CAP_SPAPR_TCE_VFIO 130 
#define  KVM_CAP_SW_TLB 129 
#define  KVM_CAP_SYNC_MMU 128 
 int KVM_MAX_VCPUS ; 
 int KVM_MAX_VCPU_ID ; 
 int PPC_FEATURE2_HTM ; 
 int /*<<< orphan*/  cpu_has_feature (int /*<<< orphan*/ ) ; 
 TYPE_3__* cur_cpu_spec ; 
 int is_kvmppc_hv_enabled (struct kvm*) ; 
 TYPE_2__* kvmppc_hv_ops ; 
 int kvmppc_hwrng_present () ; 
 int /*<<< orphan*/  kvmppc_xive_native_supported () ; 
 int num_online_cpus () ; 
 int num_present_cpus () ; 
 int /*<<< orphan*/  radix_enabled () ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *) ; 
 int threads_per_subcore ; 
 int /*<<< orphan*/  xive_enabled () ; 

int kvm_vm_ioctl_check_extension(struct kvm *kvm, long ext)
{
	int r;
	/* Assume we're using HV mode when the HV module is loaded */
	int hv_enabled = kvmppc_hv_ops ? 1 : 0;

	if (kvm) {
		/*
		 * Hooray - we know which VM type we're running on. Depend on
		 * that rather than the guess above.
		 */
		hv_enabled = is_kvmppc_hv_enabled(kvm);
	}

	switch (ext) {
#ifdef CONFIG_BOOKE
	case KVM_CAP_PPC_BOOKE_SREGS:
	case KVM_CAP_PPC_BOOKE_WATCHDOG:
	case KVM_CAP_PPC_EPR:
#else
	case KVM_CAP_PPC_SEGSTATE:
	case KVM_CAP_PPC_HIOR:
	case KVM_CAP_PPC_PAPR:
#endif
	case KVM_CAP_PPC_UNSET_IRQ:
	case KVM_CAP_PPC_IRQ_LEVEL:
	case KVM_CAP_ENABLE_CAP:
	case KVM_CAP_ONE_REG:
	case KVM_CAP_IOEVENTFD:
	case KVM_CAP_DEVICE_CTRL:
	case KVM_CAP_IMMEDIATE_EXIT:
		r = 1;
		break;
	case KVM_CAP_PPC_PAIRED_SINGLES:
	case KVM_CAP_PPC_OSI:
	case KVM_CAP_PPC_GET_PVINFO:
#if defined(CONFIG_KVM_E500V2) || defined(CONFIG_KVM_E500MC)
	case KVM_CAP_SW_TLB:
#endif
		/* We support this only for PR */
		r = !hv_enabled;
		break;
#ifdef CONFIG_KVM_MPIC
	case KVM_CAP_IRQ_MPIC:
		r = 1;
		break;
#endif

#ifdef CONFIG_PPC_BOOK3S_64
	case KVM_CAP_SPAPR_TCE:
	case KVM_CAP_SPAPR_TCE_64:
		r = 1;
		break;
	case KVM_CAP_SPAPR_TCE_VFIO:
		r = !!cpu_has_feature(CPU_FTR_HVMODE);
		break;
	case KVM_CAP_PPC_RTAS:
	case KVM_CAP_PPC_FIXUP_HCALL:
	case KVM_CAP_PPC_ENABLE_HCALL:
#ifdef CONFIG_KVM_XICS
	case KVM_CAP_IRQ_XICS:
#endif
	case KVM_CAP_PPC_GET_CPU_CHAR:
		r = 1;
		break;
#ifdef CONFIG_KVM_XIVE
	case KVM_CAP_PPC_IRQ_XIVE:
		/*
		 * We need XIVE to be enabled on the platform (implies
		 * a POWER9 processor) and the PowerNV platform, as
		 * nested is not yet supported.
		 */
		r = xive_enabled() && !!cpu_has_feature(CPU_FTR_HVMODE) &&
			kvmppc_xive_native_supported();
		break;
#endif

	case KVM_CAP_PPC_ALLOC_HTAB:
		r = hv_enabled;
		break;
#endif /* CONFIG_PPC_BOOK3S_64 */
#ifdef CONFIG_KVM_BOOK3S_HV_POSSIBLE
	case KVM_CAP_PPC_SMT:
		r = 0;
		if (kvm) {
			if (kvm->arch.emul_smt_mode > 1)
				r = kvm->arch.emul_smt_mode;
			else
				r = kvm->arch.smt_mode;
		} else if (hv_enabled) {
			if (cpu_has_feature(CPU_FTR_ARCH_300))
				r = 1;
			else
				r = threads_per_subcore;
		}
		break;
	case KVM_CAP_PPC_SMT_POSSIBLE:
		r = 1;
		if (hv_enabled) {
			if (!cpu_has_feature(CPU_FTR_ARCH_300))
				r = ((threads_per_subcore << 1) - 1);
			else
				/* P9 can emulate dbells, so allow any mode */
				r = 8 | 4 | 2 | 1;
		}
		break;
	case KVM_CAP_PPC_RMA:
		r = 0;
		break;
	case KVM_CAP_PPC_HWRNG:
		r = kvmppc_hwrng_present();
		break;
	case KVM_CAP_PPC_MMU_RADIX:
		r = !!(hv_enabled && radix_enabled());
		break;
	case KVM_CAP_PPC_MMU_HASH_V3:
		r = !!(hv_enabled && cpu_has_feature(CPU_FTR_ARCH_300) &&
		       cpu_has_feature(CPU_FTR_HVMODE));
		break;
	case KVM_CAP_PPC_NESTED_HV:
		r = !!(hv_enabled && kvmppc_hv_ops->enable_nested &&
		       !kvmppc_hv_ops->enable_nested(NULL));
		break;
#endif
	case KVM_CAP_SYNC_MMU:
#ifdef CONFIG_KVM_BOOK3S_HV_POSSIBLE
		r = hv_enabled;
#elif defined(KVM_ARCH_WANT_MMU_NOTIFIER)
		r = 1;
#else
		r = 0;
#endif
		break;
#ifdef CONFIG_KVM_BOOK3S_HV_POSSIBLE
	case KVM_CAP_PPC_HTAB_FD:
		r = hv_enabled;
		break;
#endif
	case KVM_CAP_NR_VCPUS:
		/*
		 * Recommending a number of CPUs is somewhat arbitrary; we
		 * return the number of present CPUs for -HV (since a host
		 * will have secondary threads "offline"), and for other KVM
		 * implementations just count online CPUs.
		 */
		if (hv_enabled)
			r = num_present_cpus();
		else
			r = num_online_cpus();
		break;
	case KVM_CAP_MAX_VCPUS:
		r = KVM_MAX_VCPUS;
		break;
	case KVM_CAP_MAX_VCPU_ID:
		r = KVM_MAX_VCPU_ID;
		break;
#ifdef CONFIG_PPC_BOOK3S_64
	case KVM_CAP_PPC_GET_SMMU_INFO:
		r = 1;
		break;
	case KVM_CAP_SPAPR_MULTITCE:
		r = 1;
		break;
	case KVM_CAP_SPAPR_RESIZE_HPT:
		r = !!hv_enabled;
		break;
#endif
#ifdef CONFIG_KVM_BOOK3S_HV_POSSIBLE
	case KVM_CAP_PPC_FWNMI:
		r = hv_enabled;
		break;
#endif
#ifdef CONFIG_PPC_TRANSACTIONAL_MEM
	case KVM_CAP_PPC_HTM:
		r = !!(cur_cpu_spec->cpu_user_features2 & PPC_FEATURE2_HTM) ||
		     (hv_enabled && cpu_has_feature(CPU_FTR_P9_TM_HV_ASSIST));
		break;
#endif
	default:
		r = 0;
		break;
	}
	return r;

}