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
struct thread {int /*<<< orphan*/  td_pcb; TYPE_1__* td_proc; } ;
struct TYPE_2__ {int p_pid; } ;

/* Variables and functions */
 struct thread* PCPU_GET (int /*<<< orphan*/ ) ; 
 scalar_t__ __predict_false (int) ; 
 int /*<<< orphan*/  critical_enter () ; 
 int /*<<< orphan*/  critical_exit () ; 
 struct thread* curthread ; 
 int /*<<< orphan*/  fpcurthread ; 
 int /*<<< orphan*/  hw_float ; 
 int /*<<< orphan*/  panic (char*) ; 
 int /*<<< orphan*/  printf (char*,struct thread*,int,struct thread*,int) ; 
 int /*<<< orphan*/  restore_npx_curthread (struct thread*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stop_emulating () ; 

int
npxdna(void)
{
	struct thread *td;

	if (!hw_float)
		return (0);
	td = curthread;
	critical_enter();
	if (__predict_false(PCPU_GET(fpcurthread) == td)) {
		/*
		 * Some virtual machines seems to set %cr0.TS at
		 * arbitrary moments.  Silently clear the TS bit
		 * regardless of the eager/lazy FPU context switch
		 * mode.
		 */
		stop_emulating();
	} else {
		if (__predict_false(PCPU_GET(fpcurthread) != NULL)) {
			printf(
		    "npxdna: fpcurthread = %p (%d), curthread = %p (%d)\n",
			    PCPU_GET(fpcurthread),
			    PCPU_GET(fpcurthread)->td_proc->p_pid,
			    td, td->td_proc->p_pid);
			panic("npxdna");
		}
		restore_npx_curthread(td, td->td_pcb);
	}
	critical_exit();
	return (1);
}