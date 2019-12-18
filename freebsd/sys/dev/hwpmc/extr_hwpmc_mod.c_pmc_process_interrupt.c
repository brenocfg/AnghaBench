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
struct trapframe {int dummy; } ;
struct thread {int /*<<< orphan*/  td_pmcpend; TYPE_1__* td_proc; } ;
struct pmc {int pm_flags; } ;
struct TYPE_2__ {int p_flag; } ;

/* Variables and functions */
 int PMC_F_USERCALLCHAIN ; 
 int PMC_UR ; 
 int P_KPROC ; 
 int /*<<< orphan*/  TRAPF_USERMODE (struct trapframe*) ; 
 int /*<<< orphan*/  atomic_add_int (int /*<<< orphan*/ *,int) ; 
 struct thread* curthread ; 
 int pmc_add_sample (int,struct pmc*,struct trapframe*) ; 

int
pmc_process_interrupt(int ring, struct pmc *pm, struct trapframe *tf)
{
	struct thread *td;

	td = curthread;
	if ((pm->pm_flags & PMC_F_USERCALLCHAIN) &&
	    (td->td_proc->p_flag & P_KPROC) == 0 &&
	    !TRAPF_USERMODE(tf)) {
		atomic_add_int(&td->td_pmcpend, 1);
		return (pmc_add_sample(PMC_UR, pm, tf));
	}
	return (pmc_add_sample(ring, pm, tf));
}