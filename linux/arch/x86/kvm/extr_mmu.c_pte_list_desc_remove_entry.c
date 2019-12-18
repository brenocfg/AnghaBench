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
struct pte_list_desc {scalar_t__ more; int /*<<< orphan*/ ** sptes; } ;
struct kvm_rmap_head {unsigned long val; } ;

/* Variables and functions */
 int PTE_LIST_EXT ; 
 int /*<<< orphan*/  mmu_free_pte_list_desc (struct pte_list_desc*) ; 

__attribute__((used)) static void
pte_list_desc_remove_entry(struct kvm_rmap_head *rmap_head,
			   struct pte_list_desc *desc, int i,
			   struct pte_list_desc *prev_desc)
{
	int j;

	for (j = PTE_LIST_EXT - 1; !desc->sptes[j] && j > i; --j)
		;
	desc->sptes[i] = desc->sptes[j];
	desc->sptes[j] = NULL;
	if (j != 0)
		return;
	if (!prev_desc && !desc->more)
		rmap_head->val = (unsigned long)desc->sptes[0];
	else
		if (prev_desc)
			prev_desc->more = desc->more;
		else
			rmap_head->val = (unsigned long)desc->more | 1;
	mmu_free_pte_list_desc(desc);
}