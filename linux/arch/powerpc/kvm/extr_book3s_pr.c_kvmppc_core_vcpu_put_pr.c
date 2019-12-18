#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct kvmppc_book3s_shadow_vcpu {int /*<<< orphan*/  slb_max; int /*<<< orphan*/  slb; scalar_t__ in_use; } ;
struct kvm_vcpu {int cpu; } ;
struct TYPE_2__ {int /*<<< orphan*/  slb_shadow_max; int /*<<< orphan*/  slb_shadow; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPU_FTR_ARCH_207S ; 
 int /*<<< orphan*/  CPU_FTR_HVMODE ; 
 int /*<<< orphan*/  FSCR_TAR_LG ; 
 int LPCR_AIL_3 ; 
 int MSR_FP ; 
 int MSR_VEC ; 
 int MSR_VSX ; 
 int /*<<< orphan*/  SPRN_LPCR ; 
 scalar_t__ cpu_has_feature (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvmppc_copy_from_svcpu (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  kvmppc_giveup_ext (struct kvm_vcpu*,int) ; 
 int /*<<< orphan*/  kvmppc_giveup_fac (struct kvm_vcpu*,int /*<<< orphan*/ ) ; 
 scalar_t__ kvmppc_is_split_real (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  kvmppc_save_tm_pr (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  kvmppc_unfixup_split_real (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int mfspr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtspr (int /*<<< orphan*/ ,int) ; 
 struct kvmppc_book3s_shadow_vcpu* svcpu_get (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  svcpu_put (struct kvmppc_book3s_shadow_vcpu*) ; 
 TYPE_1__* to_book3s (struct kvm_vcpu*) ; 

__attribute__((used)) static void kvmppc_core_vcpu_put_pr(struct kvm_vcpu *vcpu)
{
#ifdef CONFIG_PPC_BOOK3S_64
	struct kvmppc_book3s_shadow_vcpu *svcpu = svcpu_get(vcpu);
	if (svcpu->in_use) {
		kvmppc_copy_from_svcpu(vcpu);
	}
	memcpy(to_book3s(vcpu)->slb_shadow, svcpu->slb, sizeof(svcpu->slb));
	to_book3s(vcpu)->slb_shadow_max = svcpu->slb_max;
	svcpu_put(svcpu);
#endif

	if (kvmppc_is_split_real(vcpu))
		kvmppc_unfixup_split_real(vcpu);

	kvmppc_giveup_ext(vcpu, MSR_FP | MSR_VEC | MSR_VSX);
	kvmppc_giveup_fac(vcpu, FSCR_TAR_LG);
	kvmppc_save_tm_pr(vcpu);

	/* Enable AIL if supported */
	if (cpu_has_feature(CPU_FTR_HVMODE) &&
	    cpu_has_feature(CPU_FTR_ARCH_207S))
		mtspr(SPRN_LPCR, mfspr(SPRN_LPCR) | LPCR_AIL_3);

	vcpu->cpu = -1;
}