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
struct thread {struct proc* td_proc; } ;
struct setlogin_args {int /*<<< orphan*/  namebuf; } ;
struct proc {TYPE_1__* p_session; } ;
typedef  int /*<<< orphan*/  logintmp ;
struct TYPE_3__ {int /*<<< orphan*/  s_login; } ;

/* Variables and functions */
 int /*<<< orphan*/  AUDIT_ARG_LOGIN (char*) ; 
 int /*<<< orphan*/  CTASSERT (int) ; 
 int EINVAL ; 
 int ENAMETOOLONG ; 
 int MAXLOGNAME ; 
 int /*<<< orphan*/  PRIV_PROC_SETLOGIN ; 
 int /*<<< orphan*/  PROC_LOCK (struct proc*) ; 
 int /*<<< orphan*/  PROC_UNLOCK (struct proc*) ; 
 int /*<<< orphan*/  SESS_LOCK (TYPE_1__*) ; 
 int /*<<< orphan*/  SESS_UNLOCK (TYPE_1__*) ; 
 int copyinstr (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ *) ; 
 int priv_check (struct thread*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char*) ; 

int
sys_setlogin(struct thread *td, struct setlogin_args *uap)
{
	struct proc *p = td->td_proc;
	int error;
	char logintmp[MAXLOGNAME];

	CTASSERT(sizeof(p->p_session->s_login) >= sizeof(logintmp));

	error = priv_check(td, PRIV_PROC_SETLOGIN);
	if (error)
		return (error);
	error = copyinstr(uap->namebuf, logintmp, sizeof(logintmp), NULL);
	if (error != 0) {
		if (error == ENAMETOOLONG)
			error = EINVAL;
		return (error);
	}
	AUDIT_ARG_LOGIN(logintmp);
	PROC_LOCK(p);
	SESS_LOCK(p->p_session);
	strcpy(p->p_session->s_login, logintmp);
	SESS_UNLOCK(p->p_session);
	PROC_UNLOCK(p);
	return (0);
}