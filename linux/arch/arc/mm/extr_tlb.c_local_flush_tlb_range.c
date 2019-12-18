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
struct vm_area_struct {int /*<<< orphan*/  vm_mm; } ;

/* Variables and functions */
 scalar_t__ MM_CTXT_NO_ASID ; 
 unsigned long PAGE_MASK ; 
 int PAGE_SIZE ; 
 scalar_t__ asid_mm (int /*<<< orphan*/ ,unsigned int const) ; 
 unsigned long hw_pid (int /*<<< orphan*/ ,unsigned int const) ; 
 int /*<<< orphan*/  local_flush_tlb_mm (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 unsigned int smp_processor_id () ; 
 int /*<<< orphan*/  tlb_entry_erase (unsigned long) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  utlb_invalidate () ; 

void local_flush_tlb_range(struct vm_area_struct *vma, unsigned long start,
			   unsigned long end)
{
	const unsigned int cpu = smp_processor_id();
	unsigned long flags;

	/* If range @start to @end is more than 32 TLB entries deep,
	 * its better to move to a new ASID rather than searching for
	 * individual entries and then shooting them down
	 *
	 * The calc above is rough, doesn't account for unaligned parts,
	 * since this is heuristics based anyways
	 */
	if (unlikely((end - start) >= PAGE_SIZE * 32)) {
		local_flush_tlb_mm(vma->vm_mm);
		return;
	}

	/*
	 * @start moved to page start: this alone suffices for checking
	 * loop end condition below, w/o need for aligning @end to end
	 * e.g. 2000 to 4001 will anyhow loop twice
	 */
	start &= PAGE_MASK;

	local_irq_save(flags);

	if (asid_mm(vma->vm_mm, cpu) != MM_CTXT_NO_ASID) {
		while (start < end) {
			tlb_entry_erase(start | hw_pid(vma->vm_mm, cpu));
			start += PAGE_SIZE;
		}
	}

	utlb_invalidate();

	local_irq_restore(flags);
}