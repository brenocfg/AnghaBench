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
struct thread {int td_pflags; int /*<<< orphan*/  td_pcb; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCB_USER_FPU (int /*<<< orphan*/ ) ; 
 struct thread* PCPU_GET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PCPU_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int TDP_KTHREAD ; 
 int /*<<< orphan*/  fpcurthread ; 
 int /*<<< orphan*/  restore_fpu_curthread (struct thread*) ; 
 int /*<<< orphan*/  start_emulating () ; 

void
fpu_activate_sw(struct thread *td)
{

	if ((td->td_pflags & TDP_KTHREAD) != 0 || !PCB_USER_FPU(td->td_pcb)) {
		PCPU_SET(fpcurthread, NULL);
		start_emulating();
	} else if (PCPU_GET(fpcurthread) != td) {
		restore_fpu_curthread(td);
	}
}