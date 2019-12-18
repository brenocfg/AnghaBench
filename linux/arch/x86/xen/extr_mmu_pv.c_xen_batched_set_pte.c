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
struct mmu_update {int ptr; int /*<<< orphan*/  val; } ;
typedef  int /*<<< orphan*/  pte_t ;
struct TYPE_2__ {int maddr; } ;

/* Variables and functions */
 int MMU_NORMAL_PT_UPDATE ; 
 scalar_t__ PARAVIRT_LAZY_MMU ; 
 scalar_t__ paravirt_get_lazy_mode () ; 
 int /*<<< orphan*/  pte_val_ma (int /*<<< orphan*/ ) ; 
 TYPE_1__ virt_to_machine (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xen_extend_mmu_update (struct mmu_update*) ; 
 int /*<<< orphan*/  xen_mc_batch () ; 
 int /*<<< orphan*/  xen_mc_issue (scalar_t__) ; 

__attribute__((used)) static bool xen_batched_set_pte(pte_t *ptep, pte_t pteval)
{
	struct mmu_update u;

	if (paravirt_get_lazy_mode() != PARAVIRT_LAZY_MMU)
		return false;

	xen_mc_batch();

	u.ptr = virt_to_machine(ptep).maddr | MMU_NORMAL_PT_UPDATE;
	u.val = pte_val_ma(pteval);
	xen_extend_mmu_update(&u);

	xen_mc_issue(PARAVIRT_LAZY_MMU);

	return true;
}