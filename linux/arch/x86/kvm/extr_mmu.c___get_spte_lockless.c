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
union split_spte {scalar_t__ spte_low; int /*<<< orphan*/  spte; int /*<<< orphan*/  spte_high; } ;
typedef  int /*<<< orphan*/  u64 ;
struct kvm_mmu_page {int clear_spte_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  __pa (int /*<<< orphan*/ *) ; 
 struct kvm_mmu_page* page_header (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smp_rmb () ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static u64 __get_spte_lockless(u64 *sptep)
{
	struct kvm_mmu_page *sp =  page_header(__pa(sptep));
	union split_spte spte, *orig = (union split_spte *)sptep;
	int count;

retry:
	count = sp->clear_spte_count;
	smp_rmb();

	spte.spte_low = orig->spte_low;
	smp_rmb();

	spte.spte_high = orig->spte_high;
	smp_rmb();

	if (unlikely(spte.spte_low != orig->spte_low ||
	      count != sp->clear_spte_count))
		goto retry;

	return spte.spte;
}