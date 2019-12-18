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
struct vm_area_struct {int vm_flags; struct mm_struct* vm_mm; } ;
struct page {int dummy; } ;
struct mm_struct {scalar_t__* context; int /*<<< orphan*/  mm_users; } ;
struct TYPE_2__ {struct mm_struct* active_mm; } ;

/* Variables and functions */
 int NR_CPUS ; 
 int VM_EXEC ; 
 int /*<<< orphan*/  __load_new_mm_context (struct mm_struct*) ; 
 int atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cpu_online (int) ; 
 TYPE_1__* current ; 
 int /*<<< orphan*/  ipi_flush_icache_page ; 
 int /*<<< orphan*/  preempt_disable () ; 
 int /*<<< orphan*/  preempt_enable () ; 
 int /*<<< orphan*/  smp_call_function (int /*<<< orphan*/ ,struct mm_struct*,int) ; 
 int smp_processor_id () ; 

void
flush_icache_user_range(struct vm_area_struct *vma, struct page *page,
			unsigned long addr, int len)
{
	struct mm_struct *mm = vma->vm_mm;

	if ((vma->vm_flags & VM_EXEC) == 0)
		return;

	preempt_disable();

	if (mm == current->active_mm) {
		__load_new_mm_context(mm);
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

	smp_call_function(ipi_flush_icache_page, mm, 1);

	preempt_enable();
}