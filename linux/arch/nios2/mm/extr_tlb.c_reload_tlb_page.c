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
struct vm_area_struct {TYPE_1__* vm_mm; } ;
typedef  int /*<<< orphan*/  pte_t ;
struct TYPE_2__ {int /*<<< orphan*/  context; } ;

/* Variables and functions */
 unsigned long get_pid_from_context (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  reload_tlb_one_pid (unsigned long,unsigned long,int /*<<< orphan*/ ) ; 

void reload_tlb_page(struct vm_area_struct *vma, unsigned long addr, pte_t pte)
{
	unsigned long mmu_pid = get_pid_from_context(&vma->vm_mm->context);

	reload_tlb_one_pid(addr, mmu_pid, pte);
}