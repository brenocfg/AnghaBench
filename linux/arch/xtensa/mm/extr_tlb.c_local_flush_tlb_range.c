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
struct TYPE_2__ {scalar_t__* asid; } ;
struct mm_struct {TYPE_1__ context; } ;

/* Variables and functions */
 int ASID_INSERT (scalar_t__) ; 
 scalar_t__ NO_CONTEXT ; 
 unsigned long PAGE_MASK ; 
 int PAGE_SHIFT ; 
 int PAGE_SIZE ; 
 int VM_EXEC ; 
 int _TLB_ENTRIES ; 
 int get_rasid_register () ; 
 int /*<<< orphan*/  invalidate_dtlb_mapping (unsigned long) ; 
 int /*<<< orphan*/  invalidate_itlb_mapping (unsigned long) ; 
 int /*<<< orphan*/  local_flush_tlb_mm (struct mm_struct*) ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 int /*<<< orphan*/  pr_debug (char*,unsigned long,unsigned long,unsigned long) ; 
 int /*<<< orphan*/  set_rasid_register (int) ; 
 int smp_processor_id () ; 

void local_flush_tlb_range(struct vm_area_struct *vma,
		unsigned long start, unsigned long end)
{
	int cpu = smp_processor_id();
	struct mm_struct *mm = vma->vm_mm;
	unsigned long flags;

	if (mm->context.asid[cpu] == NO_CONTEXT)
		return;

	pr_debug("[tlbrange<%02lx,%08lx,%08lx>]\n",
		 (unsigned long)mm->context.asid[cpu], start, end);
	local_irq_save(flags);

	if (end-start + (PAGE_SIZE-1) <= _TLB_ENTRIES << PAGE_SHIFT) {
		int oldpid = get_rasid_register();

		set_rasid_register(ASID_INSERT(mm->context.asid[cpu]));
		start &= PAGE_MASK;
		if (vma->vm_flags & VM_EXEC)
			while(start < end) {
				invalidate_itlb_mapping(start);
				invalidate_dtlb_mapping(start);
				start += PAGE_SIZE;
			}
		else
			while(start < end) {
				invalidate_dtlb_mapping(start);
				start += PAGE_SIZE;
			}

		set_rasid_register(oldpid);
	} else {
		local_flush_tlb_mm(mm);
	}
	local_irq_restore(flags);
}