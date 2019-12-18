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
struct timeval {int dummy; } ;
struct thread {int /*<<< orphan*/  td_flags; int /*<<< orphan*/  td_pflags; int /*<<< orphan*/  td_oldsigmask; } ;
typedef  int /*<<< orphan*/  sigset_t ;
typedef  int /*<<< orphan*/  fd_set ;

/* Variables and functions */
 int /*<<< orphan*/  SIG_SETMASK ; 
 int /*<<< orphan*/  TDF_ASTPENDING ; 
 int /*<<< orphan*/  TDP_OLDMASK ; 
 int kern_select (struct thread*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct timeval*,int) ; 
 int kern_sigprocmask (struct thread*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  thread_lock (struct thread*) ; 
 int /*<<< orphan*/  thread_unlock (struct thread*) ; 

int
kern_pselect(struct thread *td, int nd, fd_set *in, fd_set *ou, fd_set *ex,
    struct timeval *tvp, sigset_t *uset, int abi_nfdbits)
{
	int error;

	if (uset != NULL) {
		error = kern_sigprocmask(td, SIG_SETMASK, uset,
		    &td->td_oldsigmask, 0);
		if (error != 0)
			return (error);
		td->td_pflags |= TDP_OLDMASK;
		/*
		 * Make sure that ast() is called on return to
		 * usermode and TDP_OLDMASK is cleared, restoring old
		 * sigmask.
		 */
		thread_lock(td);
		td->td_flags |= TDF_ASTPENDING;
		thread_unlock(td);
	}
	error = kern_select(td, nd, in, ou, ex, tvp, abi_nfdbits);
	return (error);
}