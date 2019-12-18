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
typedef  int u_int ;
struct trapframe {int tf_spsr; int tf_pc; int tf_r0; int tf_r1; int tf_r2; int tf_r3; int tf_r4; int tf_r5; int tf_r6; int tf_r7; int tf_r8; int tf_r9; int tf_r10; int tf_r11; int tf_r12; int tf_usr_sp; int tf_usr_lr; int tf_svc_sp; int tf_svc_lr; } ;
struct thread {int dummy; } ;
struct ksig {int dummy; } ;
struct TYPE_2__ {char* desc; } ;

/* Variables and functions */
 int FAULT_EA_IMPREC ; 
 int FSR_WNR ; 
 int /*<<< orphan*/  KDB_WHY_TRAP ; 
 int /*<<< orphan*/  KDB_WHY_UNSET ; 
 int PSR_F ; 
 int PSR_I ; 
 int TRAPF_USERMODE (struct trapframe*) ; 
 TYPE_1__* aborts ; 
 scalar_t__ debugger_on_trap ; 
 int /*<<< orphan*/  disable_interrupts (int) ; 
 scalar_t__ dtrace_trap_func (struct trapframe*,int) ; 
 int /*<<< orphan*/  kdb_trap (int,int /*<<< orphan*/ ,struct trapframe*) ; 
 int /*<<< orphan*/  kdb_why ; 
 int /*<<< orphan*/  panic (char*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 scalar_t__ stub1 (struct trapframe*,int) ; 

__attribute__((used)) static int
abort_fatal(struct trapframe *tf, u_int idx, u_int fsr, u_int far,
    u_int prefetch, struct thread *td, struct ksig *ksig)
{
	bool usermode;
	const char *mode;
	const char *rw_mode;

	usermode = TRAPF_USERMODE(tf);
#ifdef KDTRACE_HOOKS
	if (!usermode) {
		if (dtrace_trap_func != NULL && (*dtrace_trap_func)(tf, far))
			return (0);
	}
#endif

	mode = usermode ? "user" : "kernel";
	rw_mode  = fsr & FSR_WNR ? "write" : "read";
	disable_interrupts(PSR_I|PSR_F);

	if (td != NULL) {
		printf("Fatal %s mode data abort: '%s' on %s\n", mode,
		    aborts[idx].desc, rw_mode);
		printf("trapframe: %p\nFSR=%08x, FAR=", tf, fsr);
		if (idx != FAULT_EA_IMPREC)
			printf("%08x, ", far);
		else
			printf("Invalid,  ");
		printf("spsr=%08x\n", tf->tf_spsr);
	} else {
		printf("Fatal %s mode prefetch abort at 0x%08x\n",
		    mode, tf->tf_pc);
		printf("trapframe: %p, spsr=%08x\n", tf, tf->tf_spsr);
	}

	printf("r0 =%08x, r1 =%08x, r2 =%08x, r3 =%08x\n",
	    tf->tf_r0, tf->tf_r1, tf->tf_r2, tf->tf_r3);
	printf("r4 =%08x, r5 =%08x, r6 =%08x, r7 =%08x\n",
	    tf->tf_r4, tf->tf_r5, tf->tf_r6, tf->tf_r7);
	printf("r8 =%08x, r9 =%08x, r10=%08x, r11=%08x\n",
	    tf->tf_r8, tf->tf_r9, tf->tf_r10, tf->tf_r11);
	printf("r12=%08x, ", tf->tf_r12);

	if (usermode)
		printf("usp=%08x, ulr=%08x",
		    tf->tf_usr_sp, tf->tf_usr_lr);
	else
		printf("ssp=%08x, slr=%08x",
		    tf->tf_svc_sp, tf->tf_svc_lr);
	printf(", pc =%08x\n\n", tf->tf_pc);

#ifdef KDB
	if (debugger_on_trap) {
		kdb_why = KDB_WHY_TRAP;
		kdb_trap(fsr, 0, tf);
		kdb_why = KDB_WHY_UNSET;
	}
#endif
	panic("Fatal abort");
	/*NOTREACHED*/
}