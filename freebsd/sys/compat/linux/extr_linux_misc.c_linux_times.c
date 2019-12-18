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
typedef  int /*<<< orphan*/  tms ;
struct timeval {int dummy; } ;
struct thread {int* td_retval; struct proc* td_proc; } ;
struct proc {int dummy; } ;
struct linux_times_args {int /*<<< orphan*/ * buf; } ;
struct l_times_argv {void* tms_cstime; void* tms_cutime; void* tms_stime; void* tms_utime; } ;

/* Variables and functions */
 void* CONVTCK (struct timeval) ; 
 int /*<<< orphan*/  PROC_LOCK (struct proc*) ; 
 int /*<<< orphan*/  PROC_STATLOCK (struct proc*) ; 
 int /*<<< orphan*/  PROC_STATUNLOCK (struct proc*) ; 
 int /*<<< orphan*/  PROC_UNLOCK (struct proc*) ; 
 int /*<<< orphan*/  calccru (struct proc*,struct timeval*,struct timeval*) ; 
 int /*<<< orphan*/  calcru (struct proc*,struct timeval*,struct timeval*) ; 
 int copyout (struct l_times_argv*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  microuptime (struct timeval*) ; 

int
linux_times(struct thread *td, struct linux_times_args *args)
{
	struct timeval tv, utime, stime, cutime, cstime;
	struct l_times_argv tms;
	struct proc *p;
	int error;

	if (args->buf != NULL) {
		p = td->td_proc;
		PROC_LOCK(p);
		PROC_STATLOCK(p);
		calcru(p, &utime, &stime);
		PROC_STATUNLOCK(p);
		calccru(p, &cutime, &cstime);
		PROC_UNLOCK(p);

		tms.tms_utime = CONVTCK(utime);
		tms.tms_stime = CONVTCK(stime);

		tms.tms_cutime = CONVTCK(cutime);
		tms.tms_cstime = CONVTCK(cstime);

		if ((error = copyout(&tms, args->buf, sizeof(tms))))
			return (error);
	}

	microuptime(&tv);
	td->td_retval[0] = (int)CONVTCK(tv);
	return (0);
}