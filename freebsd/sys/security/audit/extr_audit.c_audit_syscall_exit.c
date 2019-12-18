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
struct thread {int* td_retval; int /*<<< orphan*/  td_pflags; int /*<<< orphan*/ * td_ar; } ;

/* Variables and functions */
 int /*<<< orphan*/  TDP_AUDITREC ; 
 int /*<<< orphan*/  audit_commit (int /*<<< orphan*/ *,int,int) ; 

void
audit_syscall_exit(int error, struct thread *td)
{
	int retval;

	/*
	 * Commit the audit record as desired; once we pass the record into
	 * audit_commit(), the memory is owned by the audit subsystem.  The
	 * return value from the system call is stored on the user thread.
	 * If there was an error, the return value is set to -1, imitating
	 * the behavior of the cerror routine.
	 */
	if (error)
		retval = -1;
	else
		retval = td->td_retval[0];

	audit_commit(td->td_ar, error, retval);
	td->td_ar = NULL;
	td->td_pflags &= ~TDP_AUDITREC;
}