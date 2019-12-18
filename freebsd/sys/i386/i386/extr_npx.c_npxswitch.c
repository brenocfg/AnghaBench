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
struct thread {int td_pflags; } ;
struct pcb {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCB_USER_FPU (struct pcb*) ; 
 struct thread* PCPU_GET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PCPU_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int TDP_KTHREAD ; 
 int /*<<< orphan*/  fpcurthread ; 
 scalar_t__ lazy_fpu_switch ; 
 int /*<<< orphan*/  restore_npx_curthread (struct thread*,struct pcb*) ; 
 int /*<<< orphan*/  start_emulating () ; 

void
npxswitch(struct thread *td, struct pcb *pcb)
{

	if (lazy_fpu_switch || (td->td_pflags & TDP_KTHREAD) != 0 ||
	    !PCB_USER_FPU(pcb)) {
		start_emulating();
		PCPU_SET(fpcurthread, NULL);
	} else if (PCPU_GET(fpcurthread) != td) {
		restore_npx_curthread(td, pcb);
	}
}