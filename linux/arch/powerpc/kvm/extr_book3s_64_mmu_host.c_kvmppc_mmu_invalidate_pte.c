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
struct kvm_vcpu {int dummy; } ;
struct hpte_cache {int /*<<< orphan*/  pagesize; int /*<<< orphan*/  host_vpn; int /*<<< orphan*/  slot; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* hpte_invalidate ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  MMU_SEGSIZE_256M ; 
 TYPE_1__ mmu_hash_ops ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

void kvmppc_mmu_invalidate_pte(struct kvm_vcpu *vcpu, struct hpte_cache *pte)
{
	mmu_hash_ops.hpte_invalidate(pte->slot, pte->host_vpn,
				     pte->pagesize, pte->pagesize,
				     MMU_SEGSIZE_256M, false);
}