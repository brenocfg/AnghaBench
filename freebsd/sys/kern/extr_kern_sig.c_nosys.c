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
struct TYPE_2__ {int code; } ;
struct thread {TYPE_1__ td_sa; struct proc* td_proc; } ;
struct proc {int p_pid; char* p_comm; } ;
struct nosys_args {int dummy; } ;

/* Variables and functions */
 int ENOSYS ; 
 int /*<<< orphan*/  PROC_LOCK (struct proc*) ; 
 int /*<<< orphan*/  PROC_UNLOCK (struct proc*) ; 
 int /*<<< orphan*/  SIGSYS ; 
 int kern_lognosys ; 
 int /*<<< orphan*/  printf (char*,int,char*,int) ; 
 int /*<<< orphan*/  tdsignal (struct thread*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uprintf (char*,int,char*,int) ; 

int
nosys(struct thread *td, struct nosys_args *args)
{
	struct proc *p;

	p = td->td_proc;

	PROC_LOCK(p);
	tdsignal(td, SIGSYS);
	PROC_UNLOCK(p);
	if (kern_lognosys == 1 || kern_lognosys == 3) {
		uprintf("pid %d comm %s: nosys %d\n", p->p_pid, p->p_comm,
		    td->td_sa.code);
	}
	if (kern_lognosys == 2 || kern_lognosys == 3) {
		printf("pid %d comm %s: nosys %d\n", p->p_pid, p->p_comm,
		    td->td_sa.code);
	}
	return (ENOSYS);
}