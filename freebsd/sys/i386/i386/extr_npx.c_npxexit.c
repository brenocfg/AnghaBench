#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u_int ;
struct thread {TYPE_1__* td_proc; } ;
struct TYPE_4__ {int /*<<< orphan*/  pcb_save; } ;
struct TYPE_3__ {int /*<<< orphan*/  p_comm; int /*<<< orphan*/  p_pid; } ;

/* Variables and functions */
 int GET_FPU_CW (struct thread*) ; 
 int GET_FPU_SW (struct thread*) ; 
 int /*<<< orphan*/  LOG_ERR ; 
 scalar_t__ PCPU_GET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PCPU_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  critical_enter () ; 
 int /*<<< orphan*/  critical_exit () ; 
 TYPE_2__* curpcb ; 
 scalar_t__ curthread ; 
 int /*<<< orphan*/  fpcurthread ; 
 int /*<<< orphan*/  fpusave (int /*<<< orphan*/ ) ; 
 scalar_t__ hw_float ; 
 int /*<<< orphan*/  log (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  start_emulating () ; 
 int /*<<< orphan*/  stop_emulating () ; 

void
npxexit(struct thread *td)
{

	critical_enter();
	if (curthread == PCPU_GET(fpcurthread)) {
		stop_emulating();
		fpusave(curpcb->pcb_save);
		start_emulating();
		PCPU_SET(fpcurthread, NULL);
	}
	critical_exit();
#ifdef NPX_DEBUG
	if (hw_float) {
		u_int	masked_exceptions;

		masked_exceptions = GET_FPU_CW(td) & GET_FPU_SW(td) & 0x7f;
		/*
		 * Log exceptions that would have trapped with the old
		 * control word (overflow, divide by 0, and invalid operand).
		 */
		if (masked_exceptions & 0x0d)
			log(LOG_ERR,
	"pid %d (%s) exited with masked floating point exceptions 0x%02x\n",
			    td->td_proc->p_pid, td->td_proc->p_comm,
			    masked_exceptions);
	}
#endif
}