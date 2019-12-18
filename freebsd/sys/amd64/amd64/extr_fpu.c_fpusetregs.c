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
struct thread {struct pcb* td_pcb; } ;
struct TYPE_2__ {int /*<<< orphan*/  en_mxcsr; } ;
struct savefpu {TYPE_1__ sv_env; } ;
struct pcb {int dummy; } ;

/* Variables and functions */
 int PCB_FPUINITDONE ; 
 int PCB_USERFPUINITDONE ; 
 scalar_t__ PCB_USER_FPU (struct pcb*) ; 
 struct thread* PCPU_GET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bcopy (struct savefpu*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  cpu_mxcsr_mask ; 
 int /*<<< orphan*/  critical_enter () ; 
 int /*<<< orphan*/  critical_exit () ; 
 int /*<<< orphan*/  fpcurthread ; 
 int /*<<< orphan*/  fpurestore (int /*<<< orphan*/ ) ; 
 int fpusetxstate (struct thread*,char*,size_t) ; 
 int /*<<< orphan*/  fpuuserinited (struct thread*) ; 
 int /*<<< orphan*/  get_pcb_user_save_td (struct thread*) ; 
 int /*<<< orphan*/  set_pcb_flags (struct pcb*,int) ; 

int
fpusetregs(struct thread *td, struct savefpu *addr, char *xfpustate,
    size_t xfpustate_size)
{
	struct pcb *pcb;
	int error;

	addr->sv_env.en_mxcsr &= cpu_mxcsr_mask;
	pcb = td->td_pcb;
	error = 0;
	critical_enter();
	if (td == PCPU_GET(fpcurthread) && PCB_USER_FPU(pcb)) {
		error = fpusetxstate(td, xfpustate, xfpustate_size);
		if (error == 0) {
			bcopy(addr, get_pcb_user_save_td(td), sizeof(*addr));
			fpurestore(get_pcb_user_save_td(td));
			set_pcb_flags(pcb, PCB_FPUINITDONE |
			    PCB_USERFPUINITDONE);
		}
	} else {
		error = fpusetxstate(td, xfpustate, xfpustate_size);
		if (error == 0) {
			bcopy(addr, get_pcb_user_save_td(td), sizeof(*addr));
			fpuuserinited(td);
		}
	}
	critical_exit();
	return (error);
}