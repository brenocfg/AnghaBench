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
struct trapframe {uintptr_t tf_rip; uintptr_t tf_rbp; uintptr_t tf_rsp; } ;
typedef  int /*<<< orphan*/  proc_t ;
struct TYPE_2__ {struct trapframe* td_frame; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPU_DTRACE_ENTRY ; 
 int /*<<< orphan*/  CPU_DTRACE_FAULT ; 
 scalar_t__ DTRACE_CPUFLAG_ISSET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * curproc ; 
 TYPE_1__* curthread ; 
 uintptr_t dtrace_fuword64 (void*) ; 
 scalar_t__ dtrace_getustack_common (int /*<<< orphan*/ *,int /*<<< orphan*/ ,uintptr_t,uintptr_t) ; 

int
dtrace_getustackdepth(void)
{
	proc_t *p = curproc;
	struct trapframe *tf;
	uintptr_t pc, fp, sp;
	int n = 0;

	if (p == NULL || (tf = curthread->td_frame) == NULL)
		return (0);

	if (DTRACE_CPUFLAG_ISSET(CPU_DTRACE_FAULT))
		return (-1);

	pc = tf->tf_rip;
	fp = tf->tf_rbp;
	sp = tf->tf_rsp;

	if (DTRACE_CPUFLAG_ISSET(CPU_DTRACE_ENTRY)) {
		/* 
		 * In an entry probe.  The frame pointer has not yet been
		 * pushed (that happens in the function prologue).  The
		 * best approach is to add the current pc as a missing top
		 * of stack and back the pc up to the caller, which is stored
		 * at the current stack pointer address since the call 
		 * instruction puts it there right before the branch.
		 */

		pc = dtrace_fuword64((void *) sp);
		n++;
	}

	n += dtrace_getustack_common(NULL, 0, pc, fp);

	return (n);
}