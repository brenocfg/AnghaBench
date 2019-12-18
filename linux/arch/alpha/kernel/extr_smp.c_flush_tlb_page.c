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
struct vm_area_struct {struct mm_struct* vm_mm; } ;
struct mm_struct {scalar_t__* context; int /*<<< orphan*/  mm_users; } ;
struct flush_tlb_page_struct {unsigned long addr; struct mm_struct* mm; struct vm_area_struct* vma; } ;
struct TYPE_2__ {struct mm_struct* active_mm; } ;

/* Variables and functions */
 int NR_CPUS ; 
 int atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cpu_online (int) ; 
 TYPE_1__* current ; 
 int /*<<< orphan*/  flush_tlb_current_page (struct mm_struct*,struct vm_area_struct*,unsigned long) ; 
 int /*<<< orphan*/  ipi_flush_tlb_page ; 
 int /*<<< orphan*/  preempt_disable () ; 
 int /*<<< orphan*/  preempt_enable () ; 
 int /*<<< orphan*/  smp_call_function (int /*<<< orphan*/ ,struct flush_tlb_page_struct*,int) ; 
 int smp_processor_id () ; 

void
flush_tlb_page(struct vm_area_struct *vma, unsigned long addr)
{
	struct flush_tlb_page_struct data;
	struct mm_struct *mm = vma->vm_mm;

	preempt_disable();

	if (mm == current->active_mm) {
		flush_tlb_current_page(mm, vma, addr);
		if (atomic_read(&mm->mm_users) <= 1) {
			int cpu, this_cpu = smp_processor_id();
			for (cpu = 0; cpu < NR_CPUS; cpu++) {
				if (!cpu_online(cpu) || cpu == this_cpu)
					continue;
				if (mm->context[cpu])
					mm->context[cpu] = 0;
			}
			preempt_enable();
			return;
		}
	}

	data.vma = vma;
	data.mm = mm;
	data.addr = addr;

	smp_call_function(ipi_flush_tlb_page, &data, 1);

	preempt_enable();
}