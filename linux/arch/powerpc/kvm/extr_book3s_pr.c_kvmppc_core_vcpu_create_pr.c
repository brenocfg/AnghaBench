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
struct kvmppc_vcpu_book3s {int dummy; } ;
struct TYPE_2__ {int shared_big_endian; int pvr; int slb_nr; int shadow_msr; int /*<<< orphan*/  shadow_vcpu; int /*<<< orphan*/  intr_msr; void* shared; struct kvmppc_vcpu_book3s* book3s; } ;
struct kvm_vcpu {TYPE_1__ arch; } ;
struct kvm {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 struct kvm_vcpu* ERR_PTR (int) ; 
 int GFP_KERNEL ; 
 int /*<<< orphan*/  MMU_FTR_1T_SEGMENT ; 
 int MSR_LE ; 
 int /*<<< orphan*/  MSR_SF ; 
 int MSR_USER64 ; 
 int /*<<< orphan*/  SPRN_PVR ; 
 int __GFP_ZERO ; 
 unsigned long __get_free_page (int) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kmem_cache_free (int /*<<< orphan*/ ,struct kvm_vcpu*) ; 
 struct kvm_vcpu* kmem_cache_zalloc (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  kvm_vcpu_cache ; 
 int kvm_vcpu_init (struct kvm_vcpu*,struct kvm*,unsigned int) ; 
 int /*<<< orphan*/  kvm_vcpu_uninit (struct kvm_vcpu*) ; 
 int kvmppc_mmu_init (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  kvmppc_set_pvr_pr (struct kvm_vcpu*,int) ; 
 int /*<<< orphan*/  kzalloc (int,int) ; 
 int mfspr (int /*<<< orphan*/ ) ; 
 scalar_t__ mmu_has_feature (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vfree (struct kvmppc_vcpu_book3s*) ; 
 struct kvmppc_vcpu_book3s* vzalloc (int) ; 

__attribute__((used)) static struct kvm_vcpu *kvmppc_core_vcpu_create_pr(struct kvm *kvm,
						   unsigned int id)
{
	struct kvmppc_vcpu_book3s *vcpu_book3s;
	struct kvm_vcpu *vcpu;
	int err = -ENOMEM;
	unsigned long p;

	vcpu = kmem_cache_zalloc(kvm_vcpu_cache, GFP_KERNEL);
	if (!vcpu)
		goto out;

	vcpu_book3s = vzalloc(sizeof(struct kvmppc_vcpu_book3s));
	if (!vcpu_book3s)
		goto free_vcpu;
	vcpu->arch.book3s = vcpu_book3s;

#ifdef CONFIG_KVM_BOOK3S_32_HANDLER
	vcpu->arch.shadow_vcpu =
		kzalloc(sizeof(*vcpu->arch.shadow_vcpu), GFP_KERNEL);
	if (!vcpu->arch.shadow_vcpu)
		goto free_vcpu3s;
#endif

	err = kvm_vcpu_init(vcpu, kvm, id);
	if (err)
		goto free_shadow_vcpu;

	err = -ENOMEM;
	p = __get_free_page(GFP_KERNEL|__GFP_ZERO);
	if (!p)
		goto uninit_vcpu;
	vcpu->arch.shared = (void *)p;
#ifdef CONFIG_PPC_BOOK3S_64
	/* Always start the shared struct in native endian mode */
#ifdef __BIG_ENDIAN__
        vcpu->arch.shared_big_endian = true;
#else
        vcpu->arch.shared_big_endian = false;
#endif

	/*
	 * Default to the same as the host if we're on sufficiently
	 * recent machine that we have 1TB segments;
	 * otherwise default to PPC970FX.
	 */
	vcpu->arch.pvr = 0x3C0301;
	if (mmu_has_feature(MMU_FTR_1T_SEGMENT))
		vcpu->arch.pvr = mfspr(SPRN_PVR);
	vcpu->arch.intr_msr = MSR_SF;
#else
	/* default to book3s_32 (750) */
	vcpu->arch.pvr = 0x84202;
#endif
	kvmppc_set_pvr_pr(vcpu, vcpu->arch.pvr);
	vcpu->arch.slb_nr = 64;

	vcpu->arch.shadow_msr = MSR_USER64 & ~MSR_LE;

	err = kvmppc_mmu_init(vcpu);
	if (err < 0)
		goto uninit_vcpu;

	return vcpu;

uninit_vcpu:
	kvm_vcpu_uninit(vcpu);
free_shadow_vcpu:
#ifdef CONFIG_KVM_BOOK3S_32_HANDLER
	kfree(vcpu->arch.shadow_vcpu);
free_vcpu3s:
#endif
	vfree(vcpu_book3s);
free_vcpu:
	kmem_cache_free(kvm_vcpu_cache, vcpu);
out:
	return ERR_PTR(err);
}