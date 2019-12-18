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
struct kvm_rmap_head {int dummy; } ;
struct kvm_mmu_page {int spt; } ;
struct kvm {int dummy; } ;
typedef  int /*<<< orphan*/  gfn_t ;

/* Variables and functions */
 int /*<<< orphan*/  __pa (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  __pte_list_remove (int /*<<< orphan*/ *,struct kvm_rmap_head*) ; 
 struct kvm_rmap_head* gfn_to_rmap (struct kvm*,int /*<<< orphan*/ ,struct kvm_mmu_page*) ; 
 int /*<<< orphan*/  kvm_mmu_page_get_gfn (struct kvm_mmu_page*,int /*<<< orphan*/ *) ; 
 struct kvm_mmu_page* page_header (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rmap_remove(struct kvm *kvm, u64 *spte)
{
	struct kvm_mmu_page *sp;
	gfn_t gfn;
	struct kvm_rmap_head *rmap_head;

	sp = page_header(__pa(spte));
	gfn = kvm_mmu_page_get_gfn(sp, spte - sp->spt);
	rmap_head = gfn_to_rmap(kvm, gfn, sp);
	__pte_list_remove(spte, rmap_head);
}