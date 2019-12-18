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
struct mmu_page_path {unsigned int* idx; struct kvm_mmu_page** parent; } ;
struct kvm_mmu_page {int /*<<< orphan*/  unsync_children; } ;

/* Variables and functions */
 unsigned int INVALID_INDEX ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  clear_unsync_child_bit (struct kvm_mmu_page*,unsigned int) ; 

__attribute__((used)) static void mmu_pages_clear_parents(struct mmu_page_path *parents)
{
	struct kvm_mmu_page *sp;
	unsigned int level = 0;

	do {
		unsigned int idx = parents->idx[level];
		sp = parents->parent[level];
		if (!sp)
			return;

		WARN_ON(idx == INVALID_INDEX);
		clear_unsync_child_bit(sp, idx);
		level++;
	} while (!sp->unsync_children);
}