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
typedef  scalar_t__ uint64_t ;
struct thread {scalar_t__* td_retval; int /*<<< orphan*/  td_proc; } ;
struct getdtablesize_args {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PROC_LOCK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PROC_UNLOCK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RACCT_NOFILE ; 
 scalar_t__ getmaxfd (struct thread*) ; 
 scalar_t__ racct_get_limit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
sys_getdtablesize(struct thread *td, struct getdtablesize_args *uap)
{
#ifdef	RACCT
	uint64_t lim;
#endif

	td->td_retval[0] = getmaxfd(td);
#ifdef	RACCT
	PROC_LOCK(td->td_proc);
	lim = racct_get_limit(td->td_proc, RACCT_NOFILE);
	PROC_UNLOCK(td->td_proc);
	if (lim < td->td_retval[0])
		td->td_retval[0] = lim;
#endif
	return (0);
}