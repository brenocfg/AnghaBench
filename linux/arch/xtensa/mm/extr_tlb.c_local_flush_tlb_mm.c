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
struct TYPE_3__ {int cpu; void** asid; } ;
struct mm_struct {TYPE_1__ context; } ;
struct TYPE_4__ {struct mm_struct* active_mm; } ;

/* Variables and functions */
 void* NO_CONTEXT ; 
 int /*<<< orphan*/  activate_context (struct mm_struct*,int) ; 
 TYPE_2__* current ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 int smp_processor_id () ; 

void local_flush_tlb_mm(struct mm_struct *mm)
{
	int cpu = smp_processor_id();

	if (mm == current->active_mm) {
		unsigned long flags;
		local_irq_save(flags);
		mm->context.asid[cpu] = NO_CONTEXT;
		activate_context(mm, cpu);
		local_irq_restore(flags);
	} else {
		mm->context.asid[cpu] = NO_CONTEXT;
		mm->context.cpu = -1;
	}
}