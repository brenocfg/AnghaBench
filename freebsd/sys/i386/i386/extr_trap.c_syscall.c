#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_6__ ;
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct trapframe {int tf_eflags; scalar_t__ tf_eip; } ;
struct TYPE_7__ {int /*<<< orphan*/  code; } ;
struct thread {TYPE_1__ td_sa; int /*<<< orphan*/  td_proc; TYPE_6__* td_pcb; struct trapframe* td_frame; } ;
typedef  int register_t ;
struct TYPE_8__ {void* ksi_addr; int /*<<< orphan*/  ksi_code; int /*<<< orphan*/  ksi_signo; } ;
typedef  TYPE_2__ ksiginfo_t ;
struct TYPE_10__ {scalar_t__ pcb_save; } ;
struct TYPE_9__ {int pcb_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int PCB_USER_FPU (TYPE_6__*) ; 
 int PCB_VM86CALL ; 
 int PSL_T ; 
 int PSL_VM ; 
 int /*<<< orphan*/  SIGTRAP ; 
 scalar_t__ TRAPF_USERMODE (struct trapframe*) ; 
 int /*<<< orphan*/  TRAP_TRACE ; 
 TYPE_5__* curpcb ; 
 struct thread* curthread ; 
 scalar_t__ get_pcb_user_save_td (struct thread*) ; 
 int /*<<< orphan*/  ksiginfo_init_trap (TYPE_2__*) ; 
 int /*<<< orphan*/  panic (char*) ; 
 int /*<<< orphan*/  syscallenter (struct thread*) ; 
 int /*<<< orphan*/  syscallname (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  syscallret (struct thread*) ; 
 int /*<<< orphan*/  trapsignal (struct thread*,TYPE_2__*) ; 

void
syscall(struct trapframe *frame)
{
	struct thread *td;
	register_t orig_tf_eflags;
	ksiginfo_t ksi;

#ifdef DIAGNOSTIC
	if (!(TRAPF_USERMODE(frame) &&
	    (curpcb->pcb_flags & PCB_VM86CALL) == 0)) {
		panic("syscall");
		/* NOT REACHED */
	}
#endif
	orig_tf_eflags = frame->tf_eflags;

	td = curthread;
	td->td_frame = frame;

	syscallenter(td);

	/*
	 * Traced syscall.
	 */
	if ((orig_tf_eflags & PSL_T) && !(orig_tf_eflags & PSL_VM)) {
		frame->tf_eflags &= ~PSL_T;
		ksiginfo_init_trap(&ksi);
		ksi.ksi_signo = SIGTRAP;
		ksi.ksi_code = TRAP_TRACE;
		ksi.ksi_addr = (void *)frame->tf_eip;
		trapsignal(td, &ksi);
	}

	KASSERT(PCB_USER_FPU(td->td_pcb),
	    ("System call %s returning with kernel FPU ctx leaked",
	     syscallname(td->td_proc, td->td_sa.code)));
	KASSERT(td->td_pcb->pcb_save == get_pcb_user_save_td(td),
	    ("System call %s returning with mangled pcb_save",
	     syscallname(td->td_proc, td->td_sa.code)));

	syscallret(td);
}