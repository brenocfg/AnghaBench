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
struct thread {int dummy; } ;
struct sigevent {scalar_t__ sigev_notify; int /*<<< orphan*/  sigev_notify_thread_id; } ;
struct proc {int /*<<< orphan*/  p_pid; } ;

/* Variables and functions */
 int ESRCH ; 
 int /*<<< orphan*/  PROC_LOCK (struct proc*) ; 
 scalar_t__ SIGEV_THREAD_ID ; 
 struct thread* tdfind (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
sigev_findtd(struct proc *p ,struct sigevent *sigev, struct thread **ttd)
{
	struct thread *td;

	if (sigev->sigev_notify == SIGEV_THREAD_ID) {
		td = tdfind(sigev->sigev_notify_thread_id, p->p_pid);
		if (td == NULL)
			return (ESRCH);
		*ttd = td;
	} else {
		*ttd = NULL;
		PROC_LOCK(p);
	}
	return (0);
}