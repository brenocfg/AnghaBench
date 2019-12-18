#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_int32_t ;
typedef  scalar_t__ u_int ;
struct trapframe {int tf_spsr; } ;
struct thread {int /*<<< orphan*/  td_proc; } ;
struct TYPE_4__ {int /*<<< orphan*/ * ksi_addr; int /*<<< orphan*/  ksi_code; void* ksi_signo; } ;
typedef  TYPE_1__ ksiginfo_t ;

/* Variables and functions */
 int FAULT_USER ; 
 scalar_t__ GDB5_BREAKPOINT ; 
 scalar_t__ GDB_BREAKPOINT ; 
 int /*<<< orphan*/  PROC_LOCK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PROC_UNLOCK (int /*<<< orphan*/ ) ; 
 int PSR_T ; 
 scalar_t__ PTRACE_BREAKPOINT ; 
 void* SIGTRAP ; 
 int /*<<< orphan*/  TRAP_BRKPT ; 
 int /*<<< orphan*/  TRAP_TRACE ; 
 int /*<<< orphan*/  T_BREAKPOINT ; 
 int /*<<< orphan*/  _PHOLD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _PRELE (int /*<<< orphan*/ ) ; 
 struct thread* curthread ; 
 int /*<<< orphan*/  kgdb_trap (int /*<<< orphan*/ ,struct trapframe*) ; 
 int /*<<< orphan*/  ksiginfo_init_trap (TYPE_1__*) ; 
 int ptrace_clear_single_step (struct thread*) ; 
 struct thread thread0 ; 
 int /*<<< orphan*/  trapsignal (struct thread*,TYPE_1__*) ; 

__attribute__((used)) static int
gdb_trapper(u_int addr, u_int insn, struct trapframe *frame, int code)
{
	struct thread *td;
	ksiginfo_t ksi;
	int error;

	td = (curthread == NULL) ? &thread0 : curthread;

	if (insn == GDB_BREAKPOINT || insn == GDB5_BREAKPOINT) {
		if (code == FAULT_USER) {
			ksiginfo_init_trap(&ksi);
			ksi.ksi_signo = SIGTRAP;
			ksi.ksi_code = TRAP_BRKPT;
			ksi.ksi_addr = (u_int32_t *)addr;
			trapsignal(td, &ksi);
			return 0;
		}
#if 0
#ifdef KGDB
		return !kgdb_trap(T_BREAKPOINT, frame);
#endif
#endif
	}

	if (code == FAULT_USER) {
		/* TODO: No support for ptrace from Thumb-2 */
		if ((frame->tf_spsr & PSR_T) == 0 &&
		    insn == PTRACE_BREAKPOINT) {
			PROC_LOCK(td->td_proc);
			_PHOLD(td->td_proc);
			error = ptrace_clear_single_step(td);
			_PRELE(td->td_proc);
			PROC_UNLOCK(td->td_proc);
			if (error == 0) {
				ksiginfo_init_trap(&ksi);
				ksi.ksi_signo = SIGTRAP;
				ksi.ksi_code = TRAP_TRACE;
				ksi.ksi_addr = (u_int32_t *)addr;
				trapsignal(td, &ksi);
				return (0);
			}
		}
	}
	
	return 1;
}