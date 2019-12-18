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
struct kvmppc_vcpu_book3s {int /*<<< orphan*/  mmu_lock; int /*<<< orphan*/  hpte_cache_count; } ;
struct kvm_vcpu {int dummy; } ;
struct hpte_cache {int /*<<< orphan*/  rcu_head; int /*<<< orphan*/  list_vpte_64k; int /*<<< orphan*/  list_vpte_long; int /*<<< orphan*/  list_vpte; int /*<<< orphan*/  list_pte_long; int /*<<< orphan*/  list_pte; } ;

/* Variables and functions */
 int /*<<< orphan*/  call_rcu (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_pte_rcu ; 
 int /*<<< orphan*/  hlist_del_init_rcu (int /*<<< orphan*/ *) ; 
 scalar_t__ hlist_unhashed (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kvmppc_mmu_invalidate_pte (struct kvm_vcpu*,struct hpte_cache*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 struct kvmppc_vcpu_book3s* to_book3s (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  trace_kvm_book3s_mmu_invalidate (struct hpte_cache*) ; 

__attribute__((used)) static void invalidate_pte(struct kvm_vcpu *vcpu, struct hpte_cache *pte)
{
	struct kvmppc_vcpu_book3s *vcpu3s = to_book3s(vcpu);

	trace_kvm_book3s_mmu_invalidate(pte);

	/* Different for 32 and 64 bit */
	kvmppc_mmu_invalidate_pte(vcpu, pte);

	spin_lock(&vcpu3s->mmu_lock);

	/* pte already invalidated in between? */
	if (hlist_unhashed(&pte->list_pte)) {
		spin_unlock(&vcpu3s->mmu_lock);
		return;
	}

	hlist_del_init_rcu(&pte->list_pte);
	hlist_del_init_rcu(&pte->list_pte_long);
	hlist_del_init_rcu(&pte->list_vpte);
	hlist_del_init_rcu(&pte->list_vpte_long);
#ifdef CONFIG_PPC_BOOK3S_64
	hlist_del_init_rcu(&pte->list_vpte_64k);
#endif
	vcpu3s->hpte_cache_count--;

	spin_unlock(&vcpu3s->mmu_lock);

	call_rcu(&pte->rcu_head, free_pte_rcu);
}