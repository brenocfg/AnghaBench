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
struct kvmppc_vcpu_book3s {int /*<<< orphan*/  mmu_lock; int /*<<< orphan*/  hpte_hash_vpte_64k; int /*<<< orphan*/  hpte_hash_vpte_long; int /*<<< orphan*/  hpte_hash_vpte; int /*<<< orphan*/  hpte_hash_pte_long; int /*<<< orphan*/  hpte_hash_pte; } ;
struct kvm_vcpu {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvmppc_mmu_hpte_init_hash (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 struct kvmppc_vcpu_book3s* to_book3s (struct kvm_vcpu*) ; 

int kvmppc_mmu_hpte_init(struct kvm_vcpu *vcpu)
{
	struct kvmppc_vcpu_book3s *vcpu3s = to_book3s(vcpu);

	/* init hpte lookup hashes */
	kvmppc_mmu_hpte_init_hash(vcpu3s->hpte_hash_pte,
				  ARRAY_SIZE(vcpu3s->hpte_hash_pte));
	kvmppc_mmu_hpte_init_hash(vcpu3s->hpte_hash_pte_long,
				  ARRAY_SIZE(vcpu3s->hpte_hash_pte_long));
	kvmppc_mmu_hpte_init_hash(vcpu3s->hpte_hash_vpte,
				  ARRAY_SIZE(vcpu3s->hpte_hash_vpte));
	kvmppc_mmu_hpte_init_hash(vcpu3s->hpte_hash_vpte_long,
				  ARRAY_SIZE(vcpu3s->hpte_hash_vpte_long));
#ifdef CONFIG_PPC_BOOK3S_64
	kvmppc_mmu_hpte_init_hash(vcpu3s->hpte_hash_vpte_64k,
				  ARRAY_SIZE(vcpu3s->hpte_hash_vpte_64k));
#endif

	spin_lock_init(&vcpu3s->mmu_lock);

	return 0;
}