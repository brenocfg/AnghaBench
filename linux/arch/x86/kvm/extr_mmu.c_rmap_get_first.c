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
struct rmap_iterator {size_t pos; struct pte_list_desc* desc; } ;
struct pte_list_desc {int /*<<< orphan*/ ** sptes; } ;
struct kvm_rmap_head {int val; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  is_shadow_present_pte (int /*<<< orphan*/ ) ; 

__attribute__((used)) static u64 *rmap_get_first(struct kvm_rmap_head *rmap_head,
			   struct rmap_iterator *iter)
{
	u64 *sptep;

	if (!rmap_head->val)
		return NULL;

	if (!(rmap_head->val & 1)) {
		iter->desc = NULL;
		sptep = (u64 *)rmap_head->val;
		goto out;
	}

	iter->desc = (struct pte_list_desc *)(rmap_head->val & ~1ul);
	iter->pos = 0;
	sptep = iter->desc->sptes[iter->pos];
out:
	BUG_ON(!is_shadow_present_pte(*sptep));
	return sptep;
}