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
struct thread {int /*<<< orphan*/  td_pcb; } ;
struct TYPE_2__ {int /*<<< orphan*/  td_pcb; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int /*<<< orphan*/ ,char*) ; 
 int PCB_FPUINITDONE ; 
 int PCB_USERFPUINITDONE ; 
 int /*<<< orphan*/  PCB_USER_FPU (int /*<<< orphan*/ ) ; 
 struct thread* PCPU_GET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clear_pcb_flags (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  critical_enter () ; 
 int /*<<< orphan*/  critical_exit () ; 
 TYPE_1__* curthread ; 
 int /*<<< orphan*/  fpcurthread ; 
 int /*<<< orphan*/  fpudrop () ; 

void
fpstate_drop(struct thread *td)
{

	KASSERT(PCB_USER_FPU(td->td_pcb), ("fpstate_drop: kernel-owned fpu"));
	critical_enter();
	if (PCPU_GET(fpcurthread) == td)
		fpudrop();
	/*
	 * XXX force a full drop of the fpu.  The above only drops it if we
	 * owned it.
	 *
	 * XXX I don't much like fpugetuserregs()'s semantics of doing a full
	 * drop.  Dropping only to the pcb matches fnsave's behaviour.
	 * We only need to drop to !PCB_INITDONE in sendsig().  But
	 * sendsig() is the only caller of fpugetuserregs()... perhaps we just
	 * have too many layers.
	 */
	clear_pcb_flags(curthread->td_pcb,
	    PCB_FPUINITDONE | PCB_USERFPUINITDONE);
	critical_exit();
}