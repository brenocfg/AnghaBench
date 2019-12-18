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
struct TYPE_3__ {int /*<<< orphan*/  en_mxcsr; } ;
struct TYPE_4__ {TYPE_1__ sv_env; } ;
union savefpu {TYPE_2__ sv_xmm; } ;
struct thread {struct pcb* td_pcb; } ;
struct pcb {int pcb_flags; } ;

/* Variables and functions */
 int ENXIO ; 
 int PCB_NPXINITDONE ; 
 int PCB_NPXUSERINITDONE ; 
 scalar_t__ PCB_USER_FPU (struct pcb*) ; 
 struct thread* PCPU_GET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bcopy (union savefpu*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ cpu_fxsr ; 
 int /*<<< orphan*/  cpu_mxcsr_mask ; 
 int /*<<< orphan*/  critical_enter () ; 
 int /*<<< orphan*/  critical_exit () ; 
 int /*<<< orphan*/  fnclex () ; 
 int /*<<< orphan*/  fpcurthread ; 
 int /*<<< orphan*/  fpurstor (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_pcb_user_save_td (struct thread*) ; 
 int /*<<< orphan*/  hw_float ; 
 int npxsetxstate (struct thread*,char*,size_t) ; 
 int /*<<< orphan*/  npxuserinited (struct thread*) ; 

int
npxsetregs(struct thread *td, union savefpu *addr, char *xfpustate,
	size_t xfpustate_size)
{
	struct pcb *pcb;
	int error;

	if (!hw_float)
		return (ENXIO);

	if (cpu_fxsr)
		addr->sv_xmm.sv_env.en_mxcsr &= cpu_mxcsr_mask;
	pcb = td->td_pcb;
	error = 0;
	critical_enter();
	if (td == PCPU_GET(fpcurthread) && PCB_USER_FPU(pcb)) {
		error = npxsetxstate(td, xfpustate, xfpustate_size);
		if (error == 0) {
			if (!cpu_fxsr)
				fnclex();	/* As in npxdrop(). */
			bcopy(addr, get_pcb_user_save_td(td), sizeof(*addr));
			fpurstor(get_pcb_user_save_td(td));
			pcb->pcb_flags |= PCB_NPXUSERINITDONE | PCB_NPXINITDONE;
		}
	} else {
		error = npxsetxstate(td, xfpustate, xfpustate_size);
		if (error == 0) {
			bcopy(addr, get_pcb_user_save_td(td), sizeof(*addr));
			npxuserinited(td);
		}
	}
	critical_exit();
	return (error);
}