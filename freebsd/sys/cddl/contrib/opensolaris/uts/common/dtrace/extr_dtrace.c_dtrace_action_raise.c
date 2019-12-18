#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint8_t ;
typedef  scalar_t__ uint64_t ;
struct proc {int dummy; } ;
struct TYPE_3__ {scalar_t__ t_dtrace_sig; int t_sig_check; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPU_DTRACE_ILLOP ; 
 int /*<<< orphan*/  DTRACE_CPUFLAG_SET (int /*<<< orphan*/ ) ; 
 scalar_t__ NSIG ; 
 int /*<<< orphan*/  PROC_LOCK (struct proc*) ; 
 int /*<<< orphan*/  PROC_UNLOCK (struct proc*) ; 
 int /*<<< orphan*/  aston (TYPE_1__*) ; 
 struct proc* curproc ; 
 TYPE_1__* curthread ; 
 scalar_t__ dtrace_destructive_disallow ; 
 int /*<<< orphan*/  kern_psignal (struct proc*,scalar_t__) ; 

__attribute__((used)) static void
dtrace_action_raise(uint64_t sig)
{
	if (dtrace_destructive_disallow)
		return;

	if (sig >= NSIG) {
		DTRACE_CPUFLAG_SET(CPU_DTRACE_ILLOP);
		return;
	}

#ifdef illumos
	/*
	 * raise() has a queue depth of 1 -- we ignore all subsequent
	 * invocations of the raise() action.
	 */
	if (curthread->t_dtrace_sig == 0)
		curthread->t_dtrace_sig = (uint8_t)sig;

	curthread->t_sig_check = 1;
	aston(curthread);
#else
	struct proc *p = curproc;
	PROC_LOCK(p);
	kern_psignal(p, sig);
	PROC_UNLOCK(p);
#endif
}