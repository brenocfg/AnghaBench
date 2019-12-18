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
typedef  int /*<<< orphan*/  u64 ;
struct kvm_vcpu {int dummy; } ;
struct TYPE_2__ {scalar_t__ level; } ;
struct kvm_mmu_page {TYPE_1__ role; } ;

/* Variables and functions */
 scalar_t__ PT_PAGE_TABLE_LEVEL ; 
 int /*<<< orphan*/  __direct_pte_prefetch (struct kvm_vcpu*,struct kvm_mmu_page*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  __pa (int /*<<< orphan*/ *) ; 
 struct kvm_mmu_page* page_header (int /*<<< orphan*/ ) ; 
 scalar_t__ sp_ad_disabled (struct kvm_mmu_page*) ; 

__attribute__((used)) static void direct_pte_prefetch(struct kvm_vcpu *vcpu, u64 *sptep)
{
	struct kvm_mmu_page *sp;

	sp = page_header(__pa(sptep));

	/*
	 * Without accessed bits, there's no way to distinguish between
	 * actually accessed translations and prefetched, so disable pte
	 * prefetch if accessed bits aren't available.
	 */
	if (sp_ad_disabled(sp))
		return;

	if (sp->role.level > PT_PAGE_TABLE_LEVEL)
		return;

	__direct_pte_prefetch(vcpu, sp, sptep);
}