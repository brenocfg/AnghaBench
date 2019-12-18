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
struct thread {TYPE_1__* td_pcb; } ;
struct TYPE_2__ {int /*<<< orphan*/  pcb_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  CRITICAL_ASSERT (struct thread*) ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  PCB_NPXINITDONE ; 
 struct thread* PCPU_GET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PCPU_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cpu_fxsr ; 
 struct thread* curthread ; 
 int /*<<< orphan*/  fnclex () ; 
 int /*<<< orphan*/  fpcurthread ; 
 int /*<<< orphan*/  start_emulating () ; 

void
npxdrop(void)
{
	struct thread *td;

	/*
	 * Discard pending exceptions in the !cpu_fxsr case so that unmasked
	 * ones don't cause a panic on the next frstor.
	 */
	if (!cpu_fxsr)
		fnclex();

	td = PCPU_GET(fpcurthread);
	KASSERT(td == curthread, ("fpudrop: fpcurthread != curthread"));
	CRITICAL_ASSERT(td);
	PCPU_SET(fpcurthread, NULL);
	td->td_pcb->pcb_flags &= ~PCB_NPXINITDONE;
	start_emulating();
}