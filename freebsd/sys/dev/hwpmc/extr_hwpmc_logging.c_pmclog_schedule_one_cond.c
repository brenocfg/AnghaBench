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
struct pmclog_buffer {scalar_t__ plb_ptr; scalar_t__ plb_base; } ;
struct pmc_owner {struct pmclog_buffer** po_curbuf; } ;

/* Variables and functions */
 int /*<<< orphan*/  PMC_CALL_HOOK_UNLOCKED (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ PMC_CPU_HAS_SAMPLES (int) ; 
 int /*<<< orphan*/  PMC_FN_DO_SAMPLES ; 
 int curcpu ; 
 int /*<<< orphan*/  curthread ; 
 int /*<<< orphan*/  pmclog_schedule_io (struct pmc_owner*,int) ; 
 int /*<<< orphan*/  spinlock_enter () ; 
 int /*<<< orphan*/  spinlock_exit () ; 

__attribute__((used)) static void
pmclog_schedule_one_cond(struct pmc_owner *po)
{
	struct pmclog_buffer *plb;
	int cpu;

	spinlock_enter();
	cpu = curcpu;
	/* tell hardclock not to run again */
	if (PMC_CPU_HAS_SAMPLES(cpu))
		PMC_CALL_HOOK_UNLOCKED(curthread, PMC_FN_DO_SAMPLES, NULL);

	plb = po->po_curbuf[cpu];
	if (plb && plb->plb_ptr != plb->plb_base)
		pmclog_schedule_io(po, 1);
	spinlock_exit();
}