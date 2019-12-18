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

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_LOCKDEP ; 
 scalar_t__ IS_ENABLED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  diagnose_trace_depth ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 unsigned int* this_cpu_ptr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_s390_diagnose (int) ; 

void trace_s390_diagnose_norecursion(int diag_nr)
{
	unsigned long flags;
	unsigned int *depth;

	/* Avoid lockdep recursion. */
	if (IS_ENABLED(CONFIG_LOCKDEP))
		return;
	local_irq_save(flags);
	depth = this_cpu_ptr(&diagnose_trace_depth);
	if (*depth == 0) {
		(*depth)++;
		trace_s390_diagnose(diag_nr);
		(*depth)--;
	}
	local_irq_restore(flags);
}