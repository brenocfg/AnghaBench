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
typedef  size_t u_int ;
struct trapframe {size_t tf_spsr; int tf_pc; int tf_r0; int tf_r1; int tf_r2; int tf_r3; int tf_r4; int tf_r5; int tf_r6; int tf_r7; int tf_r8; int tf_r9; int tf_r10; int tf_r11; size_t tf_r12; int tf_usr_sp; int tf_usr_lr; int tf_svc_sp; int tf_svc_lr; } ;
struct thread {int dummy; } ;
struct ksig {int dummy; } ;
struct TYPE_2__ {char* desc; } ;

/* Variables and functions */
 size_t FAULT_IMPRECISE ; 
 size_t FAULT_TYPE_MASK ; 
 int /*<<< orphan*/  KDB_WHY_TRAP ; 
 int /*<<< orphan*/  KDB_WHY_UNSET ; 
 int PSR_F ; 
 int PSR_I ; 
 scalar_t__ TRAP_USERMODE (struct trapframe*) ; 
 TYPE_1__* data_aborts ; 
 scalar_t__ debugger_on_trap ; 
 int /*<<< orphan*/  disable_interrupts (int) ; 
 scalar_t__ dtrace_trap_func (struct trapframe*,size_t) ; 
 scalar_t__ kdb_active ; 
 int /*<<< orphan*/  kdb_reenter () ; 
 int kdb_trap (size_t,int /*<<< orphan*/ ,struct trapframe*) ; 
 int /*<<< orphan*/  kdb_why ; 
 int /*<<< orphan*/  panic (char*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 scalar_t__ stub1 (struct trapframe*,size_t) ; 

__attribute__((used)) static int
dab_fatal(struct trapframe *tf, u_int fsr, u_int far, struct thread *td,
    struct ksig *ksig)
{
	const char *mode;
#ifdef KDB
	bool handled;
#endif

#ifdef KDB
	if (kdb_active) {
		kdb_reenter();
		return (0);
	}
#endif
#ifdef KDTRACE_HOOKS
	if (!TRAP_USERMODE(tf))	{
		if (dtrace_trap_func != NULL && (*dtrace_trap_func)(tf, far & FAULT_TYPE_MASK))
			return (0);
	}
#endif

	mode = TRAP_USERMODE(tf) ? "user" : "kernel";

	disable_interrupts(PSR_I|PSR_F);
	if (td != NULL) {
		printf("Fatal %s mode data abort: '%s'\n", mode,
		    data_aborts[fsr & FAULT_TYPE_MASK].desc);
		printf("trapframe: %p\nFSR=%08x, FAR=", tf, fsr);
		if ((fsr & FAULT_IMPRECISE) == 0)
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

	if (TRAP_USERMODE(tf))
		printf("usp=%08x, ulr=%08x",
		    tf->tf_usr_sp, tf->tf_usr_lr);
	else
		printf("ssp=%08x, slr=%08x",
		    tf->tf_svc_sp, tf->tf_svc_lr);
	printf(", pc =%08x\n\n", tf->tf_pc);

#ifdef KDB
	if (debugger_on_trap) {
		kdb_why = KDB_WHY_TRAP;
		handled = kdb_trap(fsr, 0, tf);
		kdb_why = KDB_WHY_UNSET;
		if (handled)
			return (0);
	}
#endif
	panic("Fatal abort");
	/*NOTREACHED*/
}