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
struct vm_area_struct {int /*<<< orphan*/  vm_mm; } ;
struct mmu_update {int ptr; int /*<<< orphan*/  val; } ;
typedef  int /*<<< orphan*/  pte_t ;
struct TYPE_2__ {int maddr; } ;

/* Variables and functions */
 int MMU_PT_UPDATE_PRESERVE_AD ; 
 int /*<<< orphan*/  PARAVIRT_LAZY_MMU ; 
 int /*<<< orphan*/  pte_val_ma (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_xen_mmu_ptep_modify_prot_commit (int /*<<< orphan*/ ,unsigned long,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_1__ virt_to_machine (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xen_extend_mmu_update (struct mmu_update*) ; 
 int /*<<< orphan*/  xen_mc_batch () ; 
 int /*<<< orphan*/  xen_mc_issue (int /*<<< orphan*/ ) ; 

void xen_ptep_modify_prot_commit(struct vm_area_struct *vma, unsigned long addr,
				 pte_t *ptep, pte_t pte)
{
	struct mmu_update u;

	trace_xen_mmu_ptep_modify_prot_commit(vma->vm_mm, addr, ptep, pte);
	xen_mc_batch();

	u.ptr = virt_to_machine(ptep).maddr | MMU_PT_UPDATE_PRESERVE_AD;
	u.val = pte_val_ma(pte);
	xen_extend_mmu_update(&u);

	xen_mc_issue(PARAVIRT_LAZY_MMU);
}