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
struct thread {int td_flags; int td_intrval; } ;

/* Variables and functions */
 int /*<<< orphan*/  MA_OWNED ; 
 int TDF_SINTR ; 
 int TDF_SLEEPABORT ; 
 int /*<<< orphan*/  THREAD_LOCK_ASSERT (struct thread*,int /*<<< orphan*/ ) ; 
 struct thread* curthread ; 

__attribute__((used)) static int
sleepq_check_signals(void)
{
	struct thread *td;

	td = curthread;
	THREAD_LOCK_ASSERT(td, MA_OWNED);

	/* We are no longer in an interruptible sleep. */
	if (td->td_flags & TDF_SINTR)
		td->td_flags &= ~TDF_SINTR;

	if (td->td_flags & TDF_SLEEPABORT) {
		td->td_flags &= ~TDF_SLEEPABORT;
		return (td->td_intrval);
	}

	return (0);
}