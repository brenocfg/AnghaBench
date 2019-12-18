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
struct kvm_mmu_page {int /*<<< orphan*/  unsync_children; int /*<<< orphan*/  unsync_child_bitmap; int /*<<< orphan*/ * spt; } ;

/* Variables and functions */
 int /*<<< orphan*/  __pa (int /*<<< orphan*/ *) ; 
 scalar_t__ __test_and_set_bit (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvm_mmu_mark_parents_unsync (struct kvm_mmu_page*) ; 
 struct kvm_mmu_page* page_header (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mark_unsync(u64 *spte)
{
	struct kvm_mmu_page *sp;
	unsigned int index;

	sp = page_header(__pa(spte));
	index = spte - sp->spt;
	if (__test_and_set_bit(index, sp->unsync_child_bitmap))
		return;
	if (sp->unsync_children++)
		return;
	kvm_mmu_mark_parents_unsync(sp);
}