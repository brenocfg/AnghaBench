#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_8__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int /*<<< orphan*/  gen; } ;
struct TYPE_12__ {TYPE_2__ md_invl_gen; } ;
struct TYPE_10__ {int /*<<< orphan*/  code; } ;
struct thread {int /*<<< orphan*/  td_errno; TYPE_6__* td_pcb; TYPE_8__* td_frame; TYPE_3__ td_md; TYPE_1__ td_sa; int /*<<< orphan*/  td_proc; } ;
struct TYPE_13__ {void* ksi_addr; int /*<<< orphan*/  ksi_code; int /*<<< orphan*/  ksi_signo; } ;
typedef  TYPE_4__ ksiginfo_t ;
struct TYPE_15__ {scalar_t__ tf_rip; int /*<<< orphan*/  tf_rflags; } ;
struct TYPE_14__ {scalar_t__ pcb_save; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  PCB_FULL_IRET ; 
 int PCB_USER_FPU (TYPE_6__*) ; 
 int /*<<< orphan*/  PSL_T ; 
 int /*<<< orphan*/  SIGTRAP ; 
 int /*<<< orphan*/  TRAPF_USERMODE (TYPE_8__*) ; 
 int /*<<< orphan*/  TRAP_TRACE ; 
 scalar_t__ VM_MAXUSER_ADDRESS ; 
 scalar_t__ __predict_false (int) ; 
 int /*<<< orphan*/  amd64_syscall_ret_flush_l1d_inline (int /*<<< orphan*/ ) ; 
 scalar_t__ get_pcb_user_save_td (struct thread*) ; 
 int /*<<< orphan*/  ksiginfo_init_trap (TYPE_4__*) ; 
 int /*<<< orphan*/  panic (char*) ; 
 int pmap_not_in_di () ; 
 int /*<<< orphan*/  set_pcb_flags (TYPE_6__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  syscallenter (struct thread*) ; 
 int /*<<< orphan*/  syscallname (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  syscallret (struct thread*) ; 
 int /*<<< orphan*/  trapsignal (struct thread*,TYPE_4__*) ; 

void
amd64_syscall(struct thread *td, int traced)
{
	ksiginfo_t ksi;

#ifdef DIAGNOSTIC
	if (!TRAPF_USERMODE(td->td_frame)) {
		panic("syscall");
		/* NOT REACHED */
	}
#endif
	syscallenter(td);

	/*
	 * Traced syscall.
	 */
	if (__predict_false(traced)) {
		td->td_frame->tf_rflags &= ~PSL_T;
		ksiginfo_init_trap(&ksi);
		ksi.ksi_signo = SIGTRAP;
		ksi.ksi_code = TRAP_TRACE;
		ksi.ksi_addr = (void *)td->td_frame->tf_rip;
		trapsignal(td, &ksi);
	}

	KASSERT(PCB_USER_FPU(td->td_pcb),
	    ("System call %s returning with kernel FPU ctx leaked",
	     syscallname(td->td_proc, td->td_sa.code)));
	KASSERT(td->td_pcb->pcb_save == get_pcb_user_save_td(td),
	    ("System call %s returning with mangled pcb_save",
	     syscallname(td->td_proc, td->td_sa.code)));
	KASSERT(pmap_not_in_di(),
	    ("System call %s returning with leaked invl_gen %lu",
	    syscallname(td->td_proc, td->td_sa.code),
	    td->td_md.md_invl_gen.gen));

	syscallret(td);

	/*
	 * If the user-supplied value of %rip is not a canonical
	 * address, then some CPUs will trigger a ring 0 #GP during
	 * the sysret instruction.  However, the fault handler would
	 * execute in ring 0 with the user's %gs and %rsp which would
	 * not be safe.  Instead, use the full return path which
	 * catches the problem safely.
	 */
	if (__predict_false(td->td_frame->tf_rip >= VM_MAXUSER_ADDRESS))
		set_pcb_flags(td->td_pcb, PCB_FULL_IRET);

	amd64_syscall_ret_flush_l1d_inline(td->td_errno);
}