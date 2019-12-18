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
typedef  int uint64_t ;
struct trapframe {int tf_scause; int tf_sepc; int /*<<< orphan*/  tf_stval; int /*<<< orphan*/  tf_sstatus; } ;
struct thread {struct pcb* td_pcb; struct trapframe* td_frame; } ;
struct pcb {int pcb_fpflags; } ;

/* Variables and functions */
 int /*<<< orphan*/  CTR3 (int /*<<< orphan*/ ,char*,struct thread*,int,struct trapframe*) ; 
#define  EXCP_BREAKPOINT 136 
#define  EXCP_FAULT_FETCH 135 
#define  EXCP_FAULT_LOAD 134 
#define  EXCP_FAULT_STORE 133 
#define  EXCP_ILLEGAL_INSTRUCTION 132 
#define  EXCP_INST_PAGE_FAULT 131 
 int EXCP_INTR ; 
#define  EXCP_LOAD_PAGE_FAULT 130 
 int EXCP_MASK ; 
#define  EXCP_STORE_PAGE_FAULT 129 
#define  EXCP_USER_ECALL 128 
 int /*<<< orphan*/  ILL_ILLTRP ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  KTR_TRAP ; 
 int PCB_FP_STARTED ; 
 int /*<<< orphan*/  SIGILL ; 
 int /*<<< orphan*/  SIGTRAP ; 
 int /*<<< orphan*/  SSTATUS_FS_CLEAN ; 
 int /*<<< orphan*/  SSTATUS_FS_MASK ; 
 int SSTATUS_SIE ; 
 int SSTATUS_SPP ; 
 int /*<<< orphan*/  TRAP_BRKPT ; 
 int /*<<< orphan*/  call_trapsignal (struct thread*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ; 
 struct thread* curthread ; 
 int /*<<< orphan*/  data_abort (struct trapframe*,int) ; 
 int /*<<< orphan*/  dump_regs (struct trapframe*) ; 
 int /*<<< orphan*/  fpe_state_clear () ; 
 int /*<<< orphan*/  panic (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  riscv_cpu_intr (struct trapframe*) ; 
 int /*<<< orphan*/  svc_handler (struct trapframe*) ; 
 int /*<<< orphan*/  userret (struct thread*,struct trapframe*) ; 

void
do_trap_user(struct trapframe *frame)
{
	uint64_t exception;
	struct thread *td;
	uint64_t sstatus;
	struct pcb *pcb;

	td = curthread;
	td->td_frame = frame;
	pcb = td->td_pcb;

	/* Ensure we came from usermode, interrupts disabled */
	__asm __volatile("csrr %0, sstatus" : "=&r" (sstatus));
	KASSERT((sstatus & (SSTATUS_SPP | SSTATUS_SIE)) == 0,
			("We must came from U mode with interrupts disabled"));

	exception = (frame->tf_scause & EXCP_MASK);
	if (frame->tf_scause & EXCP_INTR) {
		/* Interrupt */
		riscv_cpu_intr(frame);
		return;
	}

	CTR3(KTR_TRAP, "do_trap_user: curthread: %p, sepc: %lx, frame: %p",
	    curthread, frame->tf_sepc, frame);

	switch(exception) {
	case EXCP_FAULT_LOAD:
	case EXCP_FAULT_STORE:
	case EXCP_FAULT_FETCH:
	case EXCP_STORE_PAGE_FAULT:
	case EXCP_LOAD_PAGE_FAULT:
	case EXCP_INST_PAGE_FAULT:
		data_abort(frame, 1);
		break;
	case EXCP_USER_ECALL:
		frame->tf_sepc += 4;	/* Next instruction */
		svc_handler(frame);
		break;
	case EXCP_ILLEGAL_INSTRUCTION:
#ifdef FPE
		if ((pcb->pcb_fpflags & PCB_FP_STARTED) == 0) {
			/*
			 * May be a FPE trap. Enable FPE usage
			 * for this thread and try again.
			 */
			fpe_state_clear();
			frame->tf_sstatus &= ~SSTATUS_FS_MASK;
			frame->tf_sstatus |= SSTATUS_FS_CLEAN;
			pcb->pcb_fpflags |= PCB_FP_STARTED;
			break;
		}
#endif
		call_trapsignal(td, SIGILL, ILL_ILLTRP, (void *)frame->tf_sepc);
		userret(td, frame);
		break;
	case EXCP_BREAKPOINT:
		call_trapsignal(td, SIGTRAP, TRAP_BRKPT, (void *)frame->tf_sepc);
		userret(td, frame);
		break;
	default:
		dump_regs(frame);
		panic("Unknown userland exception %x, trap value %lx\n",
		    exception, frame->tf_stval);
	}
}