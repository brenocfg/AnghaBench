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
struct intel_shared_regs {int core_id; scalar_t__ refcnt; } ;
struct cpu_hw_events {struct intel_shared_regs* shared_regs; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_excl_cntrs (struct cpu_hw_events*) ; 
 int /*<<< orphan*/  kfree (struct intel_shared_regs*) ; 

void intel_cpuc_finish(struct cpu_hw_events *cpuc)
{
	struct intel_shared_regs *pc;

	pc = cpuc->shared_regs;
	if (pc) {
		if (pc->core_id == -1 || --pc->refcnt == 0)
			kfree(pc);
		cpuc->shared_regs = NULL;
	}

	free_excl_cntrs(cpuc);
}