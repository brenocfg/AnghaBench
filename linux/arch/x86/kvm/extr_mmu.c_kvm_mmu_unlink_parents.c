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
typedef  int /*<<< orphan*/  u64 ;
struct rmap_iterator {int dummy; } ;
struct kvm_mmu_page {int /*<<< orphan*/  parent_ptes; } ;
struct kvm {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  drop_parent_pte (struct kvm_mmu_page*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * rmap_get_first (int /*<<< orphan*/ *,struct rmap_iterator*) ; 

__attribute__((used)) static void kvm_mmu_unlink_parents(struct kvm *kvm, struct kvm_mmu_page *sp)
{
	u64 *sptep;
	struct rmap_iterator iter;

	while ((sptep = rmap_get_first(&sp->parent_ptes, &iter)))
		drop_parent_pte(sp, sptep);
}