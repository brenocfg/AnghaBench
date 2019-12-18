#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct kvmppc_vcpu_book3s {scalar_t__ hpte_cache_count; } ;
struct kvm_vcpu {int dummy; } ;
struct hpte_cache {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ HPTEG_CACHE_NUM ; 
 int /*<<< orphan*/  hpte_cache ; 
 struct hpte_cache* kmem_cache_zalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvmppc_mmu_pte_flush_all (struct kvm_vcpu*) ; 
 struct kvmppc_vcpu_book3s* to_book3s (struct kvm_vcpu*) ; 

struct hpte_cache *kvmppc_mmu_hpte_cache_next(struct kvm_vcpu *vcpu)
{
	struct kvmppc_vcpu_book3s *vcpu3s = to_book3s(vcpu);
	struct hpte_cache *pte;

	if (vcpu3s->hpte_cache_count == HPTEG_CACHE_NUM)
		kvmppc_mmu_pte_flush_all(vcpu);

	pte = kmem_cache_zalloc(hpte_cache, GFP_KERNEL);

	return pte;
}