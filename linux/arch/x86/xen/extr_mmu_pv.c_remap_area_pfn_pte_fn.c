#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct remap_data {TYPE_1__* mmu_update; scalar_t__ no_translate; int /*<<< orphan*/ * pfn; scalar_t__ contiguous; int /*<<< orphan*/  prot; } ;
typedef  int /*<<< orphan*/  pte_t ;
struct TYPE_4__ {int /*<<< orphan*/  maddr; } ;
struct TYPE_3__ {int /*<<< orphan*/  val; int /*<<< orphan*/  ptr; } ;

/* Variables and functions */
 int /*<<< orphan*/  MMU_NORMAL_PT_UPDATE ; 
 int /*<<< orphan*/  MMU_PT_UPDATE_NO_TRANSLATE ; 
 int /*<<< orphan*/  mfn_pte (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pte_mkspecial (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pte_val_ma (int /*<<< orphan*/ ) ; 
 TYPE_2__ virt_to_machine (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int remap_area_pfn_pte_fn(pte_t *ptep, unsigned long addr, void *data)
{
	struct remap_data *rmd = data;
	pte_t pte = pte_mkspecial(mfn_pte(*rmd->pfn, rmd->prot));

	/*
	 * If we have a contiguous range, just update the pfn itself,
	 * else update pointer to be "next pfn".
	 */
	if (rmd->contiguous)
		(*rmd->pfn)++;
	else
		rmd->pfn++;

	rmd->mmu_update->ptr = virt_to_machine(ptep).maddr;
	rmd->mmu_update->ptr |= rmd->no_translate ?
		MMU_PT_UPDATE_NO_TRANSLATE :
		MMU_NORMAL_PT_UPDATE;
	rmd->mmu_update->val = pte_val_ma(pte);
	rmd->mmu_update++;

	return 0;
}