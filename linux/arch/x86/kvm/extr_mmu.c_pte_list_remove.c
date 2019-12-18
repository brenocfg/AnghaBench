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

/* Variables and functions */
 int /*<<< orphan*/  __pte_list_remove (int /*<<< orphan*/ *,struct kvm_rmap_head*) ; 
 int /*<<< orphan*/  mmu_spte_clear_track_bits (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void pte_list_remove(struct kvm_rmap_head *rmap_head, u64 *sptep)
{
	mmu_spte_clear_track_bits(sptep);
	__pte_list_remove(sptep, rmap_head);
}