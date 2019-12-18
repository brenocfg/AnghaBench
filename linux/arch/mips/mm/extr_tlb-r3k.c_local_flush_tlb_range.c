#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct vm_area_struct {struct mm_struct* vm_mm; } ;
struct mm_struct {int dummy; } ;
struct TYPE_3__ {unsigned long tlbsize; } ;

/* Variables and functions */
 int KSEG0 ; 
 unsigned long PAGE_MASK ; 
 unsigned long PAGE_SHIFT ; 
 int PAGE_SIZE ; 
 unsigned long cpu_asid_mask (TYPE_1__*) ; 
 unsigned long cpu_context (int,struct mm_struct*) ; 
 TYPE_1__ current_cpu_data ; 
 int /*<<< orphan*/  drop_mmu_context (struct mm_struct*) ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 int /*<<< orphan*/  printk (char*,unsigned long,unsigned long,unsigned long) ; 
 unsigned long read_c0_entryhi () ; 
 int read_c0_index () ; 
 int smp_processor_id () ; 
 int /*<<< orphan*/  tlb_probe () ; 
 int /*<<< orphan*/  tlb_write_indexed () ; 
 int /*<<< orphan*/  write_c0_entryhi (int) ; 
 int /*<<< orphan*/  write_c0_entrylo0 (int /*<<< orphan*/ ) ; 

void local_flush_tlb_range(struct vm_area_struct *vma, unsigned long start,
			   unsigned long end)
{
	unsigned long asid_mask = cpu_asid_mask(&current_cpu_data);
	struct mm_struct *mm = vma->vm_mm;
	int cpu = smp_processor_id();

	if (cpu_context(cpu, mm) != 0) {
		unsigned long size, flags;

#ifdef DEBUG_TLB
		printk("[tlbrange<%lu,0x%08lx,0x%08lx>]",
			cpu_context(cpu, mm) & asid_mask, start, end);
#endif
		local_irq_save(flags);
		size = (end - start + (PAGE_SIZE - 1)) >> PAGE_SHIFT;
		if (size <= current_cpu_data.tlbsize) {
			int oldpid = read_c0_entryhi() & asid_mask;
			int newpid = cpu_context(cpu, mm) & asid_mask;

			start &= PAGE_MASK;
			end += PAGE_SIZE - 1;
			end &= PAGE_MASK;
			while (start < end) {
				int idx;

				write_c0_entryhi(start | newpid);
				start += PAGE_SIZE;	/* BARRIER */
				tlb_probe();
				idx = read_c0_index();
				write_c0_entrylo0(0);
				write_c0_entryhi(KSEG0);
				if (idx < 0)		/* BARRIER */
					continue;
				tlb_write_indexed();
			}
			write_c0_entryhi(oldpid);
		} else {
			drop_mmu_context(mm);
		}
		local_irq_restore(flags);
	}
}