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
struct TYPE_2__ {size_t ss_size; int ss_flags; scalar_t__ ss_sp; } ;
struct thread {int td_pflags; TYPE_1__ td_sigstk; int /*<<< orphan*/  td_proc; } ;

/* Variables and functions */
 int SS_ONSTACK ; 
 int /*<<< orphan*/  SV_AOUT ; 
 scalar_t__ SV_PROC_FLAG (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int TDP_ALTSTACK ; 
 struct thread* curthread ; 

int
sigonstack(size_t sp)
{
	struct thread *td;

	td = curthread;
	if ((td->td_pflags & TDP_ALTSTACK) == 0)
		return (0);
#if defined(COMPAT_43)
	if (SV_PROC_FLAG(td->td_proc, SV_AOUT) && td->td_sigstk.ss_size == 0)
		return ((td->td_sigstk.ss_flags & SS_ONSTACK) != 0);
#endif
	return (sp >= (size_t)td->td_sigstk.ss_sp &&
	    sp < td->td_sigstk.ss_size + (size_t)td->td_sigstk.ss_sp);
}