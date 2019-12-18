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
struct task_struct {int dummy; } ;
struct mm_struct {int /*<<< orphan*/  pgd; } ;

/* Variables and functions */
 int /*<<< orphan*/ * current_pgd ; 
 int /*<<< orphan*/  local_flush_tlb_mm (struct mm_struct*) ; 
 size_t smp_processor_id () ; 

void switch_mm(struct mm_struct *prev, struct mm_struct *next,
	       struct task_struct *next_tsk)
{
	/* remember the pgd for the fault handlers
	 * this is similar to the pgd register in some other CPU's.
	 * we need our own copy of it because current and active_mm
	 * might be invalid at points where we still need to derefer
	 * the pgd.
	 */
	current_pgd[smp_processor_id()] = next->pgd;

	/* We don't have context support implemented, so flush all
	 * entries belonging to previous map
	 */

	if (prev != next)
		local_flush_tlb_mm(prev);

}