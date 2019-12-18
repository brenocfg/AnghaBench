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
struct thread {int /*<<< orphan*/  td_pcb; } ;

/* Variables and functions */
 int /*<<< orphan*/  CRITICAL_ASSERT (struct thread*) ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  PCB_FPUINITDONE ; 
 struct thread* PCPU_GET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PCPU_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clear_pcb_flags (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct thread* curthread ; 
 int /*<<< orphan*/  fpcurthread ; 
 int /*<<< orphan*/  start_emulating () ; 

void
fpudrop(void)
{
	struct thread *td;

	td = PCPU_GET(fpcurthread);
	KASSERT(td == curthread, ("fpudrop: fpcurthread != curthread"));
	CRITICAL_ASSERT(td);
	PCPU_SET(fpcurthread, NULL);
	clear_pcb_flags(td->td_pcb, PCB_FPUINITDONE);
	start_emulating();
}